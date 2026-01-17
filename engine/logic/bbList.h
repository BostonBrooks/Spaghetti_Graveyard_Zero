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
 * compare had better return > or < and never ==
 * ie if A < B iff B > A
 *
 *
 */

#ifndef BBLIST_H
#define BBLIST_H

#include <stdlib.h>
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbFlag.h"


typedef struct {
    bbVPool* pool;
    //bbList can be attached to any bbPool_List

	/// listPtr allows a list to piggyback of another list
    bbPool_List* listPtr;
    //bbList can supply its own bbPool_List
    bbPool_List list;
    //offset of bbPool_ListElement from beginning of element
    size_t offsetOf;
    //TODO used to iterate through a list, looking at a particular sub-struct
    //size_t offsetOfInterest;

    I32 (*compare)(void* A, void* B);
	bbPool_Handle current;
	bbPool_Handle prev;
	bbPool_Handle next;
} bbList;
/*
bbPool_ListElement* getListElement (bbList list, void* element){
    return element + list.offsetOf;
}
*/
bbFlag bbList_init(bbList* list, bbVPool* pool, void* listPtr, size_t offsetOf,
				   I32 (*compare)(void* A, void* B));

bbFlag bbList_new(bbList** list, bbVPool* pool, void* listPtr, size_t offsetOf,
				   I32 (*compare)(void* A, void* B));

bbFlag bbList_pushL(bbList* list, void* element);
bbFlag bbList_pushR(bbList* list, void* element);

bbFlag bbList_popL(bbList* list, void** element);
bbFlag bbList_popR(bbList* list, void** element);

bbFlag bbList_sortL(bbList* list, void* element);
bbFlag bbList_sortR(bbList* list, void* element);


bbFlag bbList_peakL(bbList* list, void** element);
bbFlag bbList_peakR(bbList* list, void** element);

I32 bbList_getLength(bbList* list);
bbFlag bbList_sort(bbList* list);

///point the iterator to the head of the list
bbFlag bbList_setHead(bbList* list, void** element);
///point the iterator to the tail of the list
bbFlag bbList_setTail(bbList* list, void** element);

/// move the iterator to the right and return pointer by reference
bbFlag bbList_increment(bbList* list, void** element);
/// move the iterator to the left and return pointer by reference
bbFlag bbList_decrement(bbList* list, void** element);

/// return by reference, pointer to current location of iterator
bbFlag bbList_getCurrent(bbList* list, void** element);
/// point the iterator at element;
bbFlag bbList_setCurrent(bbList* list, void* element);

/// take the element and sort back into the list,
/// starting from it's current location
/// if element == current, this could be problematic, bbWarning
bbFlag bbList_sortElement(bbList* list, void* element);

// remove current object pointed to by iterator from list and return by ref
// store current.prev and current.next
//bbFlag bbList_popCurrent(bbList* list, void** element);

/// remove object from list
bbFlag bbList_remove(bbList* list, void* element);

bbFlag bbList_insertAfter(bbList* list, void* Node, void* Key);
bbFlag bbList_insertBefore(bbList* list, void* Node, void* Key);


typedef bbFlag bbListFunction(bbList* list, void* node, void* cl);
/// map function to list, going left-to-right
bbFlag bbList_mapL(bbList* list, bbListFunction* myFunc, void* cl);

/// map function to list, going right-to-left
bbFlag bbList_mapR(bbList* list, bbListFunction* myFunc, void* cl);

bbFlag bbList_isEmpty(bbList* list);

bbFlag bbList_alloc(bbList* list, void** element);

#endif //BBLIST_H