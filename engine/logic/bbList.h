/**
 * @file
 * @brief I use a lot of double-ly linked lists
 *
 * what can you do with a list?
 *
 * - push and pop left and right
 * - push and pop left and right but the list remains sorted
 * - iterate back and forth through the list.
 * - reset the iterator
 * - access the object pointed to by the iterator
 * - pop the object pointed to by the iterator
 * - after modifying object, sort back into list
 *
 * - insert object before or after another object, including the one pointed
 * to by iterator
 *
 * NOTE: if you take the object pointed to by the iterator, modify it, sort it
 * back in to the list, then continue iterating through the list, you might
 * come across the same object again! its not too big of a problem, but might
 * need to guard against
 *
 * comparator had better return > or < and never ==
 * ie if A < B iff B > A
 */
#include <stdlib.h>
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbFlag.h"


typedef struct {
    bbVPool* pool;
    //bbList can be attached to any bbPool_List
    bbPool_List* listPtr;
    //bbList can supply its own bbPool_List
    bbPool_List list;
    //offset of bbPool_ListElement from beginning of element
    size_t offsetOf;
    bbPool_Handle prev;
    bbPool_Handle self;
    bbPool_Handle next;
    I32 (*comparator)(bbPool_Handle A, bbPool_Handle B);
} bbList;

bbPool_ListElement* getListElement (bbList list, void* element){
    return element + list.offsetOf;
}

bbFlag bbList_pushL(bbList* list, void* element);
bbFlag bbList_pushR(bbList* list, void* element);

bbFlag bbList_popL(bbList* list, void** element);
bbFlag bbList_popR(bbList* list, void** element);

bbFlag bbList_sortL(bbList* list, void* element);
bbFlag bbList_sortR(bbList* list, void* element);

///point the iterator to the head of the list
bbFlag bbList_setHead(bbList* list);
///point the iterator to the tail of the list
bbFlag bbList_setTail(bbList* list);

/// move the iterator to the right and return pointer by reference
bbFlag bbList_increment(bbList* list, void** element);
/// move the iterator to the left and return pointer by reference
bbFlag bbList_decrement(bbList* list, void** element);

/// return by reference, pointer to current location of iterator
bbFlag bbList_getCurrent(bbList* list, void** element);
/// point the iterator at element;
bbFlag bbList_setCurrent(bbList* list, void* element);
/// take the current object pointed to by iterator and sort back into the list
bbFlag bbList_sortCurrent(bbList* list, void* element);

/// remove current object pointed to by iterator from list and return by ref
bbFlag bbList_popCurrent(bbList* list, void** element);
/// remove object from list
bbFlag bbList_remove(bbList* list, void* element);

bbFlag bbList_insertAfter(bbList* list, void* A, void* B);
bbFlag bbList_insertBefore(bbList* list, void* B, void* A);

//bbList is empty?

//bbList may be an element of an existing struct
bbFlag bbList_init(bbList* list, bbVPool* pool, void* listPtr, size_t offsetof,
                  I32 (*comparator)(bbPool_Handle A, bbPool_Handle B)){
    list->pool = pool;
    list->listPtr = listPtr;
    list->list.head = pool->null;
    list->list.tail = pool->null;
    list->offsetOf = offsetof;

    if (list->listPtr != NULL){
        list->prev = pool->null;
        list->self = list->listPtr->head;

    }

    list->comparator = comparator;
}

//bbList may be placed on the heap
bbFlag bbList_new(void* pool, void* listPtr, size_t offsetof,
                  I32 (*comparator)(bbPool_Handle A, bbPool_Handle B)){
    bbList* list = malloc(sizeof *list);
    return bbList_init(list, pool, listPtr, offsetof, comparator);
}