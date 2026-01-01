#include "engine/logic/bbBloatedPool.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbArith.h"
#include "engine/logic/bbString.h"
#include "engine/logic/bbVPool.h"
#include <stddef.h>
#include <stdlib.h>

//TODO check for looking up an object not in use
//TODO check for invalid addresses

I32 bbBloatedPool_handleIsEqual(bbBloatedPool* UNUSED, bbPool_Handle A, bbPool_Handle B){
	return(A.bloated.collision == B.bloated.collision
	        && A.bloated.index == B.bloated.index);
};

#define IS_NULL(A) bbBloatedPool_handleIsEqual(NULL, A, pool->null)

bbFlag bbBloatedPool_print (bbBloatedPool* pool);

bbFlag bbBloatedPool_getHeader(bbBloatedPool_Header** header, void* address){
	size_t offset = offsetof(bbBloatedPool_Header, userData);
	*header = address - offset;


	bbBloatedPool_Header* hdr= address - offset;
	hdr->file[1] = 'z';
	return Success;
}

bbFlag bbVPool_newBloated(bbVPool** Pool, I32 sizeOf, I32 level1, I32 level2){
	bbBloatedPool* BloatedPool;
	bbBloatedPool_new(&BloatedPool, sizeOf, level1, level2);
	bbVPool* pool = malloc(sizeof(bbVPool));
	pool->pool = BloatedPool;
	pool->null = BloatedPool->null;
	pool->sizeOf = BloatedPool->sizeOf;
	pool->delete = (bbFlag (*)(void* pool)) bbBloatedPool_delete;
	pool->clear = (bbFlag (*)(void* pool)) bbBloatedPool_clear;
	pool->allocImpl = (bbFlag(*)(void* pool, void** address, char* file, int
	line)) bbBloatedPool_allocImpl;
	pool->free = (bbFlag(*)(void* pool, void* address)) bbBloatedPool_free;
	pool->lookup = (bbFlag (*)(void* pool, void** address, bbPool_Handle
	handle)) bbBloatedPool_lookup;
	pool->reverseLookup = (bbFlag (*)(void* pool, void* address,
			bbPool_Handle* handle)) bbBloatedPool_reverseLookup;
	pool->printHeader = (bbFlag (*)(void *, void *)) bbBloatedPool_printHeader;
	pool->handleIsEqual = (I32 (*)(void* USUSED, bbPool_Handle A,
			bbPool_Handle B)) bbBloatedPool_handleIsEqual;
	*Pool = pool;
	return Success;
}


bbFlag bbBloatedPool_new(bbBloatedPool** Pool, I32 sizeOf, I32 level1, I32
level2){
//We might get errors if leve1, level2 are too small
    if (level1 < 1) level1 = 1;
	if (level2 < 5) level2 = 5;

	bbBloatedPool* pool = malloc(sizeof(bbBloatedPool) + level1 * sizeof
            (void*));
	I32 size = bbArith_roundUp(sizeOf, 8);
	pool->null.bloated.index = 0;
	pool->null.bloated.collision = 0;

	pool->sizeOf = size;
	pool->level1 = level1;
	pool->level2 = level2;
	pool->available.head = pool->null;
	pool->available.tail = pool->null;
	for(I32 i = 0; i < level1; i++){
		pool->elements[i] = NULL;
	}
	*Pool = pool;
	return Success;
}

bbFlag bbBloatedPool_delete(bbBloatedPool* pool){
	for(I32 i = 0; i < pool->level1; i++){
		free(pool->elements[i]);
	}
	free(pool);
	return Success;
}

bbFlag bbBloatedPool_clear(bbBloatedPool* pool){
	for(I32 i = 0; i < pool->level1; i++){
		free(pool->elements[i]);
		pool->elements[i] = NULL;
	}
	pool->available.head = pool->null;
	pool->available.tail = pool->null;
	return Success;
}
bbFlag bbBloatedPool_newHandle(bbBloatedPool* Pool, U32 lvl1index, U32
lvl2index, bbPool_Handle* Handle){
	U32 index = lvl1index * Pool->level2 + lvl2index;
	U32 randint = rand();
	if (randint == 0) randint++;
	U32 collision = randint;
    //bbDebug("collision = %d\n", collision);
	bbPool_Handle handle;
	handle.bloated.index = index;
	handle.bloated.collision = collision;
	*Handle = handle;
	return Success;
}

