#include <stdlib.h>
#include "bbPool_old.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbRoundUp.h"
#include "engine/logic/bbIntTypes.h"

#define bbPool_collisionMask 0xC0000000
#define bbPool_indexMask     0x3FFFFFFF
#define bbPool_collisionBits 2
#define bbPool_collision1    0x40000000

I32 bbPool_HandleIsNULL (bbPool_Handle handle){
    if((handle & bbPool_collisionMask) == 0) return 1;
    return 0;
}

I32 bbPool_newPool(bbPool** pool, I32 sizeOf, I32 level1, I32 level2){
    bbPool* Pool = malloc(sizeof(bbPool) + level1 * sizeof(void*));
    bbAssert(Pool!= NULL, "malloc failed!\n");
    I32 size = bbRoundUp(
            (sizeOf > sizeof(bbPool_Available))?
            sizeOf : sizeof(bbPool_Available),
            8);

    Pool->p_sizeOf = size;
    Pool->p_level1 = level1;
    Pool->p_level2 = level2;
    Pool->p_list.head = bbPool_NULL;
    Pool->p_list.tail = bbPool_NULL;

    for (I32 i = 0; i < level1; i++){
        Pool->p_elements[i] = NULL;
    }
    *pool = Pool;

    return f_Success;
}

I32 bbPool_deletePool(bbPool* pool){
    for(I32 i = 0; i < pool->p_level1; i++){
        free(pool->p_elements[i]);
    }
    free(pool);
    return f_Success;

}


I32 bbPool_clearPool(bbPool* pool){
    for(I32 i = 0; i < pool->p_level1; i++){
        free(pool->p_elements[i]);
    }
    pool->p_list.head = bbPool_NULL;
    pool->p_list.tail = bbPool_NULL;
    return f_Success;

}
I32 bbPool_expand(bbPool* pool){
    bbAssert(bbPool_HandleIsNULL(pool->p_list.head)
             && bbPool_HandleIsNULL(pool->p_list.tail),
             "expanding non-empty pool");

    U32 i = 0;
    while (pool->p_elements[i] != NULL){
        i++;
        bbAssert(i < pool->p_level1, "Pool full\n");

    }
    bbPrintf("lvl1 = %d\n", i);
    U8* level2 = calloc(pool->p_level2, pool->p_sizeOf);
    bbAssert(level2 != NULL, "calloc failed");

    // Assume pool empty, might change later:


    U32 level2index = 0;
    U32 index = i * pool->p_level2 + level2index;
    U8* elementU8;


    bbPool_Available* element = level2;

    element->p_header.p_self = bbPool_collision1 | index;
    element->p_header.p_InUse = false;
    element->p_list.prev = bbPool_NULL;
    element->p_list.next = bbPool_collision1 | (index+1);

    bbPool_Handle handle0 = element->p_header.p_self;

    for (level2index = 1; level2index< pool->p_level2 - 1; level2index++){
        index = i * pool->p_level2 + level2index;

        elementU8 = &level2[level2index * pool->p_sizeOf];

        element = elementU8;
        element->p_header.p_self = bbPool_collision1 | index;
        element->p_list.prev = bbPool_collision1 | (index-1);
        element->p_list.next = bbPool_collision1 | (index+1);

    }

    level2index = pool->p_level2 - 1;
    index = i * pool->p_level2 + level2index;
    elementU8 = &level2[level2index * pool->p_sizeOf];
    element = elementU8;

    element->p_header.p_self = bbPool_collision1 | index;
    element->p_list.prev = bbPool_collision1 | (index-1);
    element->p_list.next = bbPool_NULL;

    pool->p_list.tail = element->p_header.p_self;
    pool->p_list.head = handle0;

    pool->p_elements[i] = level2;
    return f_Success;
}

I32 bbPool_new(bbPool* pool, void** address, bbPool_Handle* handle){
    bbAssert(address != NULL || handle != NULL,
             "cant return by reference\n");

    if (bbPool_HandleIsNULL(pool->p_list.head)){
        bbAssert(bbPool_HandleIsNULL(pool->p_list.tail),
                 "head/tail\n");
        bbPool_expand(pool);
    }

    if(pool->p_list.head == pool->p_list.tail){

    }
}
