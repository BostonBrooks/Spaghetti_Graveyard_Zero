#include "engine/threadsafe/bbThreadedQueue.h"

#include "engine/threadsafe/bbThreadedPool.h"

#include <stdio.h>
#include <SFML/System/Sleep.h>

#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbVPool.h"

_Thread_local char* thread;

typedef struct
{
    char str[64];
    bbPool_ListElement list_element;
} teststring;

void* send_messages(void* queue)
{

    thread = "Send";
    I32 i = 0;
    while (1)
    {
        //bbThreadedQueue* Queue = (bbThreadedQueue*)queue;
        //bbThreadedPool* pool = Queue->pool->pool;
        //bbDebug("inUse = %d\n", pool->inUse);
        teststring* test;
        bbThreadedQueue_alloc(queue, (void**)&test);
        sprintf(test->str, "receive %d", i);
        printf("send %d\n", i);
        bbThreadedQueue_pushL(queue, test);

        //do other things
        sfSleep(sfSeconds(0.1));

        i++;
    }
    return 0;
}



void* receive_messages(void* queue)
{
    thread = "Receive";
    bbFlag flag = Success;
    while (1)
    {
        flag = Success;
        //check queue
        while (flag == Success)
        {
            //bbThreadedQueue* Queue = (bbThreadedQueue*)queue;
            //bbThreadedPool* pool = Queue->pool->pool;
            //bbDebug("inUse = %d\n", pool->inUse);
            teststring* test;
            flag = bbThreadedQueue_popR(queue, (void**)&test);
            if (flag != Success) break;
            printf("%s\n", test->str);
            bbThreadedQueue_free(queue, (void**)&test);

        }
        //do other things
        sfSleep(sfSeconds(2));
    }
    return 0;
}


int main(void)
{

    thread = "Main";
    bbFlag flag;
    bbThreadedQueue queue;
    flag = bbThreadedQueue_init(&queue, NULL, sizeof(teststring), 10, offsetof(teststring, list_element));

    pthread_t send_thread, receive_thread;
    pthread_create(&send_thread,NULL, send_messages, &queue);
    pthread_create(&receive_thread,NULL, receive_messages, &queue);

    sfSleep(sfSeconds(60));

    exit(0);
}