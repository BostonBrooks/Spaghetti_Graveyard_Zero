#include "bbThreadedQueue.h"

#include <stdlib.h>

#include "bbThreadedPool.h"
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

    //bbMutexLock(&queue->mutex);
    bbVPool_alloc(queue->pool, (void**)element);


    bbPool_ListElement* list_element = (*element + queue->offsetOf);
    list_element->prev = queue->pool->null;
    list_element->next = queue->pool->null;

   // bbMutexUnlock(&queue->mutex);

    return Success;
}


bbFlag bbThreadedQueue_free(bbThreadedQueue* queue, void** element)
{
    //bbMutexLock(&queue->mutex);
    bbVPool_free(queue->pool, (void*)*element);
    *element = NULL;
    //bbMutexUnlock(&queue->mutex);

    return Success;
}


bbFlag bbThreadedQueue_pushL(bbThreadedQueue* queue, void* element)
{
    //what if, as a protection, bbThreadedQueue_pushL sets element to NULL
    bbMutexLock(&queue->mutex);

    bbFlag flag;
    bbPool_ListElement* list_element = element + queue->offsetOf;

    bbAssert(
        bbVPool_handleIsEqual(queue->pool, queue->pool->null, list_element->prev)
        && bbVPool_handleIsEqual(queue->pool, queue->pool->null, list_element->next),
        "Tried to push element already in a queue\n"
    );
    bbPool_Handle handle_element;
    flag = bbVPool_reverseLookup(queue->pool, element, &handle_element);

    if (queue->head == -1)
    {
        bbAssert(queue->tail == -1, "head/tail mismatch\n");

        queue->head = handle_element.u64;
        queue->tail = handle_element.u64;

        //I guess we're using null for endpoints of lists, IE not a circular list
        list_element->prev = queue->pool->null;
        list_element->next = queue->pool->null;

        bbMutexUnlock(&queue->mutex);
        return Success;
    }

    void* head; bbPool_Handle headhandle;
    headhandle.u64 = queue->head;
    bbVPool_lookup(queue->pool, &head, headhandle);
    bbPool_ListElement* head_listElement = (head + queue->offsetOf);

    list_element->prev = queue->pool->null;
    list_element->next = headhandle;

    head_listElement->prev = handle_element;
    queue->head = handle_element.u64;

    bbMutexUnlock(&queue->mutex);
    return Success;
}

bbFlag bbThreadedQueue_pushR(bbThreadedQueue* queue, void* element)
{
    //what if, as a protection, bbThreadedQueue_pushL sets element to NULL
    bbMutexLock(&queue->mutex);

    bbFlag flag;
    bbPool_ListElement* list_element = element + queue->offsetOf;

    bbAssert(
        bbVPool_handleIsEqual(queue->pool, queue->pool->null, list_element->prev)
        && bbVPool_handleIsEqual(queue->pool, queue->pool->null, list_element->next),
        "Tried to push element already in a queue\n"
    );
    bbPool_Handle handle_element;
    flag = bbVPool_reverseLookup(queue->pool, element, &handle_element);

    if (queue->head == -1)
    {
        bbAssert(queue->tail == -1, "head/tail mismatch\n");

        queue->head = handle_element.u64;
        queue->tail = handle_element.u64;

        //I guess we're using null for endpoints of lists, IE not a circular list
        list_element->prev = queue->pool->null;
        list_element->next = queue->pool->null;

        bbMutexUnlock(&queue->mutex);
        return Success;
    }

    void* tail; bbPool_Handle tailhandle;
    tailhandle.u64 = queue->tail;
    bbVPool_lookup(queue->pool, &tail, tailhandle);
    bbPool_ListElement* tail_listElement = (tail + queue->offsetOf);

    list_element->next = queue->pool->null;
    list_element->prev = tailhandle;

    tail_listElement->next = handle_element;
    queue->tail = handle_element.u64;

    bbMutexUnlock(&queue->mutex);
    return Success;
}

