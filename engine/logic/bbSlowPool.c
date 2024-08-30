#include "engine/logic/bbSlowPool.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbRoundUp.h"
#include <stdlib.h>

#define bbSlowPool_collisionMask 0xC0000000
#define bbSlowPool_indexMask     0x3FFFFFFF
#define bbSlowPool_collisionBits 2
#define bbSlowPool_collision1    0x40000000

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

	//ensure elements are 64 bit aligned

	I32 size = bbRoundUp(
			(sizeOf > sizeof(bbSlowPool_Available)) ?
			sizeOf : sizeof(bbSlowPool_Available),
			8);

    Pool->p_sizeOf = size;
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
/// internal function to support expanding allocated space
I32 bbSlowPool_expand(bbSlowPool* pool){
	bbAssert(bbSlowPool_HandleIsNULL(pool->p_availableHead)
			 && bbSlowPool_HandleIsNULL(pool->p_availableTail),
			 "expanding non-empty pool");

	U32 i = 0;
	while (i < pool->p_level1 && pool->p_elements[i] != NULL){
		i++;
	}
	bbAssert(i < pool->p_level1, "Pool full\n");
	U8* level2 = calloc(pool->p_level2, pool->p_sizeOf);
	bbAssert(level2 != NULL, "calloc failed");

	// Assume pool empty, might change later:


    U32 level2index = 0;
	U32 index = i * pool->p_level2 + level2index;
	U8* elementU8;


	bbSlowPool_Available* element = level2;

	element->p_header.p_Pool = pool;
	element->p_header.p_Handle = bbSlowPool_collision1 | index;
	element->p_prev = bbSlowPool_NULL;
	element->p_next = bbSlowPool_collision1 | (index+1);

	U32 handle0 = element->p_header.p_Handle;

	for (level2index = 1; level2index< pool->p_level2 - 1; level2index++){
		index = i * pool->p_level2 + level2index;

		elementU8 = &level2[level2index * pool->p_sizeOf];


		element->p_header.p_Pool = pool;
		element->p_header.p_Handle = bbSlowPool_collision1 | index;
		element->p_prev = bbSlowPool_collision1 | (index-1);
		element->p_next = bbSlowPool_collision1 | (index+1);

	}

	level2index = pool->p_level2 - 1;
	elementU8 = &level2[level2index * pool->p_sizeOf];
	element = elementU8;

	element->p_header.p_Pool = pool;
	element->p_header.p_Handle = bbSlowPool_collision1 | index;
	element->p_prev = bbSlowPool_collision1 | (index-1);
	element->p_next = bbSlowPool_NULL;

	pool->p_availableTail = element->p_header.p_Handle;
	pool->p_availableHead = handle0;

	pool->p_elements[i] = level2;
}


I32 bbSlowPool_newA(void* pool, void** address){
	bbSlowPool* Pool = pool;
	if(bbSlowPool_HandleIsNULL(Pool->p_availableHead)){
		bbAssert(bbSlowPool_HandleIsNULL(Pool->p_availableTail),
				 "head/tail mismatch");
		bbSlowPool_expand(Pool);
	}

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
