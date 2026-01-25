/** a virtual pool is a wrapper for a more concrete kind of pool*/

#ifndef BBVPOOL_H
#define BBVPOOL_H

#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbFlag.h"

typedef enum
{
	VPoolType_lean,
	vPoolType_bloated
} bbVPool_type;

typedef struct {
	bbPool_Handle null;
	bbVPool_type type;
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

#define bbVPool_elementInBounds(pool, address){\
    if(pool->type == VPoolType_lean){\
      bbLeanPool* Pool = pool->pool;\
        bbAssert( (void*)address >= (void*)&Pool->elements[0], "Address out of bounds\n");\
        bbAssert( (void*)address <= (void*)&Pool->elements[(Pool->num-1)*Pool->sizeOf], "Address out of bounds\n");\
    }\
}\

#define bbVPool_handleValid(pool, handle){\
    if(pool->type == VPoolType_lean){\
        bbLeanPool* vPool = pool->pool;\
        bbLeanPool_handleValid(vPool, handle);\
    }\
}

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