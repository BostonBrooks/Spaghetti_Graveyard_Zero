#ifndef BB_THREADED_QUEUE_H
#define BB_THREADED_QUEUE_H

#include <pthread.h>
#include "engine/logic/bbVPool.h"

//elements must contain bbPool_ListElement at offsetOf

typedef struct
{
    bbVPool* pool;
    pthread_mutex_t mutex;
    I32 head;
    I32 tail;
    I32 offsetOf;



} bbThreadedQueue;



///Init in place, create new pool if pool == NULL
bbFlag bbThreadedQueue_init(bbThreadedQueue* queue, bbVPool* pool, I32 sizeOf, I32 num, I32 offsetOf);

///malloc then init
bbFlag bbThreadedQueue_new(bbThreadedQueue** queue, bbVPool* pool, I32 sizeOf, I32 num, I32 offsetOf);
///delete queue without deleting it's pool
bbFlag bbThreadedQueue_delete(bbThreadedQueue* queue);
///delete queue and it's pool
bbFlag bbThreadedQueue_deletePool(bbThreadedQueue* queue);

bbFlag bbThreadedQueue_alloc(bbThreadedQueue* queue, void** element);
bbFlag bbThreadedQueue_free(bbThreadedQueue* queue, void** element);
bbFlag bbThreadedQueue_pushL(bbThreadedQueue* queue, void* element);
bbFlag bbThreadedQueue_pushR(bbThreadedQueue* queue, void* element);
bbFlag bbThreadedQueue_popL(bbThreadedQueue* queue, void** element);
bbFlag bbThreadedQueue_popR(bbThreadedQueue* queue, void** element);


#endif //BB_THREADED_QUEUE_H
