/** a virtual pool is a wrapper for a more concrete kind of pool*/

#ifndef BBVPOOL_H
#define BBVPOOL_H

#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbFlag.h"

typedef struct {
	bbPool_Handle null;
	U32 sizeOf;
	void* pool;
	//I32 (*new)(void** pool, I32 sizeOf, I32 num);
    bbFlag (*delete)(void* pool);
    bbFlag (*clear)(void* pool);
    bbFlag (*allocImpl)(void* pool, void** address, char* file, int line);
    bbFlag (*free)(void* pool, void* address);
    bbFlag (*lookup)(void* pool, void** address, bbPool_Handle handle);
    bbFlag (*reverseLookup)(void* pool, void* address, bbPool_Handle* handle);
	bbFlag (*printHeader)(void* pool, void* address);
    I32 (*handleIsEqual)(void* USUSED, bbPool_Handle A, bbPool_Handle B);

} bbVPool;



#define bbVPool_alloc(pool, address)\
bbVPool_allocImpl(pool, address, __FILE_NAME__, __LINE__);

//create new pool element with the same handle as that given
//bbFlag bbVPool_newFromHande(bbVPool* pool, void** address, bbPool_Handle handle);

//I32 bbVPool_new(bbVPool** pool, I32 sizeOf, I32 num);
bbFlag bbVPool_delete(bbVPool* pool);
bbFlag bbVPool_clear(bbVPool* pool);
bbFlag bbVPool_allocImpl(bbVPool* pool, void** address, char* file, int line);
bbFlag bbVPool_free(bbVPool* pool, void* address);
bbFlag bbVPool_lookup(bbVPool* pool, void** address, bbPool_Handle handle);
bbFlag bbVPool_reverseLookup(bbVPool* pool, void* address, bbPool_Handle* handle);
bbFlag bbVPool_printHeader(bbVPool* pool, void* address);

//returns result of ==
I32 bbVPool_handleIsEqual(bbVPool* pool, bbPool_Handle A, bbPool_Handle B);


#endif // BBVPOOL_H