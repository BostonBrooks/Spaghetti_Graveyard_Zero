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
				  I32 (*compare)(void* A, void* B)){

	bbList* List = malloc(sizeof(*list));
	bbAssert(NULL != list, "malloc failed\n");

	bbFlag flag = bbList_init(List, pool, listPtr, offsetOf, compare);

	*list = List;
	return flag;
}

bbFlag bbList_init(bbList* list, bbVPool* pool, void* listPtr, size_t offsetOf,
				   I32 (*compare)(void* A, void* B)){
	list->pool = pool;
    //listPtr is used to attach a bbList to an existing list
	if(listPtr != NULL){
		list->listPtr = listPtr;
	} else {
		list->listPtr = &list->list;
		list->list.head = pool->null;
		list->list.tail = pool->null;
	}
	list->offsetOf = offsetOf;
	list->compare = compare;
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

	//set element to tail
	if(isEqual(list->listPtr->head, list->listPtr->tail)){


		headListElement->next = handleElement;
		headListElement->prev = handleElement;
		listElement->next = list->listPtr->head;
		listElement->prev = list->listPtr->head;

		//list->listPtr->head = list->listPtr->tail; redundant?
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


bbFlag bbList_peakL(bbList* list, void** element)
{
	if (isNULL(list->listPtr->head))
	{
		*element = NULL;
		return None;
	}
	void* head;
	bbVPool_lookup(list->pool, &head, list->listPtr->head);
	//Handle edge cases?
	*element = head;
	return Success;
}

bbFlag bbList_peakR(bbList* list, void** element)
{
	if (isNULL(list->listPtr->tail))
	{
		*element = NULL;
		return None;
	}
	void* head;
	bbVPool_lookup(list->pool, &head, list->listPtr->tail);
	//Handle edge cases?
	*element = head;
	return Success;
}


I32 bbList_getLength(bbList* list){
	if(isNULL(list->listPtr->head)){
		bbAssert(isNULL(list->listPtr->tail), "head / tail mismatch\n");
		return 0;
	}

	if (isEqual(list->listPtr->head, list->listPtr->tail)){
		return 1;
	}
	I32 len = 2;
	bbPool_Handle handleElement = list->listPtr->head;
	void* element;
	bbVPool_lookup(list->pool, &element, handleElement);
	bbPool_ListElement* listElement = element + list->offsetOf;

	while (!isEqual(listElement->next, list->listPtr->tail)){
		handleElement = listElement->next;
		bbVPool_lookup(list->pool, &element, handleElement);
		listElement = element + list->offsetOf;
		len++;
	}
	return len;
}

bbFlag bbList_insertAfter(bbList* list, void* Node, void* Key){

    if (Key == NULL){
        bbList_pushR(list, Node);
        return Success;
    }

    bbPool_Handle NodeHandle;
    bbVPool_reverseLookup(list->pool, Node, &NodeHandle);
    bbPool_ListElement* NodeList = Node + list->offsetOf;

    bbPool_Handle KeyHandle;
    bbVPool_reverseLookup(list->pool, Key, &KeyHandle);
    bbPool_ListElement* KeyList = Key + list->offsetOf;

    bbPool_Handle NextHandle = KeyList->next;
    void* Next;
    bbVPool_lookup(list->pool, &Next, NextHandle);
    bbPool_ListElement* NextList = Next + list->offsetOf;

    KeyList->next = NodeHandle;
    NodeList->prev = KeyHandle;
    NodeList->next = NextHandle;
    NextList->prev = NodeHandle;

    if (isEqual(KeyHandle, list->listPtr->tail)){
        list->listPtr->tail = NodeHandle;
    }

    return Success;
}

bbFlag bbList_insertBefore(bbList* list, void* Node, void* Key){

    if (Key == NULL){
        bbList_pushL(list, Node);
        return Success;
    }
    bbPool_Handle NodeHandle;
    bbVPool_reverseLookup(list->pool, Node, &NodeHandle);
    bbPool_ListElement* NodeList = Node + list->offsetOf;

    bbPool_Handle KeyHandle;
    bbVPool_reverseLookup(list->pool, Key, &KeyHandle);
    bbPool_ListElement* KeyList = Key + list->offsetOf;

    bbPool_Handle PrevHandle = KeyList->prev;
    void* Prev;
    bbVPool_lookup(list->pool, &Prev, PrevHandle);
    bbPool_ListElement* PrevList = Prev + list->offsetOf;

    PrevList->next = NodeHandle;
    NodeList->prev = PrevHandle;
    NodeList->next = KeyHandle;
    KeyList->prev = NodeHandle;

    if(isEqual(KeyHandle, list->listPtr->head)){
        list->listPtr->head = NodeHandle;
    }

    return Success;
}

bbFlag bbList_remove(bbList* list, void* element){

    bbPool_Handle elementHandle;
    bbPool_ListElement* elementList = element + list->offsetOf;
    bbVPool_reverseLookup(list->pool, element, &elementHandle);

	//Since it's a circular list, if an element points to itself, it's the only element in the list.
    if (isEqual(elementHandle, elementList->next)){

        bbAssert(isEqual(elementHandle, elementList->prev)
                 && isEqual(elementHandle, list->listPtr->head)
                 && isEqual(elementHandle, list->listPtr->tail),
                 "all things being equal\n");
        elementList->next = list->pool->null;
        elementList->prev = list->pool->null;
        list->listPtr->head = list->pool->null;
        list->listPtr->tail = list->pool->null;

        list->prev = list->pool->null;
        list->current = list->pool->null;
        list->next = list->pool->null;

        return Success;

    }

	//The element before points to the element after and the element after points to the element before
    bbPool_Handle PrevHandle = elementList->prev;
    void* Prev;
    bbVPool_lookup(list->pool, &Prev, PrevHandle);
    bbPool_ListElement* PrevList = Prev + list->offsetOf;

    bbPool_Handle NextHandle = elementList->next;
    void* Next;
    bbVPool_lookup(list->pool, &Next, NextHandle);
    bbPool_ListElement* NextList = Next + list->offsetOf;

    NextList->prev = PrevHandle;
    PrevList->next = NextHandle;

	//An element not in a list points to null
    elementList->next = list->pool->null;
    elementList->prev = list->pool->null;


//remove an element from a list that's being iterated
    if(isEqual(elementHandle, list->current)){
        list->prev = PrevHandle;
        list->current = list->pool->null;
        list->next = NextHandle;
    } else if (isEqual(elementHandle, list->prev)){
        list->prev = PrevHandle;
    } else if (isEqual(elementHandle, list->next)){
        list->next = NextHandle;
    }

	//is element first or last element in the list
    if(isEqual(list->listPtr->head, elementHandle)){
        list->listPtr->head = NextHandle;
        list->prev = list->pool->null;
    } else if(isEqual(list->listPtr->tail, elementHandle)){
        list->listPtr->tail = PrevHandle;
        list->next = list->pool->null;
    }

    return Success;
}

bbFlag bbList_isEmpty(bbList* list){
    if (isNULL(list->listPtr->head)) return 1;
    return 0;
}


bbFlag bbList_alloc(bbList* list, void** element)
{
	void* lelement;
	bbFlag flag = bbVPool_alloc(list->pool, &lelement);
	if (flag == Success)
	{
		bbPool_ListElement* elementList = lelement + list->offsetOf;
		elementList->next = list->pool->null;
		elementList->prev = list->pool->null;
		*element = lelement;
	}
	return flag;
}