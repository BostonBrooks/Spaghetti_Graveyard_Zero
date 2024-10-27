#include "engine/logic/bbList.h"
#include "engine/logic/bbString.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbFlag.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


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
        bbHere();
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
    printf("sort: len = %d\n", len);
    if (len == 1){
        return Success;
    }

    if (len == 2){
        void *head, *tail;
        bbVPool_lookup(list->pool, &head, tmpList->head);
        bbVPool_lookup(list->pool, &tail, tmpList->tail);

        if(!list->compare(head, tail)){
            bbPool_Handle tmp = tmpList->head;
            tmpList->head = tmpList->tail;
            tmpList->tail = tmp;
            return Success;
        }
        return Success;

    }

    bbPool_List B,C;
    I32 lenB = len/2;
    I32 lenC = len - lenB;

    split(list, *tmpList, &B, &C, lenB);



    printf("lenB = %d, len(B) = %d, lenC = %d, len(C) = %d\n",
           lenB, getLength(list, B),
           lenC, getLength(list, C));

    sort(list, &B, lenB);
    sort(list, &C, lenC);

    bbPool_List tmp;

    tmp = merge(list, &B, &C);

    *tmpList = tmp;
    return None;
}
bbFlag bbList_sort(bbList* list) {
    I32 len = bbList_getLength(list);
    printf("initial len = %d\n", len);
    bbPool_List tmpList = *list->listPtr;
    sort(list, &tmpList, len);
    *list->listPtr = tmpList;
    return Success;
}
