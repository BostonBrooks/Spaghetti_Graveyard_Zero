#include "engine/threadsafe/bbThreadedQueue.h"

#include "engine/threadsafe/bbThreadedPool.h"

#include <stdio.h>

#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbVPool.h"

typedef struct
{
    char str[64];
    bbPool_ListElement list_element;
} teststring;

int main(void)
{
    bbFlag flag;
    bbThreadedQueue queue;
    flag = bbThreadedQueue_init(&queue, NULL, sizeof(teststring), 100, offsetof(teststring, list_element));

    teststring* test;
    flag = bbThreadedQueue_alloc(&queue, (void**)&test);

    bbStr_setStr(test->str, "rowreowrow", 64);

    flag = bbThreadedQueue_free(&queue, (void**)&test);


    bbPrintf("We made it to the end!\n");
    return 0;
}