/** a lean pool is one that implements minimum features
 * and checks, objects are accessed by their memory addresses
 * and so the pool cannot be expanded*/

#ifndef BBLEANPOOL_H
#define BBLEANPOOL_H

#include <stdalign.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbVPool.h"

typedef struct {
	bbPool_Handle null;
	U32 num;
	U32 sizeOf;
    U32 inUse;
	bbPool_List available;
	alignas(8) U8 elements[];
} bbLeanPool;

typedef bbPool_ListElement bbLeanPool_Header;

#define bbLeanPool_alloc(pool, address)\
bbLeanPool_allocImpl(pool, address, NULL, 0);


bbFlag bbVPool_newLean(bbVPool** pool, I32 sizeOf, I32 num);
bbFlag bbLeanPool_new(bbLeanPool** pool, I32 sizeOf, I32 num);
bbFlag bbLeanPool_delete(bbLeanPool* pool);
bbFlag bbLeanPool_clear(bbLeanPool* pool);
bbFlag bbLeanPool_allocImpl(bbLeanPool* pool, void** address, char* file, int
line);
bbFlag bbLeanPool_free(bbLeanPool* pool, void* address);
bbFlag bbLeanPool_lookup(bbLeanPool* UNUSED, void** address, bbPool_Handle handle);
bbFlag bbLeanPool_reverseLookup(bbLeanPool* UNUSED, void* address, bbPool_Handle*
handle);
bbFlag bbLeanPool_printHeader(bbLeanPool* pool, void* address);
I32 bbLeanPool_handleIsEqual(bbLeanPool* USUSED, bbPool_Handle A, bbPool_Handle B);



#endif // BBLEANPOOL_H

