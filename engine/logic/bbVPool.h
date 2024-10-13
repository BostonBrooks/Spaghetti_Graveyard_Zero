/** a virtual pool is a wrapper for a more concrete kind of pool*/

#include "engine/logic/bbPoolHandle.h"
typedef struct {
	bbPool_Handle null;
	U32 sizeOf;
	void* pool;
	//I32 (*new)(void** pool, I32 sizeOf, I32 num);
	I32 (*delete)(void* pool);
	I32 (*clear)(void* pool);
	I32 (*allocImpl)(void* pool, void** address, char* file, int line);
	I32 (*free)(void* pool, void* address);
	I32 (*lookup)(void* pool, void** address, bbPool_Handle handle);
	I32 (*reverseLookup)(void* pool, void* address, bbPool_Handle* handle);
	I32 (*handleIsEqual)(void* USUSED, bbPool_Handle A, bbPool_Handle B);

} bbVPool;

I32 bbVPool_newLean(bbVPool** pool, I32 sizeOf, I32 num);
I32 bbVPool_newBloated(bbVPool** pool, I32 sizeOf, I32 level1, I32 level2);

#define bbVPool_alloc(pool, address)\
bbVPool_allocImpl(pool, address, __FILE_NAME__, __LINE__);;

//I32 bbVPool_new(bbVPool** pool, I32 sizeOf, I32 num);
I32 bbVPool_delete(bbVPool* pool);
I32 bbVPool_clear(bbVPool* pool);
I32 bbVPool_allocImpl(bbVPool* pool, void** address, char* file, int line);
I32 bbVPool_free(bbVPool* pool, void* address);
I32 bbVPool_lookup(bbVPool* pool, void** address, bbPool_Handle handle);
I32 bbVPool_reverseLookup(bbVPool* pool, void* address, bbPool_Handle* handle);
I32 bbVPool_handleIsEqual(bbVPool* pool, bbPool_Handle A, bbPool_Handle B);
