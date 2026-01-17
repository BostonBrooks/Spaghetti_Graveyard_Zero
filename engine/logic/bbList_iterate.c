#include "engine/logic/bbList.h"
#include "engine/logic/bbString.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbFlag.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>



#define isEqual(A, B) bbVPool_handleIsEqual(list->pool, A, B)
#define isNULL(A) bbVPool_handleIsEqual(list->pool, A, list->pool->null)

///point the iterator to the head of the list
bbFlag bbList_setHead(bbList* list, void** element){

    if(isNULL(list->listPtr->head)) return None;

    list->current = list->listPtr->head;
    list->prev = list->pool->null;
    list->next = list->pool->null;

    if (element!=NULL) {
        bbVPool_lookup(list->pool, element, list->current);
    }
    return Success;
}
///point the iterator to the tail of the list
bbFlag bbList_setTail(bbList* list, void** element){

    if(isNULL(list->listPtr->tail)) return None;

    list->current = list->listPtr->tail;
    list->prev = list->pool->null;
    list->next = list->pool->null;

    if (element!=NULL) {
        bbVPool_lookup(list->pool, element, list->current);
    }
    return Success;
}

bbFlag bbList_increment(bbList* list, void** element){

    //default case
    if(!isNULL(list->current)){

        //is current the tail of the list?
        if(isEqual(list->current, list->listPtr->tail)){
            //cannot increment, what do we do?
            return None;
        }

        void* current;
        bbVPool_lookup(list->pool, &current, list->current);
        bbPool_ListElement* currentList = current + list->offsetOf;

        list->current = currentList->next;
        list->prev = list->pool->null;
        list->next = list->pool->null;

        if (element!=NULL) {
            bbVPool_lookup(list->pool, element, list->current);
        }

        return Success;

    }
    // We must have removed the current element and all elements to the right
    if(isNULL(list->next)) return None;

    list->current = list->next;
    list->prev = list->pool->null;
    list->next = list->pool->null;

    if (element!=NULL) {
        bbVPool_lookup(list->pool, element, list->current);
    }

    return Success;

}

bbFlag bbList_decrement(bbList* list, void** element){

    //default case
    if(!isNULL(list->current)){

        //is current the tail of the list?
        if(isEqual(list->current, list->listPtr->head)){
            //cannot increment, what do we do?
            return None;
        }

        void* current;
        bbVPool_lookup(list->pool, &current, list->current);
        bbPool_ListElement* currentList = current + list->offsetOf;

        list->current = currentList->prev;
        list->prev = list->pool->null;
        list->next = list->pool->null;

        if (element!=NULL) {
            bbVPool_lookup(list->pool, element, list->current);
        }

        return Success;

    }
    // We must have removed the current element and all elements to the right
    if(isNULL(list->prev)) return None;

    list->current = list->prev;
    list->prev = list->pool->null;
    list->next = list->pool->null;

    if (element!=NULL) {
        bbVPool_lookup(list->pool, element, list->current);
    }

    return Success;

}

bbFlag bbList_getCurrent(bbList* list, void** element){
    if(isNULL(list->current)){
        *element = NULL;
        return None;
    }

    if (element!=NULL) {
        bbVPool_lookup(list->pool, element, list->current);
    }
}

bbFlag bbList_setCurrent(bbList* list, void* element){
    bbPool_Handle elementHandle;
    bbVPool_reverseLookup(list->pool, element, &elementHandle);

    list->current = elementHandle;
    list->prev = list->pool->null;
    list->next = list->pool->null;

    return Success;
}

//What was this supposed to do?
bbFlag bbList_popCurrent(bbList* list, void** element){
    void* Element;
    bbList_getCurrent(list, &Element);
    bbList_remove(list, Element);

    return Success;
}