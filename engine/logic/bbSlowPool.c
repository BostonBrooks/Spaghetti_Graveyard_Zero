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

U32 bbSlowPool_Handle_consolidate(U32 index, U32 collision){
    bbAssert(index <= bbSlowPool_collisionMask, "index out of bounds\n");
    bbAssert(collision < 1<<bbSlowPool_collisionBits,
             "collision out of bounds\n");

    return (index + (collision <<(32 - bbSlowPool_collisionBits)));
}

U32 bbSlowPool_Handle_incrementCollision(bbSlowPool_Handle* handle){

    U32 index = bbSlowPool_Handle_getIndex(*handle);
    U32 collision = bbSlowPool_Handle_getCollision(*handle);
    bbAssert(collision != 0, "handle should not be null\n");
    collision = collision % (1<<bbSlowPool_collisionBits - 1) + 1;
    *handle = bbSlowPool_Handle_consolidate(index, collision);
    return f_Success;
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
        Pool->p_elements[i] = NULL;
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


	bbSlowPool_Available* element = level2;

	element->p_header.p_Pool = pool;
	element->p_header.p_Handle = bbSlowPool_collision1 | index;
	element->p_prev = bbSlowPool_NULL;
	element->p_next = bbSlowPool_collision1 | (index+1);

	U32 handle0 = element->p_header.p_Handle;

	for (level2index = 1; level2index< pool->p_level2 - 1; level2index++){
		index = i * pool->p_level2 + level2index;

		elementU8 = &level2[level2index * pool->p_sizeOf];

        element = elementU8;
		element->p_header.p_Pool = pool;
		element->p_header.p_Handle = bbSlowPool_collision1 | index;
		element->p_prev = bbSlowPool_collision1 | (index-1);
		element->p_next = bbSlowPool_collision1 | (index+1);

	}

	level2index = pool->p_level2 - 1;
    index = i * pool->p_level2 + level2index;
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

    // At this point, the pool should be non-empty

    if(Pool->p_availableHead == Pool->p_availableTail){
        bbSlowPool_Handle element_handle = Pool->p_availableHead;

        bbSlowPool_Header* element;
        I32 flag = bbSlowPool_getAddress(Pool, &element, element_handle);
        bbAssert(flag == f_Success, "bad flag\n");
        Pool->p_availableHead = bbSlowPool_NULL;
        Pool->p_availableTail = bbSlowPool_NULL;

        *address = element;
        return f_Success;

    }

    bbSlowPool_Handle element_handle = Pool->p_availableHead;
    bbSlowPool_Available* element;
    I32 flag = bbSlowPool_getAddress(Pool, &element, element_handle);
    bbAssert(flag == f_Success, "bad flag\n");
    bbSlowPool_Handle next_handle = element->p_next;
    bbSlowPool_Available* next;
    flag = bbSlowPool_getAddress(Pool, &next, next_handle);

    bbAssert(flag == f_Success, "bad flag\n");
    Pool->p_availableHead = next_handle;
    next->p_prev = bbSlowPool_NULL;

    *address = element;
    return f_Success;

}

I32 bbSlowPool_newH(void* pool, bbSlowPool_Handle* handle) {
    bbSlowPool_Header* address;
    I32 flag = bbSlowPool_newA(pool, &address);
    bbAssert(flag == f_Success, "bad flag\n");
    *handle = address->p_Handle;
    return f_Success;


}

I32 bbSlowPool_deleteA(void* pool, void* address){
    bbSlowPool* Pool = pool;
    bbSlowPool_Available* element = address;
    bbSlowPool_Handle_incrementCollision(&element->p_header.p_Handle);

    if (bbSlowPool_HandleIsNULL(Pool->p_availableHead)){
        bbAssert(bbSlowPool_HandleIsNULL(Pool->p_availableTail),
                                         "head / tail\n");
        Pool->p_availableHead = element->p_header.p_Handle;
        Pool->p_availableTail = element->p_header.p_Handle;
        element->p_prev = bbSlowPool_NULL;
        element->p_next = bbSlowPool_NULL;
        return f_Success;
    }

    bbSlowPool_Handle head_handle = Pool->p_availableHead;
    bbSlowPool_Available* head;
    I32 flag = bbSlowPool_getAddress(Pool, &head, head_handle);
    bbAssert(flag == f_Success, "bad flag\n");

    head->p_prev = element->p_header.p_Handle;
    Pool->p_availableHead = element->p_header.p_Handle;
    element->p_prev = bbSlowPool_NULL;
    element->p_next = head->p_header.p_Handle;

    return f_Success;

}

I32 bbSlowPool_deleteH(void* pool, bbSlowPool_Handle handle){
    void* address;

    I32 flag = bbSlowPool_getAddress(pool, &address, handle);
    bbAssert(flag == f_Success, "bad flag\n");

    return bbSlowPool_deleteA(pool, address);
}

I32 bbSlowPool_getAddress(void* pool, void** address, bbSlowPool_Handle handle){

    if (bbSlowPool_HandleIsNULL(handle)) {
        *address = NULL;
        return f_None;
    }
    bbSlowPool* Pool = pool;
    U32 index = bbSlowPool_Handle_getIndex(handle);
    U32 collision = bbSlowPool_Handle_getCollision(handle);


    U32 lvl1_size = Pool->p_level1;
    U32 lvl2_size = Pool->p_level2;

    U32 lvl1_index = index / lvl2_size;

    bbAssert(lvl1_index < Pool->p_level1, "index out of bounds\n");

    U32 lvl2_index = index % lvl2_size;
    U32 lvl2_U8_index = lvl2_index * Pool->p_sizeOf;

    U8 *lvl2_elements = Pool->p_elements[lvl1_index];

    bbAssert(lvl2_elements != NULL, "accessing from empty pool level2\n");

    void* element = &lvl2_elements[lvl2_U8_index];

    bbSlowPool_Header* header = element;

    bbAssert(handle == header->p_Handle, "memory collision\n");

    *address = header;

    return f_Success;

}

I32 bbSlowPool_getHandle(void* pool, bbSlowPool_Handle* handle, void* address){
    bbSlowPool_Header* header = address;
    *handle = header->p_Handle;
    return f_Success;
}

// Address_getMap(), Address_getPool?
// Pool_getNum, Pool_getMap;
//
