#include "engine/logic/bbLeanPool.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbArith.h"
#include "engine/logic/bbVPool.h"
#include <stdlib.h>

#define address_in_bounds(pool, address)\
    (pool->elements <= address && address < pool->elements + pool->num * pool->sizeOf)

bbFlag bbLeanPool_lookup(bbLeanPool* UNUSED, void** address, bbPool_Handle handle){
	
	*address = handle.ptr;
	return Success;
}

bbFlag bbLeanPool_reverseLookup(bbLeanPool* UNUSED, void* address, bbPool_Handle* handle){
	
	handle->ptr = address;
	return Success;
}

void* bbLeanPool_fromInt(bbLeanPool* pool, int i){

	bbAssert(i>= 0 && i < pool->num, "index out of bounds\n")
	void* element =  &pool->elements[i * pool->sizeOf];
	return element;

}

I32 bbLeanPool_toInt(bbLeanPool* pool, void* element)
{
//TODO - doesnt work :/
	void* start_address = &pool->elements[0];
	U64 offset = element - start_address;


	return offset;


}

bbFlag bbVPool_newLean(bbVPool** Pool, I32 sizeOf, I32 num){
	bbLeanPool* LeanPool;
	bbLeanPool_new(&LeanPool, sizeOf, num);
	bbAssert(LeanPool != NULL,"bad bbLeanPool_new\n")
	bbVPool* pool = malloc(sizeof(bbVPool));
	bbAssert(pool != NULL, "bad malloc\n");
	pool->pool = LeanPool;
	pool->null = LeanPool->null;
	pool->sizeOf = LeanPool->sizeOf;
	pool->delete = (bbFlag (*)(void* pool)) bbLeanPool_delete;
	pool->clear = (bbFlag (*)(void* pool)) bbLeanPool_clear;
	pool->allocImpl = (bbFlag(*)(void* pool, void** address, char* file, int
	line)) bbLeanPool_allocImpl;
	pool->free = (bbFlag(*)(void* pool, void* address)) bbLeanPool_free;
	pool->lookup = (bbFlag (*)(void* pool, void** address, bbPool_Handle
	handle)) bbLeanPool_lookup;
	pool->reverseLookup = (bbFlag (*)(void* pool, void* address,
			bbPool_Handle* handle)) bbLeanPool_reverseLookup;
	pool->printHeader = (bbFlag (*)(void *, void *)) bbLeanPool_printHeader;
	pool->handleIsEqual = (I32 (*)(void* USUSED, bbPool_Handle A,
			bbPool_Handle B)) bbLeanPool_handleIsEqual;
	*Pool = pool;
	return Success;
}

bbFlag bbLeanPool_new(bbLeanPool** Pool, I32 sizeOf, I32 num){

	//we might get an error if num is too small
	if (num < 2) num = 2;

	I32 size = bbArith_roundUp(sizeOf, 8);
	size = bbArith_max(sizeof(bbLeanPool_Header), size);
	bbLeanPool* pool = malloc(sizeof(bbLeanPool)+ num * size);
	pool->null.ptr = NULL;
	pool->num = num;
	pool->sizeOf = size;
    pool->inUse = 0;

/*
	element0.prev = NULL
 	element0.next = bbLeanPool_fromInt 1
 	element1.prev = bbLeanPool_fromInt 0
 	element1.next = bbLeanPool_fromInt 2
 	element2.prev = bbLeanPool_fromInt 1
 	element2.next = bbLeanPool_fromInt 3
 	element3.prev = bbLeanPool_fromInt 2
 	element3.next = NULL
*/

	bbLeanPool_Header* element;
	element = bbLeanPool_fromInt(pool, 0);
	element->prev.ptr = NULL;
	element->next.ptr = bbLeanPool_fromInt(pool, 1);

	for (I32 i = 1; i < num-1; i++){
		element = bbLeanPool_fromInt(pool, i);
		element->prev.ptr = bbLeanPool_fromInt(pool, i-1);
		element->next.ptr = bbLeanPool_fromInt(pool, i+1);
	}

	element = bbLeanPool_fromInt(pool, num-1);
	element->prev.ptr = bbLeanPool_fromInt(pool, num - 2);
	element->next.ptr = NULL;

	pool->available.head.ptr = bbLeanPool_fromInt(pool, 0);
	pool->available.tail.ptr = bbLeanPool_fromInt(pool, num-1);

	*Pool = pool;

	return Success;
 }
