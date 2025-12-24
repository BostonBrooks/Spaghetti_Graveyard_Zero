
#include <limits.h>

#include "engine/threadsafe/bbThreadedPool.h"
#include "engine/logic/bbArith.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbVPool.h"

bbFlag bbThreadedPool_lookup_unsafe(bbThreadedPool* pool, void** address, bbPool_Handle handle)
{
    I32 offset = handle.u64 * pool->sizeOf;
    *address = &pool->elements[offset];
    return Success;
}

bbFlag bbThreadedPool_reverseLookup_unsafe(bbThreadedPool* pool, void* address, bbPool_Handle* handle)
{
    I32 offset = (U8*)address - (U8*)&pool->elements[0];
    I32 index = offset / pool->sizeOf;
    handle->u64 = index;

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

    bbPool_Handle handle; bbThreadedPool_unused* element;
    for (I32 i = 0; i < num; i++)
    {
        handle.u64 = i;
        
        bbThreadedPool_lookup_unsafe(pool, (void*)&element, handle);

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
    pthread_mutex_lock(&pool->mutex);
    bbAssert(pool->inUse < pool->num, "pool full\n");

    pool->inUse++;
    bbPool_Handle handle;
    bbThreadedPool_unused* element;
    handle.u64 = pool->availableHead;
    
    bbThreadedPool_lookup_unsafe(pool, (void*)&element, handle);

    if (element->next == -1) //last element
    {
        pool->availableHead = -1;
        pool->availableTail = -1;

        *address = element;
        pthread_mutex_unlock(&pool->mutex);
        return Success;
    }

    bbThreadedPool_unused* next_element;
    handle.u64 = element->next;
    
    bbThreadedPool_lookup_unsafe(pool, (void*)&next_element, handle);

    next_element->prev = -1;
    pool->availableHead = element->next;

    *address = element;

    pthread_mutex_unlock(&pool->mutex);
    return Success;
}

//Adds element to Head
bbFlag bbThreadedPool_free(bbThreadedPool* pool, void* address)
{
    pthread_mutex_lock(&pool->mutex);
    pool->inUse--;

    //Add to empty pool
    if (pool->availableHead == -1)
    {
        bbAssert(pool->availableTail == -1, "head/tail mismatch\n");
        bbPool_Handle handle;
        
        bbThreadedPool_reverseLookup_unsafe(pool, address, &handle);
        pool->availableHead = handle.u64;
        pool->availableTail = handle.u64;

        bbThreadedPool_unused* element = address;
        element->prev = -1;
        element->next = -1;
\
        pthread_mutex_unlock(&pool->mutex);
        return Success;


    }



    bbThreadedPool_unused* next_element;
    bbPool_Handle next_handle;
    next_handle.u64 = pool->availableHead;
    
    bbThreadedPool_lookup_unsafe(pool, (void**)&next_element, next_handle);

    bbPool_Handle handle;
    
    bbThreadedPool_reverseLookup_unsafe(pool, address, &handle);
    bbThreadedPool_unused* element = address;

    next_element->prev = handle.u64;
    pool->availableHead = handle.u64;
    element->next = next_handle.u64;
    element->prev = -1;

    pthread_mutex_unlock(&pool->mutex);
    return Success;
}

bbFlag bbThreadedPool_lookup(bbThreadedPool* pool, void** address, bbPool_Handle handle)
{
    pthread_mutex_lock(&pool->mutex);
    void** element;
    bbThreadedPool_lookup_unsafe(pool, (void**)&element, handle);
    *address = element;
    pthread_mutex_unlock(&pool->mutex);
    return Success;
}

bbFlag bbThreadedPool_reverseLookup(bbThreadedPool* pool, void* address, bbPool_Handle* Handle)
{
    pthread_mutex_lock(&pool->mutex);
    bbPool_Handle handle;
    bbThreadedPool_reverseLookup_unsafe(pool, (void*)address, &handle);
    *Handle = handle;
    pthread_mutex_unlock(&pool->mutex);
    return Success;
}