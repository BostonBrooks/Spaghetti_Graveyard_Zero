#include "stdlib.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbLeanPool.h"
#include "engine/logic/bbBloatedPool.h"
#include "engine/logic/bbFlag.h"
I32 bbVPool_newLean(bbVPool** pool, I32 sizeOf, I32 num){
	bbLeanPool* LeanPool;
	bbLeanPool_new(&LeanPool, sizeOf, num);
	bbVPool* Pool = malloc(sizeof(*Pool));
	Pool->pool = LeanPool;
	Pool->null = LeanPool->null;
	Pool->sizeOf = LeanPool->sizeOf;
	Pool->delete = bbLeanPool_delete;
	Pool->clear = bbLeanPool_clear;
	Pool->allocImpl = bbLeanPool_allocImpl;
	Pool->free = bbLeanPool_free;
	Pool->lookup = bbLeanPool_lookup;
	Pool->reverseLookup = bbLeanPool_reverseLookup;
	Pool->handleIsEqual = bbLeanPool_handleIsEqual;
	*pool = Pool;
	return f_Success;
}

I32 bbVPool_newBloated(bbVPool** pool, I32 sizeOf, I32 level1, I32 level2){
	bbBloatedPool* BloatedPool;
	bbBloatedPool_new(&BloatedPool, sizeOf, level1, level2);
	bbVPool* Pool = malloc(sizeof(*Pool));
	Pool->pool = BloatedPool;
	Pool->null = BloatedPool->null;
	Pool->sizeOf = BloatedPool->sizeOf;
	Pool->delete = bbBloatedPool_delete;
	Pool->clear = bbBloatedPool_clear;
	Pool->allocImpl = bbBloatedPool_allocImpl;
	Pool->free = bbBloatedPool_free;
	Pool->lookup = bbBloatedPool_lookup;
	Pool->reverseLookup = bbBloatedPool_reverseLookup;
	Pool->handleIsEqual = bbBloatedPool_handleIsEqual;
	*pool = Pool;
	return f_Success;
}

//TODO small functions, consider using static functions in the header
I32 bbVPool_delete(bbVPool* pool){
	I32 flag = pool->delete(pool->pool);
	free(pool);
	return flag;
}


I32 bbVPool_clear(bbVPool* pool) {
	return pool->clear(pool->pool);
}

I32 bbVPool_allocImpl(bbVPool* pool, void** address, char* file, int line) {
	return pool->allocImpl(pool->pool, address, file, line);
}

I32 bbVPool_free(bbVPool* pool, void* address) {
	return pool->free(pool->pool, address);
}
I32 bbVPool_lookup(bbVPool* pool, void** address, bbPool_Handle handle) {
	return pool->lookup(pool->pool, address, handle);
}
I32 bbVPool_reverseLookup(bbVPool* pool, void* address, bbPool_Handle* handle){
	return pool->reverseLookup(pool->pool, address, handle);
}
I32 bbVPool_handleIsEqual(bbVPool* pool, bbPool_Handle A, bbPool_Handle B){
	return pool->handleIsEqual(pool, A, B);
}