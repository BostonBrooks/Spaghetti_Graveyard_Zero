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


typedef struct
{
    I32 prev;
    I32 next;
} bbThreadedPool_unused;

typedef struct
{
    bbPool_Handle null;
    I32 num;
    I32 sizeOf;
    I32 inUse;
    I32 availableHead;
    I32 availableTail;
    pthread_mutex_t mutex;
    alignas(8) U8 elements[];
} bbThreadedPool;

#define bbThreadedPool_alloc(pool, address)\
bbThreadedPool_allocImpl(pool, address, NULL, 0);

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

#endif //BB_THREADED_POOL_H