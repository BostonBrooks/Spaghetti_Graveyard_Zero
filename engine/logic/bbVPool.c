#include "stdlib.h"
#include "engine/logic/bbVPool.h"

#include "bbTerminal.h"
#include "engine/logic/bbLeanPool.h"
#include "engine/logic/bbBloatedPool.h"
#include "engine/logic/bbFlag.h"
#include "engine/threadsafe/bbThreadedPool.h"

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

bbFlag bbVPool_newThreaded(bbVPool** self, I32 sizeOf, I32 num)
{
	bbThreadedPool* ThreadedPool;
	bbThreadedPool_new(&ThreadedPool, sizeOf, num);
	bbVPool* pool = malloc(sizeof(bbVPool));
	bbAssert(pool != NULL, "bad malloc\n");
	pool->pool = ThreadedPool;
	pool->null = ThreadedPool->null;
	pool->sizeOf = ThreadedPool->sizeOf;
	pool->delete = (bbFlag (*)(void* pool)) bbThreadedPool_delete;
	pool->clear = NULL;
	pool->allocImpl = (bbFlag(*)(void* pool, void** address, char* file, int
	line)) bbThreadedPool_allocImpl;
	pool->free = (bbFlag(*)(void* pool, void* address)) bbThreadedPool_free;
	pool->lookup = (bbFlag (*)(void* pool, void** address, bbPool_Handle
	handle)) bbThreadedPool_lookup;
	pool->reverseLookup = NULL;
	pool->printHeader = NULL;
	pool->handleIsEqual = NULL;
	*self = pool;
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