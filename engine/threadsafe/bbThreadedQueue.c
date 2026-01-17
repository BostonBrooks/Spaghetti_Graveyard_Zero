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
    pthread_mutex_init(&queue->empty, NULL);
    pthread_cond_init(&queue->emptyCond, NULL);
    return Success;
}

bbFlag bbThreadedQueue_alloc(bbThreadedQueue* queue, void** element)
{

    void* element1;
    bbVPool_alloc(queue->pool, (void**)&element1);

    bbPool_ListElement* list_element = (element1 + queue->offsetOf);

    list_element->prev = queue->pool->null;
    list_element->next = queue->pool->null;

   *element = element1;

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

    if (queue->head == -1 || queue->tail == -1)
    {
        bbAssert(queue->head == -1 && queue->tail == -1, "head/tail mismatch");

        queue->head = handle_element.u64;
        queue->tail = handle_element.u64;

        //I guess we're using null for endpoints of lists, IE not a circular list
        list_element->prev = queue->pool->null;
        list_element->next = queue->pool->null;

        bbMutexUnlock(&queue->mutex);


        pthread_cond_signal(&queue->emptyCond);
        pthread_mutex_unlock(&queue->empty);
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

    bbAssert( queue->head != -1 && queue->tail != -1, "head/tail error\n");

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

    if (queue->head == -1 || queue->tail == -1)
    {
        bbAssert(queue->head == -1 && queue->tail == -1, "head/tail mismatch");

        queue->head = handle_element.u64;
        queue->tail = handle_element.u64;

        //I guess we're using null for endpoints of lists, IE not a circular list
        list_element->prev = queue->pool->null;
        list_element->next = queue->pool->null;

        bbMutexUnlock(&queue->mutex);


        pthread_cond_signal(&queue->emptyCond);
        pthread_mutex_unlock(&queue->empty);
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

    if (queue->head == -1 || queue->tail == -1)
    {
        bbAssert(queue->head == -1 && queue->tail == -1, "head/tail mismatch");
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
 //   bbDebug("queue = %p, vPool = %p, Pool = %p\n", queue, pool, pool->pool);
    bbMutexLock(&queue->mutex);

    //Case 1: Empty

    if (queue->head == -1 || queue->tail == -1)
    {
        bbAssert(queue->head == -1 && queue->tail == -1, "head/tail mismatch");
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
//bbHere()
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


    prev_listElement->next = queue->pool->null;
    queue->tail = prev_handle.u64;

    *Element = tail_element;
    bbMutexUnlock(&queue->mutex);
    return Success;
}

bbFlag bbThreadedQueue_popRblock(bbThreadedQueue* queue, void** Element)
{
    bbVPool* pool = queue->pool;
 //   bbDebug("queue = %p, vPool = %p, Pool = %p\n", queue, pool, pool->pool);
    bbMutexLock(&queue->mutex);

    //Case 1: Empty

    if (queue->head == -1 || queue->tail == -1)
    {
        bbAssert(queue->head == -1 && queue->tail == -1, "head/tail mismatch");
        bbMutexUnlock(&queue->mutex);

        pthread_cond_wait(&queue->emptyCond, &queue->empty);

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
//bbHere()
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

    prev_listElement->next = queue->pool->null;
    queue->tail = prev_handle.u64;

    *Element = tail_element;
    bbMutexUnlock(&queue->mutex);
    return Success;
}

//Cases: empty, 1 element, more than 1 element;
bbFlag bbThreadedQueue_popLblock(bbThreadedQueue* queue, void** Element)
{
    bbMutexLock(&queue->mutex);

    //Case 1: Empty


    if (queue->head == -1 || queue->tail == -1)
    {
        bbAssert(queue->head == -1 && queue->tail == -1, "head/tail mismatch");
        bbMutexUnlock(&queue->mutex);
        pthread_cond_wait(&queue->emptyCond, &queue->empty);
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