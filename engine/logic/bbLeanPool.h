/** a lean pool is one that implements minimum features
 * and checks, objects are accessed by their memory addresses
 * and so the pool cannot be expanded*/

#ifndef BBLEANPOOL_H
#define BBLEANPOOL_H

#include <stdalign.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbPoolHandle.h"

typedef struct {
	bbPool_Handle null;
	U32 num;
	U32 sizeOf;
	bbPool_List available;
	alignas(8) U8 elements[];
} bbLeanPool;

typedef bbPool_ListElement bbLeanPool_Header;

#define bbLeanPool_alloc(pool, address)\
bbLeanPool_allocImpl(pool, address, NULL, 0);

I32 bbLeanPool_new(bbLeanPool** pool, I32 sizeOf, I32 num);
I32 bbLeanPool_delete(bbLeanPool* pool);
I32 bbLeanPool_clear(bbLeanPool* pool);
I32 bbLeanPool_allocImpl(bbLeanPool* pool, void** address, char* file, int line);
I32 bbLeanPool_free(bbLeanPool* pool, void* address);
I32 bbLeanPool_lookup(bbLeanPool* UNUSED, void** address, bbPool_Handle handle);
I32 bbLeanPool_reverseLookup(bbLeanPool* UNUSED, void* address, bbPool_Handle* handle);
I32 bbLeanPool_handleIsEqual(bbLeanPool* USUSED, bbPool_Handle A, bbPool_Handle B);



#endif // BBLEANPOOL_H

