#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbPool.h"
#include "engine/logic/bbPriorityQueue.h"
#include "engine/logic/bbTerminal.h"
#include <stdlib.h>


/// Initialise priority queue and attach to pool
I32 bbPriorityQueue_newQueue(bbPriorityQueue** Queue,
                             bbPool_common* Pool,
                             bbPool_ListElement* (*get_List)(void*),
                             I32 (*is_Greater)(void*, void*)){
    //is this the correct idiom?
    bbPriorityQueue* queue = malloc(sizeof *queue);
    bbAssert(queue != NULL, "malloc failed\n");
    queue->pool = Pool;
    queue->list.head = Pool->null;
    queue->list.tail = Pool->null;
    queue->getList = get_List;
    queue->isGreater = is_Greater;

    *Queue = queue;

    return f_Success;

}

/// create a new element to put on priority queue
I32 bbPriorityQueue_new(bbPriorityQueue* queue,
                               void** address,
                               bbPool_Handle* handle)
{
    bbAssert(address!=NULL || handle!= NULL, "no return address");
    void* element;
    bbPool_Handle Handle;
    I32 flag;
    flag = bbPool_new(queue->pool, &element, &Handle);
    if (flag != f_Success) return flag;
    bbPool_ListElement* listElement = queue->getList(element);
    listElement->prev = queue->pool->null;
    listElement->next = queue->pool->null;

    if (address != NULL) *address = element;
    if (handle != NULL) *handle = Handle;

    return f_Success;


}


/// delete an element from priority queue, be careful if element is in two lists
I32 bbPriorityQueue_delete(bbPriorityQueue* queue,
                                  void* address,
                                  bbPool_Handle handle){
    bbPriorityQueue_remove(queue, address,handle);
    bbPool_delete(queue->pool, address, handle);

    return f_Success;
}

/// add an element to priority queue
I32 bbPriorityQueue_add(bbPriorityQueue* queue,
                                  void* address,
                                  bbPool_Handle handle){
    void* this = address;
    if (this == NULL){
        bbPool_lookup(queue->pool, &this, handle);
    }
}

/// remove an element from priority queue
I32 bbPriorityQueue_remove(bbPriorityQueue* queue,
                                  void* address,
                                  bbPool_Handle handle)
{
    I32 flag;
    void* this = address;

    if (this == NULL) {
        flag = bbPool_lookup(queue->pool, &this, handle);
        bbAssert(flag == f_Success, "bad flag");
    }

    bbPool_ListElement* thisList = queue->getList(this);

    if (thisList->prev == queue->pool->null
         && thisList->next == queue->pool->null){
        queue->list.head = queue->pool->null;
        queue->list.tail = queue->pool->null;
        thisList->prev = queue->pool->null;
        thisList->next = queue->pool->null;
        return f_Success;
    }
    if (thisList->prev == queue->pool->null){
        //thisList->next != null
        void* next;
        flag = bbPool_lookup(queue->pool, &next, thisList->next);
        bbAssert(flag == f_Success, "bad flag\n");
        bbPool_ListElement* nextList = queue->getList(next);

        nextList->prev = queue->pool->null;
        queue->list.head = thisList->next;
        thisList->prev = queue->pool->null;
        thisList->next = queue->pool->null;
        return f_Success;
    }
    if (thisList->next == queue->pool->null){
        //thisList->prev != null
        void* prev;
        flag = bbPool_lookup(queue->pool, &prev, thisList->prev);
        bbAssert(flag == f_Success, "bad flag\n");
        bbPool_ListElement* prevList = queue->getList(prev);

        prevList->next = queue->pool->null;
        queue->list.tail = thisList->prev;
        thisList->prev = queue->pool->null;
        thisList->next = queue->pool->null;
        return f_Success;
    }
    // thisList->prev != null && thisList->next != null
    void* prev;
    flag = bbPool_lookup(queue->pool, &prev, thisList->prev);
    bbAssert(flag == f_Success, "bad flag\n");
    void* next;
    flag = bbPool_lookup(queue->pool, &next, thisList->next);
    bbAssert(flag == f_Success, "bad flag\n");

    bbPool_ListElement* prevList = queue->getList(prev);
    bbPool_ListElement* nextList = queue->getList(next);

    prevList->next = thisList->next;
    nextList->prev = thisList->prev;
    thisList->prev = queue->pool->null;
    thisList->next = queue->pool->null;

    return f_Success;
}

/// re-sort an element in priority queue
I32 bbPriorityQueue_resort(bbPriorityQueue* queue,
                                  void* address,
                                  bbPool_Handle handle);

/// return the address of an element given its handle, or NULL
/// just a wrapper fo bbPool_lookup
I32 bbPriorityQueue_lookup(bbPriorityQueue* queue,
                                  void** address,
                                  bbPool_Handle handle){
    return bbPool_lookup(queue->pool, address, handle);
}
/// return the handle of an element given its address
/// just a wrapper fo bbPool_reverseLookup
I32 bbPriorityQueue_reverseLookup(bbPriorityQueue* queue,
                                         void* address,
                                         bbPool_Handle* handle){
    return bbPool_reverseLookup(queue->pool, address, handle);
}


/// the whole point of having a priority queue
I32 bbPriorityQueue_getNext(bbPriorityQueue* queue,
                            void* address, bbPool_Handle handle,
                            void** nextAddress, bbPool_Handle* nextHandle);

/// the whole point of having a priority queue
I32 bbPriorityQueue_getPrev(bbPriorityQueue* queue,
                            void* address, bbPool_Handle handle,
                            void** prevAddress, bbPool_Handle* prevHandle);