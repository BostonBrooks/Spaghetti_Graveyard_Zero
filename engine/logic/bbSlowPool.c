#include "engine/logic/bbSlowPool.h"
#include "engine/logic/bbTerminal.h"
#include <stdlib.h>

#define bbSlowPool_collisionMask 0xE0000000
#define bbSlowPool_indexMask     0x1FFFFFFF
#define bbSlowPool_collisionBits 3

U32 bbSlowPool_Handle_getIndex(bbSlowPool_Handle handle){
    U32 index = handle & bbSlowPool_indexMask;
    return index;
}

U32 bbSlowPool_Handle_getCollision(bbSlowPool_Handle handle){
    U32 collision = handle >> (32 - bbSlowPool_collisionBits);
}

I32 bbSlowPool_HandleIsNULL (bbSlowPool_Handle handle){
    if((handle & bbSlowPool_collisionMask) == 0) return 1;
    return 0;
}


I32 bbSlowPool_newPool(void** pool, I32 sizeOf, I32 level1, I32 level2, I32
map){
    bbSlowPool* Pool = malloc(sizeof(bbSlowPool) + level1 * sizeof(void*));
    bbAssert(Pool != NULL, "malloc returned null pointer");
    Pool->p_map = map;
    Pool->p_sizeOf = sizeOf;
    Pool->p_level1 = level1;
    Pool->p_level2 = level2;
    Pool->p_availableHead = bbSlowPool_NULL;
    Pool->p_availableTail = bbSlowPool_NULL;

    for (I32 i = 0; i < level1; i++){
        Pool->p_elements[i] = NULL;
    }
    *pool = Pool;

    return f_Success;
}

I32 bbSlowPool_deletePool(void* pool) {
    bbSlowPool* Pool = pool;
    for(I32 i = 0; i < Pool->p_level1; i++){
        free(Pool->p_elements[i]);
    }
    free(pool);
    return f_Success;
}

I32 bbSlowPool_clearPool(void* pool){
    bbSlowPool* Pool = pool;
    for(I32 i = 0; i < Pool->p_level1; i++){
        free(Pool->p_elements[i]);
    }
    Pool->p_availableHead = bbSlowPool_NULL;
    Pool->p_availableTail = bbSlowPool_NULL;
    return f_Success;
}




I32 bbSlowPool_newA(void* pool, void** address){

}

I32 bbSlowPool_newH(void* pool, bbSlowPool_Handle* handle) {  }

I32 bbSlowPool_deleteA(void* pool, void* address){}

I32 bbSlowPool_deleteH(void* pool, bbSlowPool_Handle handle){}

I32 bbSlowPool_getAddress(void* pool, void** address, bbSlowPool_Handle handle){

}

I32 bbSlowPool_getHandle(void* pool, bbSlowPool_Handle* handle, void* address){}

// Address_getMap(), Address_getPool?
// Pool_getNum, Pool_getMap;
//
