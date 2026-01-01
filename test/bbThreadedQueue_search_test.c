
#include <stdio.h>

#include "engine/logic/bbPoolHandle.h"
#include "engine/threadsafe/bbThreadedQueue.h"
#include "engine/logic/bbCallback.h"
#include "engine/logic/bbTerminal.h"
#include "engine/threadsafe/bbTheadedQueue_search.h"
#include "engine/threadsafe/bbThreadedPool.h"

typedef struct {
    I32 integer;
    char string[128];
    bbPool_ListElement list_element;
} struct1;

//typedef bbFlag bbCallbackFunction(void* callback, bbPool_Handle handle);

//callback.function = this function
//callback.args.u64 = 5
//handle.ptr points to a struct1
bbFlag TestFunction(void* Callback, bbPool_Handle handle) {

    bbCallback* callback = (bbCallback*)Callback;
    struct1* struct_1 = handle.ptr;
    if (callback->args.u64 == struct_1->integer) return Success;
    return None;
}

int main (void) {

    bbThreadedQueue queue;
    bbThreadedQueue_init(&queue, NULL, sizeof(struct1), 100, offsetof(struct1, list_element));

    bbThreadedPool* pool1 = queue.pool->pool;

    struct1* struct11;

    for (I32 i = 0; i < 100; i++) {

        bbThreadedQueue_alloc(&queue, (void**)&struct11);
        struct11->integer = i;
        sprintf(struct11->string, "i = %d", i);
        bbThreadedQueue_pushR(&queue, struct11);
    }
    bbCallback test_callback;
    test_callback.function = TestFunction;
    test_callback.args.u64 = 5;

    bbThreadedQueue_search(&queue, (void**)&struct11, &test_callback);

    printf("struct1.string: %s\n", struct11->string);

    return 0;
}