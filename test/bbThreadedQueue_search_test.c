
#include <stdio.h>

#include "engine/logic/bbPoolHandle.h"
#include "engine/threadsafe/bbThreadedQueue.h"
#include "engine/logic/bbCallback.h"
#include "engine/logic/bbTerminal.h"
#include "engine/threadsafe/bbTheadedQueue_search.h"
#include "engine/threadsafe/bbThreadedPool.h"

typedef struct {
    I32 integer;
    char string[64];
    bbPool_ListElement* list_element;
} test_struct;

//typedef bbFlag bbCallbackFunction(void* callback, bbPool_Handle handle);

bbFlag TestFunction(void* Callback, bbPool_Handle handle) {
    bbCallback* callback = (bbCallback*)Callback;

    if (callback->args.u64 == handle.u64) return Success;
    return None;
}

int main (void) {

    bbThreadedQueue queue;
    bbThreadedQueue_init(&queue, NULL, sizeof(test_struct), 100, offsetof(test_struct, list_element));

    test_struct* test_struct1;

    for (I32 i = 0; i < 100; i++) {

        bbThreadedPool_debug(queue.pool->pool);
        bbThreadedQueue_alloc(&queue, (void**)&test_struct1);
        test_struct1->integer = i;
        sprintf(test_struct1->string, "i = %d", i);
        bbDebug("i = %d\n", i);
        bbThreadedQueue_pushR(&queue, test_struct1);
    }
    bbCallback test_callback;
    test_callback.function = TestFunction;
    test_callback.args.u64 = 5;

    bbThreadedQueue_search(&queue, (void**)&test_struct1, &test_callback);

    printf("test_struct.string = %s\n", test_struct1->string);

    return 0;
}