
#include <limits.h>

#include "engine/threadsafe/bbThreadedPool.h"

#include "engine/logic/bbArith.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbVPool.h"


extern _Thread_local char* thread;

bbFlag bbThreadedPool_lookup_unsafe(bbThreadedPool* pool, void** address, bbPool_Handle handle)
{

    bbAssert(handle.u64 >= 0 && handle.u64 < pool->num, "index %d out of bounds\n", handle.u64);
    I32 offset = handle.u64 * pool->sizeOf;

    *address = &pool->elements[offset];
    return Success;
}

bbFlag bbThreadedPool_reverseLookup_unsafe(bbThreadedPool* pool, void* address, bbPool_Handle* handle)
{
    I32 offset = (U8*)address - (U8*)&pool->elements[0];
    I32 index = offset / pool->sizeOf;
    bbAssert(index >= 0 && index < pool->num, "index %d out of bounds\n", index);
    handle->u64 = index;

    return Success;
}


bbFlag bbVPool_newThreaded(bbVPool** self, I32 sizeOf, I32 num)
{
    bbThreadedPool* ThreadedPool;
    bbThreadedPool_new(&ThreadedPool, sizeOf, num);
    bbVPool* pool = malloc(sizeof(bbVPool));
    bbAssert(pool != NULL, "bad malloc\n");
    pool->pool = ThreadedPool;
    pool->null = ThreadedPool->null;
    pool->sizeOf = ThreadedPool->sizeOf;
    pool->delete = (bbFlag (*)(void* pool)) bbThreadedPool_delete;
    pool->clear = bbThreadedPool_clear;
    pool->allocImpl = (bbFlag(*)(void* pool, void** address, char* file, int
    line)) bbThreadedPool_allocImpl;
    pool->free = (bbFlag(*)(void* pool, void* address)) bbThreadedPool_free;
    pool->lookup = (bbFlag (*)(void* pool, void** address, bbPool_Handle
    handle)) bbThreadedPool_lookup;
    pool->reverseLookup = bbThreadedPool_reverseLookup;
    pool->printHeader = bbThreadedPool_printHeader;
    pool->handleIsEqual = bbThreadedPool_handleIsEqual;
    *self = pool;
    return Success;

}

bbFlag bbThreadedPool_new(bbThreadedPool** self, I32 sizeOf, I32 num)
{
    bbAssert(num>2, "num to small\n");
    bbAssert(sizeOf > 0, "sizeOf too small\n");

    I32 size = bbArith_roundUp(sizeOf, 8);


    bbThreadedPool* pool = malloc(sizeof(bbThreadedPool)+ num * size * sizeof(U8));

    bbAssert(pool != NULL, "bad malloc\n");

    pool->null.u64 = UINT64_MAX;
    pool->sizeOf = size;
    pool->num = num;
    pool->inUse = 0;

    pool->availableHead = 0;
    pool->availableTail = num-1;

    bbPool_Handle handle; bbThreadedPool_available* element;
    for (I32 i = 0; i < num; i++)
    {
        handle.u64 = i;
        

        I32 offset = i * pool->sizeOf;
        element = (bbThreadedPool_available*)&pool->elements[offset];

        element->prev = i-1;
        element->next = i+1;
    }
    handle.u64 = 0;
    
    bbThreadedPool_lookup_unsafe(pool, (void*)&element, handle);
    element->prev = -1;
    handle.u64 = num-1;
    
    bbThreadedPool_lookup_unsafe(pool, (void*)&element, handle);
    element->next = -1;

    pthread_mutex_init(&pool->mutex, NULL);
    pthread_mutex_init(&pool->poolFull, NULL);
    pthread_cond_init(&pool->poolFull2, NULL);

    *self = pool;


    return Success;
}

bbFlag bbThreadedPool_delete(bbThreadedPool* pool){

    free(pool);
    return Success;
}

