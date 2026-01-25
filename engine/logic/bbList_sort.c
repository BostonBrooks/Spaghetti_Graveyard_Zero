#include "engine/logic/bbList.h"
#include "engine/logic/bbString.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbFlag.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "bbLeanPool.h"


#define isEqual(A, B) bbVPool_handleIsEqual(list->pool, A, B)
#define isNULL(A) bbVPool_handleIsEqual(list->pool, A, list->pool->null)

I32 getLength(bbList* list, bbPool_List tmpList){
    if(isNULL(tmpList.head)){
        bbAssert(isNULL(tmpList.tail), "head / tail mismatch\n");
        return 0;
    }

    if (isEqual(tmpList.head, tmpList.tail)){
        return 1;
    }
    I32 len = 2;
    bbPool_Handle handleElement = tmpList.head;
    void* element;
    bbVPool_lookup(list->pool, &element, handleElement);
    bbPool_ListElement* listElement = element + list->offsetOf;

    while (!isEqual(listElement->next, tmpList.tail)){
        handleElement = listElement->next;
        bbVPool_lookup(list->pool, &element, handleElement);
        listElement = element + list->offsetOf;
        len++;
    }
    return len;
}


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

///if the list has an element N, starting at 1, return that element,
///else return the nearest element ie the head or the tail

bbFlag getNth (bbList* list, bbPool_List tmpList, void** element, I32 N){

    bbPool_Handle handle = tmpList.head;
    void* Element;
    bbVPool_lookup(list->pool, &Element, handle);
    bbPool_ListElement* listElement = Element + list->offsetOf;

    if (N <= 1){
        *element = Element;
        return Head;
    }

    for(I32 i = 1; i < N; i++){
        handle = listElement->next;
        bbVPool_lookup(list->pool, &Element, handle);
        if(isEqual(handle,tmpList.tail)) {
            *element = Element;
            return Tail;
        };
        listElement = Element + list->offsetOf;

    }

    *element = Element;

    return Success;

}