bbFlag bbLeanPool_delete(bbLeanPool* pool){
	
	free(pool);
	return Success;
}

bbFlag bbLeanPool_clear(bbLeanPool* pool){
	
	I32 num = pool->num;
    pool->inUse = 0;
	bbLeanPool_Header* element;
	element = bbLeanPool_fromInt(pool, 0);
	element->prev.ptr = NULL;
	element->next.ptr = bbLeanPool_fromInt(pool, 1);

	for (I32 i = 1; i < num-1; i++){
		element = bbLeanPool_fromInt(pool, i);
		element->prev.ptr = bbLeanPool_fromInt(pool, i-1);
		element->next.ptr = bbLeanPool_fromInt(pool, i+1);
	}

	element = bbLeanPool_fromInt(pool, num-1);
	element->prev.ptr = bbLeanPool_fromInt(pool, num - 2);
	element->next.ptr = NULL;

	pool->available.head.ptr = bbLeanPool_fromInt(pool, 0);
	pool->available.tail.ptr = bbLeanPool_fromInt(pool, num-1);

	return Success;
}

bbFlag bbLeanPool_allocImpl(bbLeanPool* pool, void** address, char* file, int line){
	

	bbAssert(address != NULL, "null return address\n");
	bbAssert(pool->available.head.ptr != NULL, "pool full\n");
	bbLeanPool_Header* header = pool->available.head.ptr;

    pool->inUse += 1;
	if (pool->available.head.ptr == pool->available.tail.ptr){
		//last available element
		bbLeanPool_Header* element = pool->available.tail.ptr;
		pool->available.head.ptr = NULL;
		pool->available.tail.ptr = NULL;

        *address = element;
		return Success;
	}
	bbLeanPool_Header* headHeader = pool->available.head.ptr;
	bbLeanPool_Header* nextHeader = headHeader->next.ptr;
	pool->available.head.ptr = nextHeader;
	nextHeader->prev.ptr = NULL;

	if (pool->available.head.ptr == pool->available.tail.ptr){
		nextHeader->prev.ptr = nextHeader;
		nextHeader->next.ptr = nextHeader;
	}

	*address = headHeader;

	return Success;

}

bbFlag bbLeanPool_free(bbLeanPool* pool, void* address){
	
	bbLeanPool_Header* element = address;
	bbLeanPool_Header* available = pool->available.head.ptr;

    pool->inUse -= 1;
	// if pool is empty
	if (available == NULL){
		bbAssert(pool->available.head.ptr == NULL, "head/tail\n");
		pool->available.head.ptr = element;
		pool->available.tail.ptr = element;
		element->prev.ptr = element;
		element->next.ptr = element;

		return Success;
	}

	available->prev.ptr = element;
	element->next.ptr = available;
	element->prev.ptr = NULL;
	pool->available.head.ptr = element;

	return Success;
}

I32 bbLeanPool_handleIsEqual(bbLeanPool* USUSED, bbPool_Handle A, bbPool_Handle B){
	return (A.ptr == B.ptr);
}


bbFlag bbLeanPool_printHeader(bbLeanPool* pool, void* address)
{
	I32 index = bbLeanPool_toInt(pool, address);
	bbPrintf("bbLeanPool_printHeader:\n");
	bbPrintf("INDEX: %d\n", index);

	return Success;
}