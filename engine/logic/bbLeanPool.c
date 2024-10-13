#include "engine/logic/bbLeanPool.h"
#include "engine/logic/bbFlags.h"
#include "engine/logic/bbArith.h"
#include <stdlib.h>

#define address_in_bounds(pool, address)\
    (pool->elements <= address && address < pool->elements + pool->num * pool->sizeOf)

I32 bbLeanPool_lookup(bbLeanPool* UNUSED, void** address, bbPool_Handle handle){
	
	*address = handle.ptr;
	return f_Success;
}

I32 bbLeanPool_reverseLookup(bbLeanPool* UNUSED, void* address, bbPool_Handle* handle){
	
	handle->ptr = address;
	return f_Success;
}

void* bbLeanPool_fromInt(bbLeanPool* pool, int i){

	bbAssert(i>= 0 && i < pool->num, "index out of bounds\n")
	void* element =  &pool->elements[i * pool->sizeOf];
	return element;

}

I32 bbLeanPool_new(bbLeanPool** pool, I32 sizeOf, I32 num){

	//we might get an error if num is too small
	if (num < 2) num = 2;

	I32 size = bbArith_roundUp(sizeOf, 8);
	size = bbArith_max(sizeof(bbLeanPool_Header), size);
	bbLeanPool* Pool = malloc(sizeof(bbLeanPool)+ num * size);
	Pool->null.ptr = NULL;
	Pool->num = num;
	Pool->sizeOf = size;

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
	element = bbLeanPool_fromInt(Pool, 0);
	element->prev.ptr = NULL;
	element->next.ptr = bbLeanPool_fromInt(Pool, 1);

	for (I32 i = 1; i < num-1; i++){
		element = bbLeanPool_fromInt(Pool, i);
		element->prev.ptr = bbLeanPool_fromInt(Pool, i-1);
		element->next.ptr = bbLeanPool_fromInt(Pool, i+1);
	}

	element = bbLeanPool_fromInt(Pool, num-1);
	element->prev.ptr = bbLeanPool_fromInt(Pool, num - 2);
	element->next.ptr = NULL;

	Pool->available.head.ptr = bbLeanPool_fromInt(Pool, 0);
	Pool->available.tail.ptr = bbLeanPool_fromInt(Pool, num-1);

	*pool = Pool;

	return f_Success;
 }
I32 bbLeanPool_delete(bbLeanPool* pool){
	
	free(pool);
	return f_Success;
}

I32 bbLeanPool_clear(bbLeanPool* pool){
	
	I32 num = pool->num;
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

	return f_Success;
}

I32 bbLeanPool_allocImpl(bbLeanPool* pool, void** address, char* file, int line){
	

	bbAssert(address != NULL, "null return address\n");
	bbAssert(pool->available.head.ptr != NULL, "pool full\n");
	bbLeanPool_Header* header = pool->available.head.ptr;

	if (pool->available.head.ptr == pool->available.tail.ptr){
		//last available element
		bbLeanPool_Header* element = pool->available.tail.ptr;
		pool->available.head.ptr = NULL;
		pool->available.tail.ptr = NULL;

		return f_Success;
	}
	bbLeanPool_Header* headHeader = pool->available.head.ptr;
	bbLeanPool_Header* nextHeader = headHeader->next.ptr;
	pool->available.head.ptr = nextHeader;
	nextHeader->prev.ptr = NULL;

	if (pool->available.tail.ptr == nextHeader){
		nextHeader->prev.ptr = nextHeader;
		nextHeader->next.ptr = nextHeader;
	}

	*address = headHeader;

	return f_Success;

}

I32 bbLeanPool_free(bbLeanPool* pool, void* address){
	
	bbLeanPool_Header* element = address;
	bbLeanPool_Header* available = pool->available.head.ptr;

	// if pool is empty
	if (available == NULL){
		bbAssert(pool->available.head.ptr == NULL, "head/tail\n");
		pool->available.head.ptr = element;
		pool->available.tail.ptr = element;
		element->prev.ptr = element;
		element->next.ptr = element;

		return f_Success;
	}

	available->prev.ptr = element;
	element->next.ptr = available;
	element->prev.ptr = NULL;
	pool->available.head.ptr = element;

	return f_Success;
}

I32 bbLeanPool_handleIsEqual(bbLeanPool* USUSED, bbPool_Handle A, bbPool_Handle B){
	return (A.ptr == B.ptr);
}