bbFlag bbBloatedPool_expand(bbBloatedPool* pool){
	bbAssert(IS_NULL(pool->available.head)
			 && IS_NULL(pool->available.tail),
			 "expanding non-empty pool");
	U32 i = 0;
	while (pool->elements[i] != NULL){
		i++;
		bbAssert(i<pool->level1, "Pool full\n");
	}

    int* array = calloc(23, sizeof (int));



	U8* level2 = calloc(pool->level2,
                                sizeof(bbBloatedPool_Header)
                                + pool->sizeOf * sizeof(U8)); //why is
                                // this?

	bbAssert(level2 != NULL, "calloc failed\n");

	U32 j = 0;
	bbBloatedPool_Header* element_A;
	bbBloatedPool_Header* element_B;

	element_A = (bbBloatedPool_Header *)&level2[j * (sizeof(bbBloatedPool_Header) + pool->sizeOf)];
	element_A->list.prev = pool->null;
	bbBloatedPool_newHandle(pool, i, j, &element_A->self);
	bbBloatedPool_newHandle(pool, i, j+1, &element_A->list.next);

	j++;

	while(j<pool->level2 - 1){
		element_B = (bbBloatedPool_Header *) &level2[j * (sizeof(bbBloatedPool_Header) + pool->sizeOf)];
		element_B->list.prev = element_A->self;
		element_B->self = element_A->list.next;
		bbBloatedPool_newHandle(pool, i, j+1, &element_B->list.next);
		element_A = element_B;

		j++;
	}

	element_B = (bbBloatedPool_Header *) &level2[j * (sizeof(bbBloatedPool_Header) + pool->sizeOf)];
	element_B->list.prev = element_A->self;
	//TODO the next line is a guess
	element_B->self = element_A->list.next;
	element_B->list.next = pool->null;
	element_A = (bbBloatedPool_Header *)&level2[0 * (sizeof(bbBloatedPool_Header) + pool->sizeOf)];


	pool->elements[i] = level2;
	pool->available.head = element_A->self;
	pool->available.tail = element_B->self;

    /* print indices and collisions
	for (int k = 0; k < pool->level2; k++){

		element_A = (bbBloatedPool_Header *)&level2[k * (sizeof(bbBloatedPool_Header) + pool->sizeOf)];

		printf("prev = %d, self = %d, next = %d\n",
			   element_A->list.prev.bloated.index,
			   element_A->self.bloated.index,
			   element_A->list.next.bloated.index);

	}

	for (int k = 0; k < pool->level2; k++){

		element_A = (bbBloatedPool_Header *)&level2[k * (sizeof(bbBloatedPool_Header) + pool->sizeOf)];

		printf("Collisions: prev = %d, self = %d, next = %d\n",
			   element_A->list.prev.bloated.collision %100,
			   element_A->self.bloated.collision %100,
			   element_A->list.next.bloated.collision %100);

	}
*/


	return Success;
}

bbFlag bbBloatedPool_allocImpl(bbBloatedPool* pool, void** address, char* file, int line) {
    //bbBloatedPool_print (pool);
	bbAssert(address != NULL, "null return address\n");
	if (IS_NULL(pool->available.head)) {
		bbAssert(IS_NULL(pool->available.tail), "head/tail\n");
		bbBloatedPool_expand(pool);
	}
	if (bbBloatedPool_handleIsEqual(NULL, pool->available.head,
									pool->available.tail)) {
		bbBloatedPool_Header *element;
		void *elementAddress;
		bbPool_Handle elementHandle = pool->available.head;
		bbBloatedPool_lookup(pool, &elementAddress, elementHandle);
		bbBloatedPool_getHeader(&element, elementAddress);


		//If element is not in a list, element.next == NULL
		//If element is only element in list, element.next == element

		bbAssert(bbBloatedPool_handleIsEqual(NULL, elementHandle,
											 element->list.prev)
				 && bbBloatedPool_handleIsEqual(NULL, elementHandle,
												element->list.next),
				 "only element in list\n");

		pool->available.head = pool->null;
		pool->available.tail = pool->null;

		//list is only used when object not in use, could be stored in userData.
		element->list.prev = pool->null;
		element->list.next = pool->null;

		*address = &element->userData;
		return Success;
	}


	bbPool_Handle headHandle = pool->available.head;
	void *headAddress;
	bbBloatedPool_Header *headHeader;
	bbBloatedPool_lookup(pool, &headAddress, headHandle);
	bbBloatedPool_getHeader(&headHeader, headAddress);

	bbPool_Handle nextHandle = headHeader->list.next;
	void *nextAddress;
	bbBloatedPool_Header *nextHeader;
	bbBloatedPool_lookup(pool, &nextAddress, nextHandle);
	bbBloatedPool_getHeader(&nextHeader, nextAddress);

	bbAssert(nextHeader!=NULL,"found the bug yet?\n");
	nextHeader->list.prev = pool->null;

	//If element is not in a list, element.next == NULL
	//If element is only element in list, element.next == element
	if (bbBloatedPool_handleIsEqual(NULL, nextHeader->self, pool->available.tail)){
		nextHeader->list.prev = nextHeader->self;
		nextHeader->list.next = nextHeader->self;
	}

	headHeader->line = line;
	bbStr_setStr(headHeader->file, file, 33);

	pool->available.head = nextHandle;

	*address = headAddress;

	return Success;
}

