#include "engine/logic/bbList.h"
#include "engine/logic/bbString.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbFlag.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


#define isEqual(A, B) bbVPool_handleIsEqual(list->pool, A, B)
#define isNULL(A) bbVPool_handleIsEqual(list->pool, A, list->pool->null)

bbFlag popL (bbList* list, void** element, bbPool_List* tmpList){
	//cases: empty, 1 element, more than 1 element;
	if (isNULL(tmpList->head)){
		bbAssert(isNULL(tmpList->tail), "head / tail mismatch");
		if (element != NULL){
			*element = NULL;
		}
		return None;
	}

	void* head;
	bbVPool_lookup(list->pool, &head, tmpList->head);
	bbPool_ListElement* headListElement = head + list->offsetOf;

	if(isEqual(tmpList->head, tmpList->tail)){
		bbAssert(isEqual(tmpList->head, headListElement->prev), "\n");
		bbAssert(isEqual(tmpList->head, headListElement->next), "\n");

		tmpList->head = list->pool->null;
		tmpList->tail = list->pool->null;
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
	tmpList->head = headListElement->next;

	headListElement->prev = list->pool->null;
	headListElement->next = list->pool->null;

	if (element != NULL){
		*element = head;

	}
	return Success;
}


bbFlag pushR(bbList* list, void* element, bbPool_List* tmpList){
	//cases: empty list / 1 element list / other

	bbPool_ListElement* listElement = element + list->offsetOf;
	bbPool_Handle handleElement;
	bbVPool_reverseLookup(list->pool, element, &handleElement);

	bbAssert(isNULL(listElement->prev), "already in a list\n");
	bbAssert(isNULL(listElement->next), "already in a list\n");

	//set element to only member of list
	if(isNULL(tmpList->head)){
		bbAssert(isNULL(tmpList->head), "head/tail mismatch\n");
		listElement->prev = handleElement;
		listElement->next = handleElement;
		tmpList->head = handleElement;
		tmpList->tail = handleElement;

		return Success;
	}

	void* head;
	bbVPool_lookup(list->pool, &head, tmpList->head);
	bbPool_ListElement* headListElement = head + list->offsetOf;

	//set element to tail, tail to head
	if(isEqual(tmpList->head, tmpList->tail)){


		headListElement->next = handleElement;
		headListElement->prev = handleElement;
		listElement->next = tmpList->head;
		listElement->prev = tmpList->head;

		tmpList->head = tmpList->tail;
		tmpList->tail = handleElement;

		return Success;

	}
	//insert between head and tail and update tail
	void* tail;
	bbVPool_lookup(list->pool, &tail, tmpList->tail);
	bbPool_ListElement* tailListElement = tail + list->offsetOf;

	tailListElement->next = handleElement;
	headListElement->prev = handleElement;
	listElement->prev = tmpList->tail;
	listElement->next = tmpList->head;
	tmpList->tail = handleElement;

	return Success;
}

bbPool_List merge(bbList* list, bbPool_List* A, bbPool_List* B){
	if (isNULL(A->head) && isNULL(B->head)  ){
		bbPool_List C;
		C.head = list->pool->null;
		C.tail = list->pool->null;
		return C;
	}
	if (isNULL(A->head)) return *B;
	if (isNULL(B->head)) return *A;

	//actually merge the lists:

	bbPool_List C;
	C.head = list->pool->null;
	C.tail = list->pool->null;


	void *elementA;
	popL(list, &elementA, A);


	void *elementB;
    popL(list, &elementB, B);

	bbFlag flag;

	while(1) {
		if (list->compare(elementA, elementB)) {
			pushR(list, elementA, &C);
			flag = popL(list, &elementA, A);
			if (flag != Success) goto RemainingB;
		} else {
			pushR(list, elementB, &C);
			flag = popL(list, &elementB, B);
			if (flag != Success) goto RemainingA;
		}
	}
	//add remaining elements fram A to C
	RemainingA:
	while(1) {
	    pushR(list, elementA, &C);
	    flag = popL(list, &elementA, A);
		if (flag != Success) return C;
    }


	RemainingB:
	while(1) {
		pushR(list, elementB, &C);
		flag = popL(list, &elementB, B);
		if (flag != Success) return C;
	}


	return C;
}

/// take the first num elements and put in A, the rest go in C
bbFlag split(bbList* list, bbPool_List A, bbPool_List* B, bbPool_List* C, I32 num){

	if (num == 0) {
		*C = A;
		B->head = list->pool->null;
		B->tail = list->pool->null;

		return f_Success;
	}

	if (num == 1){

		void *BHead, *BTail, *CHead, *CTail;
		bbPool_ListElement *BHead_list, *BTail_list, *CHead_list, *CTail_list;
		bbPool_Handle BHead_handle, BTail_handle, CHead_handle, CTail_handle;

		BHead_handle = BTail_handle = A.head;

		bbVPool_lookup(list->pool, &BHead, BHead_handle);
		BTail = BHead;
		BHead_list = BTail_list = BHead + list->offsetOf;

		CHead_handle = BTail_list->next;
		bbVPool_lookup(list->pool, &CHead, CHead_handle);
		CHead_list = CHead + list->offsetOf;

		CTail_handle = BHead_list->prev;
		bbVPool_lookup(list->pool, &CTail, CTail_handle);
		CTail_list = CTail + list->offsetOf;

		BHead_list->prev = BTail_handle;
		BTail_list->next = BHead_handle;
		CHead_list->prev = CTail_handle;
		CTail_list->next = CHead_handle;

		B->head = BHead_handle;
		B->tail = BTail_handle;
		C->head = CHead_handle;
		C->tail = CTail_handle;

		return Success;

	}


	for(I32 i)


}