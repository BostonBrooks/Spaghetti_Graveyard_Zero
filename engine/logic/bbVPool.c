#include "stdlib.h"
#include "engine/logic/bbVPool.h"

#include "bbTerminal.h"
#include "engine/logic/bbLeanPool.h"
#include "engine/logic/bbBloatedPool.h"
#include "engine/logic/bbFlag.h"
#include "engine/threadsafe/bbThreadedPool.h"





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