#include "bbThreadedQueue.h"

#include <stdlib.h>

#include "engine/logic/bbTerminal.h"

bbFlag bbThreadedQueue_init(bbThreadedQueue** self, bbVPool* pool, I32 sizeOf, I32 num, I32 offsetOf)
{
    bbThreadedQueue* queue = malloc(sizeof(bbThreadedQueue));
    bbAssert(queue != NULL, "bad malloc\n");

    if (pool == NULL)
    {
        bbVPool_newThreaded(&queue->pool, sizeOf, num);
    }
    else
    {
        queue->pool = (bbVPool*)pool;
    }


    queue->head = -1;
    queue->tail = -1;
    queue->offsetOf = offsetOf;


    pthread_mutex_init(&queue->mutex, NULL);
    *self = (bbThreadedQueue*)queue;
    return Success;
}

bbFlag bbThreadedQueue_alloc(bbThreadedQueue* queue, void** element)
{
    pthread_mutex_lock(&queue->mutex);
    bbVPool_alloc(queue->pool, (void**)element);
    pthread_mutex_unlock(&queue->mutex);

    return Success;
}


bbFlag bbThreadedQueue_free(bbThreadedQueue* queue, void* element)
{
    pthread_mutex_lock(&queue->mutex);
    bbVPool_free(queue->pool, (void*)element);
    pthread_mutex_unlock(&queue->mutex);

    return Success;
}


bbFlag bbThreadedQueue_pushL(bbThreadedQueue* queue, void* element)
{
    pthread_mutex_lock(&queue->mutex);


}

