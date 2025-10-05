#include <stdio.h>
#include <stdlib.h>
#include "engine/logic/bbLeanPool.h"
#include "engine/logic/bbBloatedPool.h"
#include "engine/logic/bbVPool.h"

typedef struct
{
    char str[64];
} testStruct;

int main(void)
{
    bbVPool* testPool1;
    void* address;

    bbVPool_newLean(&testPool1, sizeof(testStruct), 256);


    bbVPool_alloc(testPool1, &address);
    bbVPool_printHeader(testPool1, address);
    bbVPool_alloc(testPool1, &address);
    bbVPool_printHeader(testPool1, address);
    bbVPool_alloc(testPool1, &address);
    bbVPool_printHeader(testPool1, address);

    bbVPool_delete(testPool1);

    bbVPool_newBloated(&testPool1, sizeof(testStruct), 4, 64);

    bbVPool_alloc(testPool1, &address);
    bbVPool_printHeader(testPool1, address);
    bbVPool_alloc(testPool1, &address);
    bbVPool_printHeader(testPool1, address);
    bbVPool_alloc(testPool1, &address);
    bbVPool_printHeader(testPool1, address);

    bbVPool_delete(testPool1);

    return 0;
}