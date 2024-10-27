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

	for (I32 i = 0; i < 32; i ++) {
		I32 len = bbList_getLength(&listA);
		bbVPool_alloc(pool, &aStruct);
		aStruct->i = rand()%100;
		aStruct->listElement.prev = pool->null;
		aStruct->listElement.next = pool->null;
		bbList_pushR(&listA, aStruct);


	}


	printf("processing:\n");

    bbList_sort(&listA);
    printf("list A sorted:\n");

	while(Success == bbList_popL(&listA, &aStruct)){

		printf("%d\n", aStruct->i);
		bbVPool_free(pool, aStruct);
	}

    exit(EXIT_SUCCESS);
}