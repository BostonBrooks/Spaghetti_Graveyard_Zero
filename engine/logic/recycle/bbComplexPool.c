#include    <stdlib.h>
#include <stddef.h>
#include "bbPool.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbArith.h"
#include "bbComplexPool.h"

typedef struct {
    bbPool_common common;

    U32 level1;
    U32 level2;
    bbPool_List available;
    void* elements[];
} bbComplexPool;

I32 bbComplexPool_deletePool(bbPool_common* pool);
I32 bbComplexPool_clearPool(bbPool_common* pool);
I32 bbComplexPool_new(struct bbPool_common* pool, void** address);
I32 bbComplexPool_delete(struct bbPool_common* pool, void* address);
I32 bbComplexPool_lookup(struct bbPool_common* pool, void** address, bbPool_Handle handle);
I32 bbComplexPool_reverseLookup(struct bbPool_common* pool, void* address, bbPool_Handle* handle);

I32 bbComplexPool_handleIsEqual(bbPool_Handle A, bbPool_Handle B){
    return (A.complex.collision == B.complex.collision) &&
           (A.complex.index == B.complex.index);
}

//internal function to get the header associated with the element
void* bbComplexPool_getHeader(bbPool_Header** element, void* address){
    //size_t offset =  offsetof(struct bbPool_Header, userData);
    bbPool_Header dummyElement;
    void* a = dummyElement;
    void* b = dummyElement.userData;
    size_t offset = b - a;
    *element = (address - offset);
    return f_Success;
}


I32 bbComplexPool_newPool(struct bbPool_common** pool, I32 sizeOf, I32 level1, I32 level2){

    bbComplexPool* Pool = malloc(sizeof(bbComplexPool) + level1 * sizeof(void*));
    bbAssert(Pool != NULL, "malloc returned null pointer");


    Pool->common.deletePool = bbComplexPool_deletePool;
    Pool->common.clearPool = bbComplexPool_clearPool;
    Pool->common.new = bbComplexPool_new;
    Pool->common.delete = bbComplexPool_delete;
    Pool->common.lookup = bbComplexPool_lookup;
    Pool->common.reverseLookup = bbComplexPool_reverseLookup;
    Pool->common.handleIsEqual = bbComplexPool_handleIsEqual;
    Pool->common.null.complex.collision = 0;
    Pool->common.null.complex.index = 0;
    //elements of pools will be 64 bit aligned
    I32 size = bbArith_roundUp(sizeOf, 8);

    Pool->common.sizeOf = size;
    Pool->level1 = level1;
    Pool->level2 = level2;
    Pool->available.head = Pool->common.null;
    Pool->available.tail = Pool->common.null;

    for (I32 i = 0; i < level1; i++){
        Pool->elements[i] = NULL;
    }
    *pool = Pool;

    return f_Success;

}

I32 bbComplexPool_deletePool(bbPool_common* pool){
    bbComplexPool* Pool = pool;
    for (I32 i = 0; i < Pool->level1; i++){
        free(Pool->elements[i]);
    }
    free(pool);
    return(f_Success);
}

I32 bbComplexPool_clearPool(bbPool_common* pool){
    bbComplexPool* Pool = pool;
    for(I32 i = 0; i < Pool->level1; i++){
        free(Pool->elements[i]);
        Pool->elements[i] = NULL;
    }
    Pool->available.head = Pool->common.null;
    Pool->available.tail = Pool->common.null;

    return f_Success;
}

// internal function to generate a new bbComplexPool_Handle
I32 bbComplexPool_newHandle(bbComplexPool* Pool, U32 lvl1index, U32 lvl2index, bbPool_Handle* handle){
    U32 index = lvl1index * Pool->level2 + lvl2index;
    U32 randint = rand();
    if (randint == 0) randint++;
    U32 collision = randint;
    bbPool_Handle Handle;
    Handle.complex.index = index;
    Handle.complex.collision = collision;
    *handle = Handle;
    return f_Success;
}
/// internal function to support expanding allocated space
I32 bbComplexPool_expand(bbComplexPool* pool){
    bbAssert(bbComplexPool_handleIsEqual(pool->available.head,
                            pool->common.null)
             && bbComplexPool_handleIsEqual(pool->available.tail,
                               pool->common.null),
             "expanding non-empty pool");

    U32 i = 0;
    while (pool->elements[i] != NULL){
        i++;
        bbAssert(i < pool->level1, "Pool full\n");

    }
    U8* level2 = calloc(pool->level2, sizeof(bbPool_Header) +  pool->common.sizeOf);
    bbAssert(level2 != NULL, "calloc failed");



    //element_0.prev = null
    //element_0.self = f(0)
    //element_0.next = f(1)
    //element_1.prev = element_0.self
    //element_1.self = element_0.next
    //element_1.next = f(2)
    //element_2.prev = element_1.self
    //element_2.self = element_1.next
    //element_2.next = f(3)

    //element_A = element_0
    //element_A.prev = null
    //element_A.self = f(0)
    //element_A.next = f(1)
    //element_B = element_1
    //element_B.prev = element_A.self
    //element_B.self = element_A.next
    //element_B.next = f(2)
    //element_A = element_B
    //element_B = element_2
    //element_B.prev = element_A.self
    //element_B.self = element_A.next
    //element_B.next = f(3)
    //element_A = element_B
    //element_B = element_3
    //element_B.prev = element_A.self
    //element_B.self = element_A.next
    //element_B.next = f(4)

    //...

    //element_A = element_B
    //element_B = element_N-2
    //element_B.prev = element_A.self
    //element_B.self = element_A.next
    //element_B.next = f(N-1)
    //element_A = element_B
    //element_B = element_N-1
    //element_B.prev = element_A.self
    //element_B.self = element_A.next
    //element_B.next = null

    U32 j = 0;
    bbPool_Header *element_A;
    bbPool_Header *element_B;
    U32 index;
    bbPool_Handle* handle;

    element_A = &level2[j * (sizeof(bbPool_Header) + pool->common.sizeOf)];
    element_A->list.prev = pool->common.null;
    bbComplexPool_newHandle(pool, i, j, &element_A->self);
    bbComplexPool_newHandle(pool, i, j+1, &element_A->list.next);

    j++;
    while(j<pool->level2 - 1) {
        element_B = &level2[j * (sizeof(bbPool_Header) + pool->common.sizeOf)];
        element_B->list.prev = element_A->self;
        element_B->self = element_A->list.next;
        bbComplexPool_newHandle(pool, i, j+1, &element_B->list.next);
        element_A = element_B;
        j++;
    }
    element_B = &level2[j * (sizeof(bbPool_Header) + pool->common.sizeOf)];
    element_B->list.prev = element_A->self;
    element_B->self = element_A->list.next;
    element_B->list.next = pool->common.null;

    element_A = &level2[0 * (sizeof(bbPool_Header) + pool->common.sizeOf)];

    pool->elements[i] = level2;
    pool->available.head = element_A->self;
    pool->available.tail = element_B->self;

    return f_Success;
}

