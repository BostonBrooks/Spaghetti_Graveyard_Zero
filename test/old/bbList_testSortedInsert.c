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

	bbList listA;
	bbList_init(&listA, pool, NULL, offsetof(testStruct, listElement),compare);

	printf("input:\n");

	for (I32 i = 0; i < 6; i ++) {
		bbVPool_alloc(pool, &aStruct);
		aStruct->i = 2*(rand()%64);
		aStruct->listElement.prev = pool->null;
		aStruct->listElement.next = pool->null;
		bbList_sortL(&listA, aStruct);


	}

    for (I32 i = 0; i < 6; i ++) {
        bbVPool_alloc(pool, &aStruct);
        aStruct->i = 2*(rand()%64) + 1;
        aStruct->listElement.prev = pool->null;
        aStruct->listElement.next = pool->null;
        bbList_sortR(&listA, aStruct);


    }

	printf("processing:\n");

    printf("list A sorted:\n");

	while(Success == bbList_popL(&listA, &aStruct)){

		printf("%d\n", aStruct->i);
		bbVPool_free(pool, aStruct);
	}



    exit(EXIT_SUCCESS);
}