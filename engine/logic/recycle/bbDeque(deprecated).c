#include "bbDeque.h"
#include "engine/logic/bbTerminal.h"
#include <stdlib.h>



I32 bbDeque_newDeque(void** deque, I32 sizeOf, I32 level1, I32 level2, I32 map){

    bbDeque* Deque = malloc (sizeof (bbDeque));
    bbDequePool_newPool(&Deque->p_pool, sizeOf, level1, level2, map);
    Deque->p_head = bbDequePool_NULL;
    Deque->p_tail = bbDequePool_NULL;

    return f_Success;
}

I32 bbDeque_deleteDeque(void* deque){
    bbDeque* Deque = deque;
    bbDequePool_deletePool(Deque->p_pool);
    free(deque);
    return f_Success;
}

I32 bbDeque_clearDeque(void* deque){
    bbDeque* Deque = deque;
    bbDequePool_clearPool(Deque->p_pool);
    Deque->p_head = bbDequePool_NULL;
    Deque->p_tail = bbDequePool_NULL;
    return f_Success;
}

I32 bbDeque_new(void* deque, void** element){
    bbDeque* Deque = deque;
    bbDeque_Element* Element;
    I32 flag = bbDequePool_newA(Deque->p_pool, &Element);
    bbAssert(flag = f_Success, "pool for in bbDeque_new\n");
    Element->p_prev = bbDequePool_NULL;
    Element->p_next = bbDequePool_NULL;
    Element->p_InUse = 0;

    *element = Element;

}


I32 bbDeque_delete(void* deque, void* element){
    bbDeque* Deque = deque;
    bbDeque_Element* Element = element;
    bbDeque_Element* prev;
    bbDeque_Element* next;
    bbDequePool_getAddress(Deque->p_pool, &prev, Element->p_prev);
    bbDequePool_getAddress(Deque->p_pool, &next, Element->p_next);

    //if element not in list
    if (Element->p_InUse == 0){
        bbDequePool_deleteA(Deque->p_pool, Element);
        return f_Success;
    }
    //if lone element in list
    if (prev == NULL && next == NULL){
        //assert deque->head & deque->tail bbFastPool_HeaderIsNULL()
        Deque->p_head = bbDequePool_NULL;
        Deque->p_tail = bbDequePool_NULL;

        bbDequePool_deleteA (Deque->p_pool, Element);
        return f_Success;
    }
    // element at head
    if (prev == NULL){
        //assert deque->head == element.handle
        Deque->p_head = Element->p_next;
        next->p_prev = bbDequePool_NULL;

        bbDequePool_deleteA(Deque->p_pool, Element);
        return f_Success;
    }
    // element at tail
    if (next == NULL){
        //assert deque->tail == element.handle
        Deque->p_tail = Element->p_prev;
        prev->p_next = bbDequePool_NULL;

        bbDequePool_deleteA(Deque->p_pool, Element);
        return f_Success;
    }

    // element in middle of list

    prev->p_next = Element->p_next;
    next->p_prev = Element->p_prev;

    bbDequePool_deleteA(Deque->p_pool, Element);

}


I32 bbDeque_pushHead(void* deque, void* element){
    bbDeque* Deque = deque;
    bbDeque_Element* Element = element;

    bbAssert(Element->p_prev == bbDequePool_NULL && Element->p_next ==
            bbDequePool_NULL && Element->p_InUse == 0,
            "object already in list\n");
}

I32 bbDeque_popHead(void* deque, void** element){

}

I32 bbDeque_pushTail(void* deque, void* element){

}

I32 bbDeque_popTail(void* deque, void** element){

}