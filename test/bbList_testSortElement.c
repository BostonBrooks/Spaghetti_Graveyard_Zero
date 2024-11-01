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

    testStruct * elements[16];

	for (I32 i = 0; i < 16; i ++) {
		bbVPool_alloc(pool, &aStruct);
        elements[i] = aStruct;
		aStruct->i = rand()%256;
		aStruct->listElement.prev = pool->null;
		aStruct->listElement.next = pool->null;
		bbList_sortL(&listA, aStruct);


	}

    printf("processing:\n");

    for (I32 i = 0; i < 16; i ++) {

        aStruct = elements[i];
        aStruct->i += rand()%64 - 32;

        bbList_sortElement(&listA, aStruct);


    }


    printf("list A sorted:\n");

	while(Success == bbList_popL(&listA, &aStruct)){

		printf("%d\n", aStruct->i);
		bbVPool_free(pool, aStruct);
	}



    exit(EXIT_SUCCESS);
}