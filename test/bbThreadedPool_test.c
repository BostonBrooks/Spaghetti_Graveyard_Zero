#include "engine/threadsafe/bbThreadedPool.h"

#include <stdio.h>

#include "engine/logic/bbVPool.h"

typedef struct
{
    char str[64];
} teststring;

int main(void)
{
    bbVPool* pool;
    bbVPool_newThreaded(&pool, sizeof(teststring), 100);
    teststring* test[100];

    for (I32 i = 0; i < 100; i++)
    {
        bbVPool_alloc(pool, (void**)&test[i]);
        sprintf(test[i]->str, "test %d", i);

        printf("original string = %s\n", test[i]->str);

        /*teststring* teststring;
        bbPool_Handle handle;
        handle.u64 = i;
        bbThreadedPool_lookup(pool->pool, (void**)&teststring, handle);
        printf("lookup string = %s\n", teststring->str);


        bbThreadedPool_reverseLookup(pool->pool, teststring, &handle);
        */


    }

    //everything works up until here

    printf("\n");

    for (I32 i = 0; i < 100; i++)
    {
        int tens = i/10;
        int ones = i%10;

        int shuffled = 10* ones + tens;
        teststring* teststring = test[shuffled];

        printf("delete string %s\n", teststring->str);
        bbVPool_free(pool, teststring);
    }

    bbVPool_delete(pool);
    return 0;
}