I32 bbComplexPool_new(struct bbPool_common* pool, void** address){
    bbAssert(address != NULL, "where do we return the new element?\n");
    bbComplexPool* Pool = pool;
    if(bbComplexPool_handleIsEqual(Pool->available.head,
                      Pool->common.null)){
        bbAssert(bbComplexPool_handleIsEqual(Pool->available.tail,
                                Pool->common.null), "head/tail\n");
        bbComplexPool_expand(Pool);
    }
    if (bbComplexPool_handleIsEqual(Pool->available.head,
                       Pool->available.tail)){
        bbPool_Header* element;
        void* address;
        bbPool_Handle elementHandle = Pool->available.head;
        bbComplexPool_lookup(Pool, &address, elementHandle);
        bbComplexPool_getHeader(&element, address);

        bbAssert(bbComplexPool_handleIsEqual(element->list.prev, Pool->common.null)
                 && bbComplexPool_handleIsEqual(element->list.next, Pool->common.null),
                 "last element in list\n");
        Pool->available.head = Pool->common.null;
        Pool->available.tail = Pool->common.null;

        *address = &element->userData;

        return f_Success;
    }

    bbPool_Handle headHandle = Pool->available.head;
    void* headAddress;
    bbPool_Header* headHeader;
    bbComplexPool_lookup(Pool, &headAddress, headHandle);
    bbComplexPool_getHeader(&headHeader, headAddress);

    bbPool_Handle nextHandle = headHeader->list.next;
    void* nextAddress;
    bbPool_Header* nextHeader;
    bbComplexPool_lookup(Pool, &nextAddress, nextHandle);
    bbComplexPool_getHeader(&headHeader, nextAddress);

    nextHeader->list.prev = Pool->common.null;
    Pool->available.head = nextHandle;

    *address = headAddress;

    return f_Success;

}

I32 bbComplexPool_Handle_incrementCollision(bbPool_Handle* handle){
    U32 collision = handle->complex.collision;
    collision++;
    if (collision == 0) collision++;
    handle->complex.collision = collision;
    return f_Success;
}

I32 bbComplexPool_delete(struct bbPool_common* pool, void* address){
    bbComplexPool* Pool = pool;
    bbPool_Header* header;
    bbComplexPool_getHeader(&header, address);

    bbComplexPool_Handle_incrementCollision(&header->self);

    bbPool_Header* availableHead;
    void* available;
    bbComplexPool_lookup(pool, &available, Pool->available.head);
    bbComplexPool_getHeader(&availableHead, available);

    availableHead->list.prev = header->self;
    Pool->available.head = header->self;
    header->list.next = availableHead->self;
    header->list.prev = Pool->common.null;

    return f_Success;
}

I32 bbComplexPool_lookupHeader(struct bbPool_common* pool, void** address, bbPool_Handle handle){
    bbComplexPool* Pool = pool;
    U32 index = handle.complex.index;
    U32 collision = handle.complex.collision;
    U32 lvl1index = index / Pool->level2;
    U32 lvl2index = index % Pool->level2;

    U8* lvl2 = Pool->elements[lvl1index];
    bbPool_Header *element = &lvl2[lvl2index * (sizeof(bbPool_Header) + Pool->common.sizeOf)];
    bbPool_Handle* elementHandle = &element->self; //may or may not work :P

    bbAssert(handle.complex.collision == elementHandle->complex.collision, "handle "
                                                                           "collision\n");

    *address = element;
    return f_Success;
}

I32 bbComplexPool_lookup(struct bbPool_common* pool, void** address, bbPool_Handle handle){
    bbPool_Header* element;
    bbComplexPool_lookupHeader(pool, &element, handle);
    *address = &element->userData;

    return f_Success;
}

I32 bbComplexPool_reverseLookup(struct bbPool_common* pool, void* address, bbPool_Handle* handle){
    bbPool_Header* element = bbComplexPool_getHeader(address);
    *handle = element->self;

    return f_Success;
}