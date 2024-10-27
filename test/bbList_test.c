#include "engine/logic/bbList.h"
#include "engine/logic/bbString.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
	char str[33];
	bbPool_ListElement listElement;
} testStruct;

int main(void){
	bbVPool* pool;
	bbVPool_newBloated(&pool, sizeof (testStruct),64, 64);

	bbList list;
	bbList_init(&list, pool, NULL, offsetof(testStruct, listElement),NULL);

	testStruct* aStruct;

	printf("Push Left:\n");
	for (I32 i = 0; i < 8; i++) {
		I32 len = bbList_getLength(&list);
		printf("len = %d\n", len);

		bbVPool_alloc(pool, &aStruct);
		sprintf(aStruct->str, "i = %d", i);
		printf("i = %d\n", i);
		aStruct->listElement.prev = pool->null;
		aStruct->listElement.next = pool->null;
		bbList_pushL(&list, aStruct);


	}

	I32 len = bbList_getLength(&list);
	printf("len = %d\n", len);

	printf("Pop Left:\n");
	while(Success == bbList_popL(&list, &aStruct)){

		printf("%s\n", aStruct->str);
		bbVPool_free(pool, aStruct);
	}
	printf("Push Right:\n");
	for (I32 i = 0; i < 8; i++) {
		bbVPool_alloc(pool, &aStruct);
		sprintf(aStruct->str, "i = %d", i);
		printf("i = %d\n", i);
		aStruct->listElement.prev = pool->null;
		aStruct->listElement.next = pool->null;
		bbList_pushR(&list, aStruct);
	}



	printf("Pop Right:\n");
	while(Success == bbList_popR(&list, &aStruct)){

		printf("%s\n", aStruct->str);
		bbVPool_free(pool, aStruct);
	}
	exit(EXIT_SUCCESS);
}