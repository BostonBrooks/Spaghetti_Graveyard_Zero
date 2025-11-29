//#include "engine/logic/bbList.h"
#include "engine/logic/bbString.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "engine/logic/bbList_sort.c"

typedef struct {
	I32 i;
	bbPool_ListElement listElement;
} testStruct;

I32 compare (void* A, void* B){
	testStruct* aStruct = A;
	testStruct* bStruct = B;
	return aStruct->i < bStruct->i;
}

int main(void){

	bbVPool* pool;
	bbVPool_newBloated(&pool, sizeof (testStruct),64, 64);

	testStruct* aStruct;

	bbList listA, listB, listC;
	bbList_init(&listA, pool, NULL, offsetof(testStruct, listElement),compare);
	bbList_init(&listB, pool, NULL, offsetof(testStruct, listElement),NULL);
	bbList_init(&listC, pool, NULL, offsetof(testStruct, listElement),NULL);

	printf("input:\n");

	for (I32 i = 0; i < 16; i ++) {
		I32 len = bbList_getLength(&listA);
		bbVPool_alloc(pool, &aStruct);
		aStruct->i = i;
		aStruct->listElement.prev = pool->null;
		aStruct->listElement.next = pool->null;
		bbList_pushR(&listA, aStruct);


	}


    for (I32 i = -3; i < 20; i ++) {
        testStruct *aStruct1;
        bbFlag flag = getNth(&listA, *listA.listPtr, &aStruct1, i);

        if (flag == Tail) printf ("(Tail) ");
        else if (flag == Success) printf ("(Middle) ");
        else if (flag == Head) printf ("(Head) ");

        printf("%dth element is %d\n", i, aStruct1->i);
    }
	printf("processing:\n");

    split(&listA, *listA.listPtr, listB.listPtr, listC.listPtr, 6);


    printf("list B: (first 6 elements)\n");

	while(Success == bbList_popL(&listB, &aStruct)){

		printf("%d\n", aStruct->i);
		bbVPool_free(pool, aStruct);
	}


    printf("list C: (remaining elements)\n");

    while(Success == bbList_popL(&listC, &aStruct)){

        printf("%d\n", aStruct->i);
        bbVPool_free(pool, aStruct);
    }
}