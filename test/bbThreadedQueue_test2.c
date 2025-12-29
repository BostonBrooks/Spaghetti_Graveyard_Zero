#include <stddef.h>
#include <stdio.h>
#include <SFML/System/Sleep.h>

#include "engine/logic/bbTerminal.h"
#include "engine/threadsafe/bbThreadedQueue.h"


_Thread_local char* thread;

typedef struct
{
    char str[64];
    bbPool_ListElement list_element;
} test_struct;

void* receiveThread(void*);

int main(void)
{

    thread = "main";
    bbThreadedQueue queue;
    bbThreadedQueue_init(&queue, NULL, sizeof(test_struct), 100,offsetof(test_struct, list_element));

    pthread_t receive_thread;
    pthread_create(&receive_thread, NULL, receiveThread, &queue);

    test_struct* test;

    I32 i = 0;
    while (1)
    {
        bbThreadedQueue_alloc(&queue, (void**)&test);
        sprintf(test->str, "i = %d", i);
        bbThreadedQueue_pushL(&queue, test);
        printf("sent: %s\n", test->str);
        sfSleep(sfSeconds(1));
        i++;
    }

    return 0;
}


void* receiveThread(void* arg)
{

    thread = "recieve";
    bbHere()
    bbThreadedQueue* queue = arg;

    test_struct* test;
    while (1)
    {
        bbThreadedQueue_popRblock(queue, (void**)&test);

        printf("received: %s\n", test->str);
        bbThreadedQueue_free(queue, (void**)&test);
    }
    return NULL;
}