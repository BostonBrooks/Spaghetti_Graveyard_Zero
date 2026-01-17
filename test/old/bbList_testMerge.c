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
	I32 j = 0;
	for (I32 i = 0; i < 16; i += 2) {
		I32 len = bbList_getLength(&listA);
		bbVPool_alloc(pool, &aStruct);
		aStruct->i = j;
		printf("i = %d\n", j);
		j+= rand()%64;
		aStruct->listElement.prev = pool->null;
		aStruct->listElement.next = pool->null;
		bbList_pushR(&listA, aStruct);


	}
	printf("\n");
	j = 1;
	for (I32 i = 1; i < 16; i += 2) {
		I32 len = bbList_getLength(&listA);

		bbVPool_alloc(pool, &aStruct);
		aStruct->i = j;
		printf("i = %d\n", j);
		j+= rand()%64;
		aStruct->listElement.prev = pool->null;
		aStruct->listElement.next = pool->null;
		bbList_pushR(&listB, aStruct);

	}
	printf("\nprocessing:\n");
	listC.list = merge(&listA, listA.listPtr, listB.listPtr);
	printf("\noutput:\n");
	while(Success == bbList_popL(&listC, &aStruct)){

		printf("%d\n", aStruct->i);
		bbVPool_free(pool, aStruct);
	}
}