#include "engine/logic/bbFastPool.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbRoundUp.h"
#include <stdlib.h>

I32 bbFastPool_newPool(void** pool, I32 sizeOf, I32 level1, I32 level2, I32
map) {

    bbAssert (level1 * level2 >= 3, "why such a small pool?");

    I32 size = bbRoundUp(
			(sizeOf > sizeof(bbFastPool_Available)) ?
            sizeOf : sizeof(bbFastPool_Available),
					8);

    bbFastPool *Pool = malloc(sizeof(bbFastPool) + level1 * level2 * size);
    bbAssert(Pool != NULL, "malloc failed\n");
    Pool->p_sizeOf = size;
    Pool->p_num = level1 * level2;
    Pool->p_map = map;

    void* prev = NULL;
    void* this = &Pool->p_objects[0 * size];
    void* next = &Pool->p_objects[1 * size];

    bbFastPool_Available* castThis = this;

    castThis->p_header.p_pool = Pool;
    castThis->p_prev = prev;
    castThis->p_next = next;

    for (I32 i = 1; i < level1 * level2; i++) {

        prev = this;
        this = next;
        next = &Pool->p_objects[i * size];

        castThis = this;

        castThis->p_header.p_pool = Pool;
        castThis->p_prev = prev;
        castThis->p_next = next;
    }
    prev = this;
    this = next;
    next = NULL;

    castThis = this;

    castThis->p_header.p_pool = Pool;
    castThis->p_prev = prev;
    castThis->p_next = next;

    Pool->p_availableHead = &Pool->p_objects[0 * size];
    Pool->p_availableTail = this;

    *pool = Pool;

    return f_Success;

}
I32 bbFastPool_deletePool(void* pool){
    free(pool);
    return f_Success;
}

I32 bbFastPool_clearPool(void* pool){
    bbFastPool *Pool = pool;
    I32 size = Pool->p_sizeOf;
    I32 num = Pool->p_num;

    void* prev = NULL;
    void* this = &Pool->p_objects[0 * size];
    void* next = &Pool->p_objects[1 * size];

    bbFastPool_Available* castThis = this;

    castThis->p_header.p_pool = Pool;
    castThis->p_prev = prev;
    castThis->p_next = next;

    for (I32 i = 1; i < num - 1; i++) {

        prev = this;
        this = next;
        next = &Pool->p_objects[(i+1) * size];

        castThis = this;

        castThis->p_header.p_pool = Pool;
        castThis->p_prev = prev;
        castThis->p_next = next;
    }
    prev = this;
    this = next;
    next = NULL;

    castThis = this;

    castThis->p_header.p_pool = Pool;
    castThis->p_prev = prev;
    castThis->p_next = next;

    Pool->p_availableHead = &Pool->p_objects[0 * size];
    Pool->p_availableTail = &Pool->p_objects[(num-1) * size];
}


I32 bbFastPool_newA(void* pool, void** address){
    bbFastPool* Pool = pool;

    if (Pool->p_availableHead == NULL){
        //empty list
        bbAssert(Pool->p_availableTail == NULL, "head/tail mismatch\n");
        return f_None;
    }
    bbFastPool_Available* this = Pool->p_availableHead;
    bbAssert(this->p_prev == NULL, "head not start of list?\n");

    if (this->p_next == NULL){
        // last item in list
        bbAssert(this == Pool->p_availableTail, "tail not end of list?\n");

        Pool->p_availableHead = NULL;
        Pool->p_availableTail = NULL;

        *address = this;
        return f_Success;
    }

    bbFastPool_Available* Next = this->p_next;

    Pool->p_availableHead = Next;
    Next->p_prev = NULL;

    *address = this;

    return f_Success;



}
I32 bbFastPool_newH(void* pool, bbFastPool_Handle* handle){
    bbFastPool* Pool = pool;

    if (Pool->p_availableHead == NULL){
        //empty list
        bbAssert(Pool->p_availableTail == NULL, "head/tail mismatch\n");
        return f_None;
    }
    bbFastPool_Available* this = Pool->p_availableHead;
    bbAssert(this->p_prev == NULL, "head not start of list?\n");

    if (this->p_next == NULL){
        // last item in list
        bbAssert(this == Pool->p_availableTail, "tail not end of list?\n");

        Pool->p_availableHead = NULL;
        Pool->p_availableTail = NULL;

        *handle = this;
        return f_Success;
    }

    bbFastPool_Available* Next = this->p_next;

    Pool->p_availableHead = Next;
    Next->p_prev = NULL;

    *handle = this;

    return f_Success;

}

I32 bbFastPool_deleteA(void* pool, void* address){
    bbFastPool_Available* this = address;
    bbFastPool* Pool = pool;

    bbFastPool_Available* Head = Pool->p_availableHead;
    bbFastPool_Available* Tail = Pool->p_availableTail;

    if (Head == NULL) {
        bbAssert (Tail == NULL, "head/tail mismathc\n");
        Pool->p_availableHead = this;
        Pool->p_availableTail = this;
        this->p_prev = NULL;
        this->p_next = NULL;

        return f_Success;

    }
    bbFastPool_Available* hedd = Head;
    bbFastPool_Available* next = hedd->p_next;
    Pool->p_availableHead = this;
    this->p_prev = NULL;
    next->p_prev = this;
    this->p_next = next;

    return f_Success;
}

I32 bbFastPool_deleteH(void* pool, bbFastPool_Handle handle){
    bbFastPool_Available* this = handle;
    bbFastPool* Pool = pool;

    bbFastPool_Available* Head = Pool->p_availableHead;
    bbFastPool_Available* Tail = Pool->p_availableTail;

    if (Head == NULL) {
        bbAssert (Tail == NULL, "head/tail mismatch\n");
        Pool->p_availableHead = this;
        Pool->p_availableTail = this;
        this->p_prev = NULL;
        this->p_next = NULL;

        return f_Success;

    }
    bbFastPool_Available* hedd = Head;
    bbFastPool_Available* next = hedd->p_next;
    Pool->p_availableHead = this;
    this->p_prev = NULL;
    next->p_prev = this;
    this->p_next = next;

    return f_Success;
}

I32 bbFastPool_getAddress(void* pool, void** address, bbFastPool_Handle handle){
    *address = handle;
    return f_Success;
}
I32 bbFastPool_getHandle(void* pool, bbFastPool_Handle* handle, void* address){
    *handle = address;
    return f_Success;
}
