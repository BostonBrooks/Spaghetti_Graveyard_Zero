/** The threadsafe pool includes a guard so that it can only be modified by one thread at a time.
 * If an element is allocated, then freed, the pool will be in the same state as it was
 **/
#ifndef BB_THREADED_POOL_H
#define BB_THREADED_POOL_H

#include <pthread.h>
#include <stdalign.h>

#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbVPool.h"


typedef struct
{
    I32 prev;
    I32 next;
} bbThreadedPool_available;

typedef struct
{
    bbPool_Handle null;
    I32 num;
    I32 sizeOf;
    I32 inUse;
    I32 availableHead;
    I32 availableTail;
    pthread_mutex_t mutex;
    //If pool full, thread waits until pool is not full
    pthread_mutex_t poolFull;
    pthread_cond_t poolFull2;
    alignas(8) U8 elements[];
} bbThreadedPool;

#define bbThreadedPool_alloc(pool, address)\
bbThreadedPool_allocImpl(pool, address, NULL, 0);


bbFlag bbVPool_newThreaded(bbVPool** pool, I32 sizeOf, I32 num);
bbFlag bbThreadedPool_new(bbThreadedPool** pool, I32 sizeOf, I32 num);
bbFlag bbThreadedPool_delete(bbThreadedPool* pool);
bbFlag bbThreadedPool_clear(void* pool);
bbFlag bbThreadedPool_allocImpl(bbThreadedPool* pool, void** address, char* file, int
line);
bbFlag bbThreadedPool_free(bbThreadedPool* pool, void* address);
bbFlag bbThreadedPool_lookup(bbThreadedPool* pool, void** address, bbPool_Handle handle);
bbFlag bbThreadedPool_reverseLookup(void* Pool, void* address, bbPool_Handle*
handle);
bbFlag bbThreadedPool_printHeader(void* Pool, void* address);
I32 bbThreadedPool_handleIsEqual(void* USUSED, bbPool_Handle A, bbPool_Handle B);

#define bbThreadedPool_debug(pool) \
{\
bbThreadedPool* pool1 = (bbThreadedPool*)pool;\
bbDebug("head = %d, tail = %d\n", pool1->availableHead, pool1->availableTail);\
for (I32 i = 0; i < 20; i++) {\
bbThreadedPool_available* element;\
\
I32 offset = i * pool1->sizeOf;\
element = (bbThreadedPool_available*)&pool1->elements[offset];\
\
bbPrintf("prev = %d, index = %d, next = %d\n",element->prev, i, element->next);\
}\
bbPrintf("...\n\n");\
\
}\


#endif //BB_THREADED_POOL_H