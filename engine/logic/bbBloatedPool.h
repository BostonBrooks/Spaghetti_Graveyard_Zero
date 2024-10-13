/** a bloated pool is one that implements all possible features
 * and checks */

#ifndef BBBLOATEDPOOL_H
#define BBBLOATEDPOOL_H

#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbPoolHandle.h"

#include <stdalign.h>
#include <stdbool.h>

typedef struct {
	bbPool_Handle null;
	U32 level1;
	U32 level2;
	U32 sizeOf;
	bbPool_List available;
	void* elements[];
} bbBloatedPool;

typedef struct {
	bbPool_Handle self;
	//this is only used when object not in use, could be stored in userData.
	bbPool_ListElement list;
	bool inUse;
	I32 line;
	char file[33];
	alignas(8) U8 userData[];
} bbBloatedPool_Header;

#define bbBloatedPool_alloc(pool, address)\
bbBloatedPool_allocImpl(pool, address, __FILE_NAME__, __LINE__);

I32 bbBloatedPool_new(bbBloatedPool** pool, I32 sizeOf, I32 level1, I32 level2);
I32 bbBloatedPool_delete(bbBloatedPool* pool);
I32 bbBloatedPool_clear(bbBloatedPool* pool);
I32 bbBloatedPool_allocImpl(bbBloatedPool* pool, void** address, char* file, int line);
I32 bbBloatedPool_free(bbBloatedPool* pool, void* address);
I32 bbBloatedPool_lookup(bbBloatedPool* pool, void** address, bbPool_Handle handle);
I32 bbBloatedPool_reverseLookup(bbBloatedPool* pool, void* address, bbPool_Handle* handle);
I32 bbBloatedPool_handleIsEqual(bbBloatedPool* USUSED, bbPool_Handle A, bbPool_Handle B);

#endif // BBBLOATEDPOOL_H