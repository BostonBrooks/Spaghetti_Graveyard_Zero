#include "engine/logic/bbTerminal.h"
#include "engine/threadsafe/bbTheadedQueue_search.h"


bbFlag bbThreadedQueue_search(bbThreadedQueue* queue, void** Element, bbCallback* callback)
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

    while (1)
    {
        elementHandle.u64 = elementInt;
        bbFlag flag = bbCallback_execute(callback, elementHandle);

        if (flag == Success)
        {
            //pop element
        }

        //update elementInt and return None if we reach the end
    }

}