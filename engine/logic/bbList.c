#include "engine/logic/bbList.h"
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbTerminal.h"

// implements circular doubly linked list.
// uses head/tail in bbPool_List
// head.prev = tail, tail.next = head

#define isEqual(A, B) bbVPool_handleIsEqual(list->pool, A, B)
#define isNULL(A) bbVPool_handleIsEqual(list->pool, A, list->pool->null)

bbFlag bbList_new(bbList** list, bbVPool* pool, void* listPtr, size_t offsetOf,
				  I32 (*comparator)(bbPool_Handle A, bbPool_Handle B)){

	bbList* List = malloc(sizeof(*list));
	bbAssert(NULL != list, "malloc failed\n");

	bbFlag flag = bbList_init(List, pool, listPtr, offsetOf, comparator);

	*list = List;
	return flag;
}

bbFlag bbList_init(bbList* list, bbVPool* pool, void* listPtr, size_t offsetOf,
				   I32 (*comparator)(bbPool_Handle A, bbPool_Handle B)){
	list->pool = pool;
	if(listPtr != NULL){
		list->listPtr = listPtr;
	} else {
		list->listPtr = &list->list;
		list->list.head = pool->null;
		list->list.tail = pool->null;
	}
	list->offsetOf = offsetOf;
	list->comparator = comparator;
	list->prev = list->pool->null;
	list->current = list->pool->null;
	list->next = list->pool->null;

	return Success;
}

//TODO modify current, prev, next
bbFlag bbList_pushL(bbList* list, void* element){
	//cases: empty list / 1 element list / other

	bbPool_ListElement* listElement = element + list->offsetOf;
	bbPool_Handle handleElement;
	bbVPool_reverseLookup(list->pool, element, &handleElement);

	bbAssert(isNULL(listElement->prev), "already in a list\n");
	bbAssert(isNULL(listElement->next), "already in a list\n");

	//set element to only member of list
	if(isNULL(list->listPtr->head)){
		bbAssert(isNULL(list->listPtr->head), "head/tail mismatch\n");
		listElement->prev = handleElement;
		listElement->next = handleElement;
		list->listPtr->head = handleElement;
		list->listPtr->tail = handleElement;

		return Success;
	}

	void* head;
	bbVPool_lookup(list->pool, &head, list->listPtr->head);
	bbPool_ListElement* headListElement = head + list->offsetOf;

	//set element to head, head to tail
	if(isEqual(list->listPtr->head, list->listPtr->tail)){


		headListElement->next = handleElement;
		headListElement->prev = handleElement;
		listElement->next = list->listPtr->head;
		listElement->prev = list->listPtr->head;

		list->listPtr->tail = list->listPtr->head;
		list->listPtr->head = handleElement;

		return Success;

	}
	//insert between head and tail and update head
	void* tail;
	bbVPool_lookup(list->pool, &tail, list->listPtr->tail);
	bbPool_ListElement* tailListElement = tail + list->offsetOf;

	tailListElement->next = handleElement;
	headListElement->prev = handleElement;
	listElement->prev = list->listPtr->tail;
	listElement->next = list->listPtr->head;
	list->listPtr->head = handleElement;

	return Success;
}

//TODO modify current, prev, next
bbFlag bbList_pushR(bbList* list, void* element){
	//cases: empty list / 1 element list / other

	bbPool_ListElement* listElement = element + list->offsetOf;
	bbPool_Handle handleElement;
	bbVPool_reverseLookup(list->pool, element, &handleElement);

	bbAssert(isNULL(listElement->prev), "already in a list\n");
	bbAssert(isNULL(listElement->next), "already in a list\n");

	//set element to only member of list
	if(isNULL(list->listPtr->head)){
		bbAssert(isNULL(list->listPtr->head), "head/tail mismatch\n");
		listElement->prev = handleElement;
		listElement->next = handleElement;
		list->listPtr->head = handleElement;
		list->listPtr->tail = handleElement;

		return Success;
	}

	void* head;
	bbVPool_lookup(list->pool, &head, list->listPtr->head);
	bbPool_ListElement* headListElement = head + list->offsetOf;

	//set element to tail, tail to head
	if(isEqual(list->listPtr->head, list->listPtr->tail)){


		headListElement->next = handleElement;
		headListElement->prev = handleElement;
		listElement->next = list->listPtr->head;
		listElement->prev = list->listPtr->head;

		list->listPtr->head = list->listPtr->tail;
		list->listPtr->tail = handleElement;

		return Success;

	}
	//insert between head and tail and update tail
	void* tail;
	bbVPool_lookup(list->pool, &tail, list->listPtr->tail);
	bbPool_ListElement* tailListElement = tail + list->offsetOf;

	tailListElement->next = handleElement;
	headListElement->prev = handleElement;
	listElement->prev = list->listPtr->tail;
	listElement->next = list->listPtr->head;
	list->listPtr->tail = handleElement;

	return Success;
}