//Cases: empty, 1 element, more than 1 element;
bbFlag bbThreadedQueue_popL(bbThreadedQueue* queue, void** Element)
{
    bbMutexLock(&queue->mutex);

    //Case 1: Empty

    if (queue->head == -1)
    {
        bbAssert(queue->tail == -1, "head/tail mismatch");
        *Element = NULL;
        bbMutexUnlock(&queue->mutex);
        return None;
    }

    //Case 2: One Element

    if (queue->head == queue->tail)
    {
        bbPool_Handle handle;
        handle.u64 = queue->head;
        void* element;
        bbVPool_lookup(queue->pool, &element, handle);
        bbPool_ListElement* listElement = (element + queue->offsetOf);
        listElement->prev = queue->pool->null;
        listElement->next = queue->pool->null;
        queue->head = -1;
        queue->tail = -1;

        *Element = element;
        bbMutexUnlock(&queue->mutex);
        return Success;
    }

    //Case 3: More than one element
    bbPool_Handle head_handle;
    head_handle.u64 = queue->head;
    void* head_element;
    bbVPool_lookup(queue->pool, &head_element, head_handle);
    bbPool_ListElement* head_listElement = (head_element + queue->offsetOf);

    void* next_element;
    bbVPool_lookup(queue->pool, &next_element, head_listElement->next);
    bbPool_ListElement* next_listElement = (next_element + queue->offsetOf);
    bbPool_Handle next_handle;
    bbVPool_reverseLookup(queue->pool, next_element, &next_handle);

    head_listElement->prev = queue->pool->null;
    head_listElement->next = queue->pool->null;

    next_listElement->prev = queue->pool->null;
    queue->head = next_handle.u64;

    *Element = head_element;
    bbMutexUnlock(&queue->mutex);
    return Success;
}
//Cases: empty, 1 element, more than 1 element;
__attribute__((no_sanitize("address")))
bbFlag bbThreadedQueue_popR(bbThreadedQueue* queue, void** Element)
{
    bbVPool* pool = queue->pool;
    bbDebug("queue = %p, vPool = %p, Pool = %p\n", queue, pool, pool->pool);
    bbMutexLock(&queue->mutex);

    //Case 1: Empty

    if (queue->head == -1)
    {
        bbAssert(queue->tail == -1, "head/tail mismatch");
        *Element = NULL;
        bbMutexUnlock(&queue->mutex);
        return None;
    }

    //Case 2: One Element

    if (queue->head == queue->tail)
    {
        bbPool_Handle handle;
        handle.u64 = queue->head;
        void* element;
        bbVPool_lookup(queue->pool, &element, handle);
        bbPool_ListElement* listElement = (element + queue->offsetOf);
        listElement->prev = queue->pool->null;
        listElement->next = queue->pool->null;
        queue->head = -1;
        queue->tail = -1;

        *Element = element;
        bbMutexUnlock(&queue->mutex);
        return Success;
    }

    //Case 3: More than one element
bbHere()
    bbPool_Handle tail_handle;
    tail_handle.u64 = queue->tail;
    void* tail_element;
    bbVPool_lookup(queue->pool, &tail_element, tail_handle);
    bbPool_ListElement* tail_listElement = (tail_element + queue->offsetOf);

    void* prev_element;
    bbVPool_lookup(queue->pool, &prev_element, tail_listElement->prev);
    bbPool_ListElement* prev_listElement = (tail_listElement + queue->offsetOf);
    bbPool_Handle prev_handle;
    bbVPool_reverseLookup(queue->pool, prev_element, &prev_handle);

    tail_listElement->prev = queue->pool->null;
    tail_listElement->next = queue->pool->null;

    /* test - Test passes index = 1, offsetof = 64, offset_int_pool = 160

    bbPool_Handle test_handle;
    bbThreadedPool* threaded_pool = queue->pool->pool;
    bbVPool_reverseLookup(queue->pool, prev_listElement - queue->offsetOf, &test_handle);
    bbDebug("index = %d, offsetof = %d, sizeOf = %d, offset_in_pool = %llu\n",
        test_handle.u64, queue->offsetOf, threaded_pool->sizeOf,  (U64)prev_element - (U64)queue->pool->pool);
    bbDebug("tail_listElement address = %p,\n       prev_listElement address = %p\n", tail_listElement, prev_listElement);
     //end test - why does the below line buffer-overflow when the index is within bounds?
     Have switched off address sanitisation for this function*/

    prev_listElement->next = queue->pool->null;
    queue->tail = prev_handle.u64;

    *Element = tail_element;
    bbMutexUnlock(&queue->mutex);
    return Success;
}