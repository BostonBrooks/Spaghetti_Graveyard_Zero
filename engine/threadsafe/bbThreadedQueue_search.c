#include "engine/logic/bbTerminal.h"
#include "engine/threadsafe/bbTheadedQueue_search.h"

bbFlag bbThreadedQueue_removeUnsafe(bbThreadedQueue* queue, void* element) {

    bbPool_Handle elementHandle;
    bbPool_ListElement* list_element = element + queue->offsetOf;
    bbVPool_reverseLookup(queue->pool, element, &elementHandle);
    I32 elementInt = elementHandle.u64;

    //Case 1: only element
    if (queue->head == queue->tail) {
        bbAssert(queue->head == elementInt, "element not in list\n");

        bbAssert(
            bbVPool_handleIsEqual(queue->pool, list_element->prev, queue->pool->null) &&
            bbVPool_handleIsEqual(queue->pool, list_element->next, queue->pool->null),
            "weird bbPool_ListElement\n"
        );
        queue->head = -1;
        queue->tail = -1;

        list_element->prev = queue->pool->null;
        list_element->next = queue->pool->null;
        return Success;
    }
    //Case 2: first element
    if (queue->head == elementInt) {
        bbPool_Handle nextHandle = list_element->next;
        void* nextElement;
        bbVPool_lookup(queue->pool, &nextElement, nextHandle);
        bbPool_ListElement* nextListElement = nextElement + queue->offsetOf;
        nextListElement->prev = queue->pool->null;
        queue->head = nextHandle.u64;

        list_element->prev = queue->pool->null;
        list_element->next = queue->pool->null;
        return Success;
    }
    //Case 3: last element
    if (queue->tail == elementInt) {
        bbPool_Handle prevHandle = list_element->prev;
        void* prevElement;
        bbVPool_lookup(queue->pool, &prevElement, prevHandle);
        bbPool_ListElement* prevListElement = prevElement + queue->offsetOf;
        prevListElement->next = queue->pool->null;
        queue->tail = prevHandle.u64;

        list_element->prev = queue->pool->null;
        list_element->next = queue->pool->null;
        return Success;
    }
    //case 4: middle element
    bbPool_Handle prevHandle = list_element->prev;
    bbPool_Handle nextHandle = list_element->next;

    void* prevElement;
    void* nextElement;

    bbVPool_lookup(queue->pool, &prevElement, prevHandle);
    bbVPool_lookup(queue->pool, &nextElement, nextHandle);

    bbPool_ListElement* prevListElement = prevElement + queue->offsetOf;
    bbPool_ListElement* nextListElement = nextElement + queue->offsetOf;

    prevListElement->next = nextHandle;
    nextListElement->prev = prevHandle;

    list_element->prev = queue->pool->null;
    list_element->next = queue->pool->null;

    return Success;
}

bbFlag bbThreadedQueue_search(bbThreadedQueue* queue, void** Element, bbCallback* callback)
{
    bbMutexLock(&queue->mutex);

    //Case 1: Empty
    if (queue->head == -1 || queue->tail == -1)
    {
        bbAssert(queue->head == -1 && queue->tail == -1, "head/tail mismatch\n");
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
        bbPool_Handle handle2;
        handle2.ptr = element;

        bbFlag flag = bbCallback_execute(callback, handle2);

        if (flag == Success)
        {
            bbPool_ListElement* listElement = (element + queue->offsetOf);
            listElement->prev = queue->pool->null;
            listElement->next = queue->pool->null;
            queue->head = -1;
            queue->tail = -1;

            *Element = element;
            bbMutexUnlock(&queue->mutex);
            return Success;
        }

        *Element = NULL;
        bbMutexUnlock(&queue->mutex);
        return None;
    }

    //Case 3: More than one element

    I32 elementInt = queue->head;
    bbPool_Handle elementHandle;
    void* element;
    bbPool_ListElement* listElement;
    bbFlag flag;
    bbPool_Handle addressHandle;


    elementHandle.u64 = elementInt;
    bbVPool_lookup(queue->pool, &element, elementHandle);

    while (1)
    {

        addressHandle.ptr = element;
        bbFlag flag = bbCallback_execute(callback, addressHandle);

        if (flag == Success)
        {
            bbThreadedQueue_removeUnsafe(queue, element);
            *Element = element;
            bbMutexUnlock(&queue->mutex);
            return Success;

        }

        //update elementInt and return None if we reach the end

        bbPool_ListElement* listElement = (element + queue->offsetOf);
        bbPool_Handle nextHandle = listElement->next;
        if (bbVPool_handleIsEqual(queue->pool, nextHandle, queue->pool->null)) {
            return None;
        }
        bbVPool_lookup(queue->pool, &element, nextHandle);
    }

}