//TODO modify current, prev, next
bbFlag bbList_popL(bbList* list, void** element){
	//cases: empty, 1 element, more than 1 element;
	if (isNULL(list->listPtr->head)){
		bbAssert(isNULL(list->listPtr->tail), "head / tail mismatch");
		if (element != NULL){
			*element = NULL;
		}
		return None;
	}

	void* head;
	bbVPool_lookup(list->pool, &head, list->listPtr->head);
	bbPool_ListElement* headListElement = head + list->offsetOf;

	if(isEqual(list->listPtr->head, list->listPtr->tail)){
		bbAssert(isEqual(list->listPtr->head, headListElement->prev), "\n");
		bbAssert(isEqual(list->listPtr->head, headListElement->next), "\n");

		list->listPtr->head = list->pool->null;
		list->listPtr->tail = list->pool->null;
		headListElement->prev = list->pool->null;
		headListElement->next = list->pool->null;
		if (element != NULL){
			*element = head;
		}
		return Success;
	}
	void* prev;
	bbVPool_lookup(list->pool, &prev, headListElement->prev);
	bbPool_ListElement* prevListElement = prev + list->offsetOf;

	void* next;
	bbVPool_lookup(list->pool, &next, headListElement->next);
	bbPool_ListElement* nextListElement = next + list->offsetOf;

	prevListElement->next = headListElement->next;
	nextListElement->prev = headListElement->prev;
	list->listPtr->head = headListElement->next;

	headListElement->prev = list->pool->null;
	headListElement->next = list->pool->null;

	if (element != NULL){
		*element = head;
	}
	return Success;
}

bbFlag bbList_popR(bbList* list, void** element){

	//cases: empty, 1 element, more than 1 element;
	if (isNULL(list->listPtr->head)){
		bbAssert(isNULL(list->listPtr->tail), "head / tail mismatch");
		if (element != NULL){
			*element = NULL;
		}
		return None;
	}

	void* tail;
	bbVPool_lookup(list->pool, &tail, list->listPtr->tail);
	bbPool_ListElement* tailListElement = tail + list->offsetOf;

	if(isEqual(list->listPtr->head, list->listPtr->tail)){
		bbAssert(isEqual(list->listPtr->tail, tailListElement->prev), "\n");
		bbAssert(isEqual(list->listPtr->tail, tailListElement->next), "\n");

		list->listPtr->head = list->pool->null;
		list->listPtr->tail = list->pool->null;
		tailListElement->prev = list->pool->null;
		tailListElement->next = list->pool->null;
		if (element != NULL){
			*element = tail;
		}
		return Success;
	}

	void* prev;
	bbVPool_lookup(list->pool, &prev, tailListElement->prev);
	bbPool_ListElement* prevListElement = prev + list->offsetOf;

	void* next;
	bbVPool_lookup(list->pool, &next, tailListElement->next);
	bbPool_ListElement* nextListElement = next + list->offsetOf;

	prevListElement->next = tailListElement->next;
	nextListElement->prev = tailListElement->prev;
	list->listPtr->tail = tailListElement->prev;

	tailListElement->prev = list->pool->null;
	tailListElement->next = list->pool->null;

	if (element != NULL){
		*element = tail;
	}
	return Success;
}