/// take the first num elements and put in A, the rest go in C
bbFlag split(bbList* list, bbPool_List A, bbPool_List* B, bbPool_List* C, I32 num){


    if (isNULL(A.head)){
        bbAssert(isNULL(A.tail), "split empty list?\n");


        B->head = list->pool->null;
        B->tail = list->pool->null;

        C->head = list->pool->null;
        C->tail = list->pool->null;
    }
	if (num <= 0) {
		*C = A;
		B->head = list->pool->null;
		B->tail = list->pool->null;

		return f_Success;
	}

	if (num == 1){

        if(isEqual(A.head, A.tail)){
            *B = A;
            C->head = list->pool->null;
            C->tail = list->pool->null;

            return f_Success;
        }

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

    if (num == 2){
        if(isEqual(A.head, A.tail)){
            *B = A;
            C->head = list->pool->null;
            C->tail = list->pool->null;

            return Success;
        }

        bbPool_Handle AHeadHandle = A.head;
        void* AHead;
        bbVPool_lookup(list->pool, &AHead, AHeadHandle);
        bbPool_ListElement* AHeadList = AHead + list->offsetOf;

        bbPool_Handle A2Handle = AHeadList->next;

        //list has only 2 elements
        if (isEqual(A2Handle, A.tail)){
            *B = A;
            C->head = list->pool->null;
            C->tail = list->pool->null;

            return Success;
        }

        void* A2;
        bbVPool_lookup(list->pool, &A2, A2Handle);
        bbPool_ListElement* A2List = A2 + list->offsetOf;

        //B contains AHead, A2,
        //C contains A3 to A.Tail

        bbPool_Handle A3Handle = A2List->next;
        void* A3;
        bbVPool_lookup(list->pool, &A3, A3Handle);
        bbPool_ListElement* A3List = A3 + list->offsetOf;

        B->head = A.head;
        B->tail = A2Handle;
        AHeadList->prev = A2Handle;
        A2List->next = AHeadHandle;

        if(isEqual(A3Handle, A.tail)){
            C->head = A3Handle;
            C->tail = A3Handle;
            A3List->prev = A3Handle;
            A3List->next = A3Handle;

            return Success;
        }

        bbPool_Handle ATailHandle = A.tail;
        void* ATail;
        bbVPool_lookup(list->pool, &ATail, ATailHandle);
        bbPool_ListElement* ATailList = ATail + list->offsetOf;

        C->head = A3Handle;
        C->tail = A.tail;
        A3List->prev = A.tail;
        ATailList->next = A3Handle;

        return Success;

    }

    //if (num == 3)
    {

        void* Nth;
        bbFlag flag = getNth(list, A, &Nth, num);

        if (flag == Tail){
            B->head = A.head;
            B->tail = A.tail;
            C->head = list->pool->null;
            C->tail = list->pool->null;

            return Success;
        }

        bbPool_Handle NthHandle;
        bbVPool_reverseLookup(list->pool, Nth, &NthHandle);
        bbPool_ListElement* NthList = Nth + list->offsetOf;

        bbPool_Handle AHeadHandle = A.head;
        void* AHead;
        bbVPool_lookup(list->pool, &AHead, AHeadHandle);
        bbPool_ListElement* AHeadList = AHead + list->offsetOf;

        bbPool_Handle NthNextHandle = NthList->next;

        B->head = A.head;
        B->tail = NthHandle;
        NthList->next = A.head;
        AHeadList->prev = NthHandle;

        void* NthNext;
        bbVPool_lookup(list->pool, &NthNext, NthNextHandle);
        bbPool_ListElement* NthNextList = NthNext + list->offsetOf;

        if(isEqual(NthNextHandle, A.tail)){
            // one element in A;


            C->head = NthNextHandle;
            C->tail = NthNextHandle;
            NthNextList->prev = NthNextHandle;
            NthNextList->next = NthNextHandle;

            return Success;

        }

        bbPool_Handle ATailHandle = A.tail;
        void* ATail;
        bbVPool_lookup(list->pool, &ATail, ATailHandle);
        bbPool_ListElement* ATailList = ATail + list->offsetOf;

        C->head = NthNextHandle;
        C->tail = ATailHandle;
        NthNextList->prev = ATailHandle;
        ATailList->next = NthNextHandle;

        return Success;
    }
}

bbFlag sort(bbList* list, bbPool_List* tmpList, I32 len){
//printf("sort: len = %d\n", len);
    if (len == 1){
        return Success;
    }

    if (len == 2){
        void *head, *tail;
        bbVPool_lookup(list->pool, &head, tmpList->head);
        bbVPool_lookup(list->pool, &tail, tmpList->tail);

        if(list->compare(head, tail)) return Success;


        bbPool_Handle tmp = tmpList->head;
        tmpList->head = tmpList->tail;
        tmpList->tail = tmp;
        return Success;


    }

    bbPool_List B,C;
    I32 lenB = len/2;
    I32 lenC = len - lenB;

    split(list, *tmpList, &B, &C, lenB);



//printf("lenB = %d, len(B) = %d, lenC = %d, len(C) = %d\n",
//       lenB, getLength(list, B),
//       lenC, getLength(list, C));

    sort(list, &B, lenB);
    sort(list, &C, lenC);

    bbPool_List tmp;

    tmp = merge(list, &B, &C);

    *tmpList = tmp;
    return None;
}
bbFlag bbList_sort(bbList* list) {
    I32 len = bbList_getLength(list);
//printf("initial len = %d\n", len);
    bbPool_List tmpList = *list->listPtr;
    sort(list, &tmpList, len);
    *list->listPtr = tmpList;
    return Success;
}

bbFlag bbList_sortL(bbList* list, void* element){

	bbVPool* pool = list->pool;
	bbVPool_handleValid(pool, list->listPtr->head);
	bbVPool_handleValid(pool, list->listPtr->tail);



    bbPool_Handle elementHandle;
    bbVPool_reverseLookup(list->pool, element, &elementHandle);
    bbPool_ListElement* elementList = element + list->offsetOf;

    bbAssert(isNULL(elementList->prev), "element already in a list\n");
    bbAssert(isNULL(elementList->next), "element already in a list\n");

	//this should deal with empty list
    if(isNULL(list->listPtr->head) || isNULL(list->listPtr->tail)){
        bbAssert(isNULL(list->listPtr->head) && isNULL(list->listPtr->tail), "head / tail mismatch\n");
        bbList_pushL(list, element);
        return Success;
    }

    bbPool_Handle nextHandle = list->listPtr->head;
    void *next;
    bbPool_ListElement *nextList;
    while(1) {

        bbFlag flag = bbVPool_lookup(list->pool, &next, nextHandle);

        nextList = next + list->offsetOf;

    	bbVPool* pool = list->pool;

    	bbVPool_elementInBounds(pool, element)
    	//bbDebug("next = %llu\n", next);

    	if (next == NULL)
    	{
    		bbList_pushR(list, element);
    		return Success;
    	}

    	bbVPool_elementInBounds(pool, next);
        if (list->compare(element, next)) {
            bbList_insertBefore(list, element, next);
            return Success;
        }
        if (isEqual(nextHandle,list->listPtr->tail)) {
            bbList_pushR(list, element);
            return Success;
        }
        nextHandle = nextList->next;

    }



}
bbFlag bbList_sortR(bbList* list, void* element) {
    bbPool_Handle elementHandle;
    bbVPool_reverseLookup(list->pool, element, &elementHandle);
    bbPool_ListElement *elementList = element + list->offsetOf;

    bbAssert(isNULL(elementList->prev), "element already in a list\n");
    bbAssert(isNULL(elementList->next), "element already in a list\n");

    if(isNULL(list->listPtr->head)){
        bbAssert(isNULL(list->listPtr->tail), "head / tail mismatch\n");
        bbList_pushR(list, element);
        return Success;
    }

    bbPool_Handle prevHandle = list->listPtr->tail;
    void *prev;
    bbPool_ListElement *prevList;

    while(1) {
        bbVPool_lookup(list->pool, &prev, prevHandle);
        prevList = prev + list->offsetOf;

    	if (prev == NULL)
    	{
    		bbList_pushL(list, element);
    		return Success;
    	}

        if (!list->compare(element, prev)) {
            bbList_insertAfter(list, element, prev);
            return Success;
        }
        if (isEqual(prevHandle,list->listPtr->head)) {
            bbList_pushL(list, element);
            return Success;
        }
        prevHandle = prevList->prev;
    }
}

bbFlag bbList_sortElement(bbList* list, void* element){
    bbPool_Handle elementHandle;
    bbVPool_reverseLookup(list->pool, element, &elementHandle);
    bbPool_ListElement *elementList = element + list->offsetOf;

    bbAssert(!isNULL(list->listPtr->head), "list should not ne empty\n");
    bbAssert(!isNULL(list->listPtr->tail), "list should not ne empty\n");

    //Is this the only element in the list?
    if (isEqual(elementHandle, list->listPtr->head )
        && isEqual(elementHandle, list->listPtr->tail ) ){
        return Success;
    }

    //Is this the head element?
    if (isEqual(elementHandle, list->listPtr->head )){


        bbPool_Handle nextHandle = elementList->next;
        void* next;
        bbVPool_lookup(list->pool, &next, nextHandle);
        bbPool_ListElement* nextList = next + list->offsetOf;

        //Is the element already sorted?
        if(list->compare(element, next)) return Success;

        //remove element from list
        bbPool_Handle tailHandle = list->listPtr->tail;
        void* tail;
        bbVPool_lookup(list->pool, &tail, tailHandle);
        bbPool_ListElement* tailList = tail + list->offsetOf;

        nextList->prev = tailHandle;
        tailList->next = nextHandle;
        elementList->prev = list->pool->null;
        elementList->next = list->pool->null;

        list->listPtr->head = nextHandle;

        return bbList_sortL(list, element);
    }

    //Is this the tail element?
    if (isEqual(elementHandle, list->listPtr->tail )){

        bbPool_Handle prevHandle = elementList->prev;
        void* prev;
        bbVPool_lookup(list->pool, &prev, prevHandle);
        bbPool_ListElement* prevList = prev + list->offsetOf;

        //Is the element already sorted?
        if(list->compare(prev, element)) return Success;

        //remove element from list
        bbPool_Handle headHandle = list->listPtr->head;
        void* head;
        bbVPool_lookup(list->pool, &head, headHandle);
        bbPool_ListElement* headList = head + list->offsetOf;

        prevList->next = headHandle;
        headList->prev = prevHandle;
        elementList->prev = list->pool->null;
        elementList->next = list->pool->null;

        list->listPtr->tail = prevHandle;

        return bbList_sortR(list, element);
    }


    bbPool_Handle prevHandle = elementList->prev;
    void* prev;
    bbVPool_lookup(list->pool, &prev, prevHandle);
    bbPool_ListElement* prevList = prev + list->offsetOf;

    bbPool_Handle nextHandle = elementList->next;
    void* next;
    bbVPool_lookup(list->pool, &next, nextHandle);
    bbPool_ListElement* nextList = next + list->offsetOf;

    //Is the element already sorted?
    if (list->compare(prev, element) && list->compare(element, next))
        return Success;


    nextList->prev = prevHandle;
    prevList->next = nextHandle;
    elementList->prev = list->pool->null;
    elementList->next = list->pool->null;

    //move element left
    if (!list->compare(prev, element)){

        while(1) {
            bbVPool_lookup(list->pool, &prev, prevHandle);
            prevList = prev + list->offsetOf;

            if (list->compare(prev, element)) {
                bbList_insertAfter(list, element, prev);
                return Success;
            }
            if (isEqual(prevHandle,list->listPtr->head)) {
                bbList_pushL(list, element);
                return Success;
            }
            prevHandle = prevList->prev;
        }

        //move element left

        return Success;
    }

    //if (!list->compare(element, next)){
        //move element right
    while(1) {

        bbVPool_lookup(list->pool, &next, nextHandle);
        nextList = next + list->offsetOf;

        if (list->compare(element, next)) {
            bbList_insertBefore(list, element, next);
            return Success;
        }
        if (isEqual(nextHandle,list->listPtr->tail)) {
            bbList_pushR(list, element);
            return Success;
        }
        nextHandle = nextList->next;
    }

}