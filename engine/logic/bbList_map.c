
#include "engine/logic/bbList.h"
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbTerminal.h"

#define isEqual(A, B) bbVPool_handleIsEqual(list->pool, A, B)
#define isNULL(A) bbVPool_handleIsEqual(list->pool, A, list->pool->null)

bbFlag bbList_mapL(bbList* list, bbListFunction* myFunc, void* cl){


	if(isNULL(list->listPtr->head)){
		bbAssert(isNULL(list->listPtr->tail), "head/tail\n");
		return f_Success;
	}

	bbPool_Handle handeElement = list->listPtr->head;
	void* element;
	bbPool_ListElement* listElement;
	bbFlag flag;

	while(1){
		bbVPool_lookup(list->pool, &element, handeElement);
		listElement = element + list->offsetOf;
		flag = myFunc(list, element, cl);
		switch (flag){
			case Break:
				return Break;
			case Continue:
				if(isEqual(handeElement, list->listPtr->tail))
					return Success;
				handeElement = listElement->next;
				break;
			case Repeat:
				bbHere();
				break;
			default:
				bbHere();
		}

	}

}

bbFlag bbList_mapR(bbList* list, bbListFunction* myFunc, void* cl){


	if(isNULL(list->listPtr->tail)){
		bbAssert(isNULL(list->listPtr->head), "head/tail\n");
		return f_Success;
	}

	bbPool_Handle handeElement = list->listPtr->tail;
	void* element;
	bbPool_ListElement* listElement;
	bbFlag flag;

	while(1){
		bbVPool_lookup(list->pool, &element, handeElement);
		listElement = element + list->offsetOf;
		flag = myFunc(list, element, cl);
		switch (flag){
			case Break:
				return Break;
			case Continue:
				if(isEqual(handeElement, list->listPtr->head))
					return Success;
				handeElement = listElement->prev;
				break;
			case Repeat:
				bbHere();
				break;
			default:
				bbHere();
		}

	}

}


