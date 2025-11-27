#include "engine/logic/bbList.h"
#include <stdio.h>

typedef struct {
    bbPool_ListElement listElement;
} testStruct;

int main (void){
    bbVPool* pool;
    bbVPool_newBloated(&pool, sizeof(testStruct), 12, 12);

    bbList list;
    bbList_init(&list, pool, NULL, offsetof(testStruct, listElement),NULL);

    testStruct* someStructs[12];

    for (I32 i = 0; i < 12; i++){
        bbVPool_alloc(pool, (void**)&someStructs[i]);
        someStructs[i]->listElement.next = pool->null;
        someStructs[i]->listElement.prev = pool->null;

        bbList_pushR(&list, someStructs[i]);
    }

    bbList_remove(&list, someStructs[3]);

    printf("Task passed unexpectedly\n");

    exit(EXIT_SUCCESS);
}

