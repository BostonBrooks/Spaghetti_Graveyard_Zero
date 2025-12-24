#include "bbThreadedQueue.h"

#include <stdlib.h>

#include "engine/logic/bbTerminal.h"

bbFlag bbThreadedQueue_init(bbThreadedQueue* queue, bbVPool* pool, I32 sizeOf, I32 num, I32 offsetOf)
{
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
    return Success;
}

bbFlag bbThreadedQueue_alloc(bbThreadedQueue* queue, void** element)
{
    pthread_mutex_lock(&queue->mutex);
    bbVPool_alloc(queue->pool, (void**)element);

    bbPool_ListElement* list_element = (*element + queue->offsetOf);
    list_element->prev = queue->pool->null;
    list_element->next = queue->pool->null;

    pthread_mutex_unlock(&queue->mutex);

    return Success;
}


bbFlag bbThreadedQueue_free(bbThreadedQueue* queue, void** element)
{
    pthread_mutex_lock(&queue->mutex);
    bbVPool_free(queue->pool, (void*)element);
    *element = NULL;
    pthread_mutex_unlock(&queue->mutex);

    return Success;
}


bbFlag bbThreadedQueue_pushL(bbThreadedQueue* queue, void* element)
{
    pthread_mutex_lock(&queue->mutex);

    bbFlag flag;
    bbPool_ListElement* list_element = element + queue->offsetOf;

    bbAssert(
        !bbVPool_handleIsEqual(queue->pool, queue->pool->null, list_element->prev)
        && !bbVPool_handleIsEqual(queue->pool, queue->pool->null, list_element->next),
        "Tried to push element already in a queue\n"
    );
    bbPool_Handle handle_element;
    flag = bbVPool_reverseLookup(queue->pool, element, &handle_element);

    if (queue->head == -1)
    {
        bbAssert(queue->tail == -1, "head/tail mismatch\n");

        queue->head = handle_element.u64;
        queue->tail = handle_element.u64;

        //I guess we're using null for endpoints of lists
        list_element->prev = queue->pool->null;
        list_element->next = queue->pool->null;

        pthread_mutex_unlock(&queue->mutex);
        return Success;
    }



    pthread_mutex_unlock(&queue->mutex);
}

