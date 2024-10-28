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

	testStruct *middleStruct, *aStruct;

    bbVPool_alloc(pool, &middleStruct);
    sprintf(middleStruct->str, "middle");
    bbList_pushL(&list, middleStruct);

	for (I32 i = 0; i < 3; i++) {
		bbVPool_alloc(pool, &aStruct);
		sprintf(aStruct->str, "i = %d", i);
		aStruct->listElement.prev = pool->null;
		aStruct->listElement.next = pool->null;
        bbList_insertBefore(&list, aStruct, middleStruct);


	}

    for (I32 i = 0; i < 3; i++) {

        bbVPool_alloc(pool, &aStruct);
        sprintf(aStruct->str, "j = %d", i);
        aStruct->listElement.prev = pool->null;
        aStruct->listElement.next = pool->null;
        bbList_insertAfter(&list, aStruct, middleStruct);


    }

	I32 len = bbList_getLength(&list);
	printf("len = %d\n", len);

	printf("Pop Left:\n");
	while(Success == bbList_popL(&list, &aStruct)){

		printf("%s\n", aStruct->str);
		bbVPool_free(pool, aStruct);
	}

	exit(EXIT_SUCCESS);
}