//Takes element from Head
bbFlag bbThreadedPool_allocImpl(bbThreadedPool* pool, void** address, char* file, int line)
{
    bbMutexLock(&pool->mutex);

    if (pool->inUse >= pool->num)
    {
        //assert available list empty
        bbMutexUnlock(&pool->mutex);

        //there is a bug when mutex is unlocked in between the following lines
        pthread_cond_wait(&pool->poolFull2, &pool->poolFull);
        bbMutexLock(&pool->mutex);
    }

    pool->inUse++;

    bbPool_Handle handle;
    bbThreadedPool_available* element;
    handle.u64 = pool->availableHead;

    bbThreadedPool_lookup_unsafe(pool, (void*)&element, handle);


    if (element->next == -1) //last element
    {
        bbAssert(pool->inUse == pool->num, "We should not get here until pool is almost empty");;
        pool->availableHead = -1;
        pool->availableTail = -1;

        *address = element;
        bbMutexUnlock(&pool->mutex);
        return Success;
    }

    bbThreadedPool_available* next_element;
    handle.u64 = element->next;
    
    bbThreadedPool_lookup_unsafe(pool, (void*)&next_element, handle);

    next_element->prev = -1;
    pool->availableHead = element->next;


    memset(element, 0, pool->sizeOf);

    *address = element;

    bbMutexUnlock(&pool->mutex);

    return Success;
}

//Adds element to Head
bbFlag bbThreadedPool_free(bbThreadedPool* pool, void* address)
{
    bbMutexLock(&pool->mutex);
    pool->inUse--;
    pthread_cond_signal(&pool->poolFull2);

    //pool full, reserve empty
    if (pool->availableHead == -1)
    {
        bbAssert(pool->availableTail == -1, "head/tail mismatch\n");
        bbPool_Handle handle;
        
        bbThreadedPool_reverseLookup_unsafe(pool, address, &handle);
        pool->availableHead = handle.u64;
        pool->availableTail = handle.u64;

        bbThreadedPool_available* element = address;
        element->prev = -1;
        element->next = -1;


        bbMutexUnlock(&pool->poolFull);
        bbMutexUnlock(&pool->mutex);
        return Success;


    }



    bbThreadedPool_available* next_element;
    bbPool_Handle next_handle;
    next_handle.u64 = pool->availableHead;
    
    bbThreadedPool_lookup_unsafe(pool, (void**)&next_element, next_handle);

    bbPool_Handle handle;
    
    bbThreadedPool_reverseLookup_unsafe(pool, address, &handle);
    bbThreadedPool_available* element = address;

    next_element->prev = handle.u64;
    pool->availableHead = handle.u64;
    element->next = next_handle.u64;
    element->prev = -1;

    //the following line may not be necessary because the pool is not full

    bbMutexUnlock(&pool->poolFull);
    bbMutexUnlock(&pool->mutex);
    return Success;
}

bbFlag bbThreadedPool_lookup(bbThreadedPool* pool, void** address, bbPool_Handle handle)
{
    //bbMutexLock(&pool->mutex);
    void** element;
    bbThreadedPool_lookup_unsafe(pool, (void**)&element, handle);
    *address = element;
    //bbMutexUnlock(&pool->mutex);
    return Success;
}

bbFlag bbThreadedPool_reverseLookup(void* Pool, void* address, bbPool_Handle* Handle)
{
    bbThreadedPool* pool = Pool;
    //bbMutexLock(&pool->mutex);
    bbPool_Handle handle;
    bbThreadedPool_reverseLookup_unsafe(pool, (void*)address, &handle);
    *Handle = handle;
    //bbMutexUnlock(&pool->mutex);
    return Success;
}

I32 bbThreadedPool_handleIsEqual(void* USUSED, bbPool_Handle A, bbPool_Handle B)
{
    return (A.u64 == B.u64);
}

bbFlag bbThreadedPool_clear(void* Pool)
{
    bbThreadedPool* pool = Pool;
    bbMutexLock(&pool->mutex);
    bbThreadedPool_available* element;
    pool->inUse = 0;
    for (I32 i = 0; i < pool->num; i++)
    {
        element = (bbThreadedPool_available*)&pool->elements[i];
        element->prev = i-1;
        element->next = i+1;
    }
    element = (bbThreadedPool_available*)&pool->elements[0];
    element->prev = -1;
    element = (bbThreadedPool_available*)&pool->elements[pool->num-1];
    element->next = -1;

    pool->availableHead = 0;
    pool->availableTail = pool->num - 1;


    bbMutexUnlock(&pool->mutex);
    return Success;
}


bbFlag bbThreadedPool_printHeader(void* Pool, void* address)
{
    bbThreadedPool* pool = Pool;
    bbPool_Handle handle;
    bbThreadedPool_reverseLookup(Pool, address, &handle);
    bbPrintf("Element id at index %d\n", handle.u64);

    return Success;
}


