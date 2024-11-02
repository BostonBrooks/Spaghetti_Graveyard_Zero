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
    testStruct* bStruct;

    testStruct* structs[8];

    printf("Push Right:\n");
    for (I32 i = 0; i < 8; i++) {

        bbVPool_alloc(pool, &aStruct);
        structs[i] = aStruct;
        sprintf(aStruct->str, "i = %d", i);
        aStruct->listElement.prev = pool->null;
        aStruct->listElement.next = pool->null;
        bbList_pushR(&list, aStruct);


    }

    bbList_remove(&list, structs[4]);

    printf("loop left to right\n");
    bbList_setHead(&list, &aStruct);
    do {
        bbList_getCurrent(&list, &bStruct);
        printf("%s\n", bStruct->str); }
    while(Success == bbList_increment(&list, &aStruct));

    printf("loop right to left\n");
    bbList_setCurrent(&list, structs[5]);
    bbList_getCurrent(&list, &aStruct);
    do {
        printf("%s\n", aStruct->str);
        bbList_remove(&list, aStruct);
    }
    while(Success == bbList_decrement(&list, &aStruct));

    printf("remaining elements:\n");
    printf("Pop Left:\n");
    while(Success == bbList_popL(&list, &aStruct)){

        printf("%s\n", aStruct->str);
        bbVPool_free(pool, aStruct);
    }


    exit(EXIT_SUCCESS);
}