bbFlag bbBloatedPool_Handle_incrementCollision(bbPool_Handle* handle){
	U32 collision = handle->bloated.collision;
	collision++;
	if(collision == 0) collision++;
	handle->bloated.collision = collision;
	return Success;
}

bbFlag bbBloatedPool_free(bbBloatedPool* pool, void* address){
	bbBloatedPool_Header* header;
	bbBloatedPool_getHeader(&header, address);
	bbBloatedPool_Handle_incrementCollision(&header->self);

	bbPool_Handle availableHandle = pool->available.head;

	if (IS_NULL(availableHandle)){
		pool->available.head = header->self;
		pool->available.tail = header->self;
		header->list.prev = header->self;
		header->list.next = header->self;
		return Success;
	}

	bbBloatedPool_Header* availableHeader;
	void* available;
	bbBloatedPool_lookup(pool, &available, availableHandle);
	bbBloatedPool_getHeader(&availableHeader, available);

	availableHeader->list.prev = header->self;
	pool->available.head = header->self;
	header->list.next = availableHeader->self;
	header->list.prev = pool->null;
	return Success;
}

bbFlag bbBloatedPool_lookupHeader(bbBloatedPool* pool, void** address, bbPool_Handle handle){
	U32 index = handle.bloated.index;
	U32 collision = handle.bloated.collision;
	U32 lvl1index = index / pool->level2;
	bbAssert(lvl1index < pool->level1, "index out of bounds\n");
	U32 lvl2index = index % pool->level2;
	U8* lvl2 = pool->elements[lvl1index];
	bbBloatedPool_Header *element = (bbBloatedPool_Header *)&lvl2[lvl2index * (sizeof(bbBloatedPool_Header) + pool->sizeOf)];
	bbPool_Handle elementHandle = element->self;
	//printf("col1 = %d, col2 = %d\n",handle.bloated.collision%100,
    //        elementHandle.bloated.collision%100);
	bbAssert(handle.bloated.collision == elementHandle.bloated.collision,
			 "handle collision\n");

	*address = element;
    return Success;
}

bbFlag bbBloatedPool_lookup(bbBloatedPool* pool, void** address, bbPool_Handle
handle){
	bbBloatedPool_Header* element;
	bbBloatedPool_lookupHeader(pool, (void**)&element, handle);
	*address = &element->userData;

	return Success;
}

bbFlag bbBloatedPool_reverseLookup(bbBloatedPool* pool, void* address, bbPool_Handle* handle){
	bbAssert(handle != NULL, "handle is NULL\n");
	bbAssert(address != NULL, "address is NULL\n");
	bbAssert(pool != NULL, "pool is NULL\n");
	bbBloatedPool_Header* element;
	bbBloatedPool_getHeader(&element, address);
	//handle->u64 = 0; handle is good, element is questionable
	//element->file[0] = 'z'; element is bad, cannot write to element
	*handle = element->self;
	return Success;
}
/*
 * typedef struct {
	bbPool_Handle null;
	U32 level1;
	U32 level2;
	U32 sizeOf;
	bbPool_List available;
	void* elements[];
} bbBloatedPool;
 */
bbFlag bbBloatedPool_print (bbBloatedPool* pool){
    bbPrintf("bbBloatedPool_print:\n");
    bbPrintf("null.index =               %d\n"
                       "null.collision =           %d\n", pool->null.bloated
    .index, pool->null.bloated.collision);
    bbPrintf("level1 =                   %d\n"
                       "level2 =                   %d\n", pool->level1,
             pool->level2);
    bbPrintf("sizeOf =                   %d\n", pool->sizeOf);
    bbPrintf("available.head.index =     %d\n", pool->available.head.bloated
    .index);
    bbPrintf("available.head.collision = %d\n", pool->available.head.bloated
    .collision);
    bbPrintf("available.tail.index =     %d\n", pool->available.tail.bloated
    .index);
    bbPrintf("available.tail.collision = %d\n", pool->available.tail.bloated
    .collision);

    return Success;
}

bbFlag bbBloatedPool_printHeader(bbBloatedPool* pool, void* address)
{
	bbBloatedPool_Header* header;
	bbBloatedPool_getHeader(&header, address);


	bbPrintf("bbBloatedPool_printHeader:\n");
	bbPrintf("FILE: %s, LINE: %d, INDEX: %d\n", header->file, header->line, header->self.bloated.index);
	return Success;
}