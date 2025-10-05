#include "stdlib.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbLeanPool.h"
#include "engine/logic/bbBloatedPool.h"
#include "engine/logic/bbFlag.h"
bbFlag bbVPool_newLean(bbVPool** pool, I32 sizeOf, I32 num){
	bbLeanPool* LeanPool;
	bbLeanPool_new(&LeanPool, sizeOf, num);
	bbVPool* Pool = malloc(sizeof(*Pool));
	Pool->pool = LeanPool;
	Pool->null = LeanPool->null;
	Pool->sizeOf = LeanPool->sizeOf;
	Pool->delete = (bbFlag (*)(void* pool)) bbLeanPool_delete;
	Pool->clear = (bbFlag (*)(void* pool)) bbLeanPool_clear;
	Pool->allocImpl = (bbFlag(*)(void* pool, void** address, char* file, int line)) bbLeanPool_allocImpl;
	Pool->free = (bbFlag(*)(void* pool, void* address)) bbLeanPool_free;
	Pool->lookup = (bbFlag (*)(void* pool, void** address, bbPool_Handle handle)) bbLeanPool_lookup;
	Pool->reverseLookup = (bbFlag (*)(void* pool, void* address, bbPool_Handle* handle)) bbLeanPool_reverseLookup;
	Pool->printHeader = (bbFlag (*)(void *, void *)) bbLeanPool_printHeader;
	Pool->handleIsEqual = (I32 (*)(void* USUSED, bbPool_Handle A, bbPool_Handle B)) bbLeanPool_handleIsEqual;
	*pool = Pool;
	return Success;
}

bbFlag bbVPool_newBloated(bbVPool** pool, I32 sizeOf, I32 level1, I32 level2){
	bbBloatedPool* BloatedPool;
	bbBloatedPool_new(&BloatedPool, sizeOf, level1, level2);
	bbVPool* Pool = malloc(sizeof(*Pool));
	Pool->pool = BloatedPool;
	Pool->null = BloatedPool->null;
	Pool->sizeOf = BloatedPool->sizeOf;
	Pool->delete = (bbFlag (*)(void* pool)) bbBloatedPool_delete;
	Pool->clear = (bbFlag (*)(void* pool)) bbBloatedPool_clear;
	Pool->allocImpl = (bbFlag(*)(void* pool, void** address, char* file, int line)) bbBloatedPool_allocImpl;
	Pool->free = (bbFlag(*)(void* pool, void* address)) bbBloatedPool_free;
	Pool->lookup = (bbFlag (*)(void* pool, void** address, bbPool_Handle handle)) bbBloatedPool_lookup;
	Pool->reverseLookup = (bbFlag (*)(void* pool, void* address, bbPool_Handle* handle)) bbBloatedPool_reverseLookup;
	Pool->printHeader = (bbFlag (*)(void *, void *)) bbBloatedPool_printHeader;
	Pool->handleIsEqual = (I32 (*)(void* USUSED, bbPool_Handle A, bbPool_Handle B)) bbBloatedPool_handleIsEqual;
	*pool = Pool;
	return Success;
}

//TODO small functions, consider using static functions in the header
bbFlag bbVPool_delete(bbVPool* pool){
    bbFlag flag = pool->delete(pool->pool);
	free(pool);
	return flag;
}


bbFlag bbVPool_clear(bbVPool* pool) {
	return pool->clear(pool->pool);
}

bbFlag bbVPool_allocImpl(bbVPool* pool, void** address, char* file, int line) {
	return pool->allocImpl(pool->pool, address, file, line);
}

bbFlag bbVPool_free(bbVPool* pool, void* address) {
	return pool->free(pool->pool, address);
}
bbFlag bbVPool_lookup(bbVPool* pool, void** address, bbPool_Handle handle) {
	return pool->lookup(pool->pool, address, handle);
}
bbFlag bbVPool_reverseLookup(bbVPool* pool, void* address, bbPool_Handle* handle){
	return pool->reverseLookup(pool->pool, address, handle);
}

bbFlag bbVPool_printHeader(bbVPool* pool, void* address)
{
	return pool->printHeader(pool, address);
}
I32 bbVPool_handleIsEqual(bbVPool* pool, bbPool_Handle A, bbPool_Handle B){
	return pool->handleIsEqual(pool, A, B);
}