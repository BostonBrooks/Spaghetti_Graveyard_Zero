/**
 * @file
 * @brief Pools pre-allocate space for objects in the game to quickly allocate
 * and de-allocate individual objects. this provides an interface for different
 * pools using different strategies
 *
 * Will generally work with memory addresses but may be able to convert
 * between addresses and handles
 */

#ifndef POOL_H
#define POOL_H

#include <stdalign.h>
#include <stdbool.h>
#include <assert.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbFlags.h"
#include "engine/logic/bbComplexPool.h"

typedef union {
    void* ptr;
    bbComplexPool_Handle complex;
    U64 u64;
} bbPool_Handle;


typedef struct{
    bbPool_Handle head;
    bbPool_Handle tail;
}  bbPool_List;

typedef struct{
    bbPool_Handle prev;
    bbPool_Handle next;
}  bbPool_ListElement;

typedef struct{
    bbPool_Handle self;
    //do we need bbPool_ListElement list if inUse?
    bbPool_ListElement list;
    bool inUse;
    alignas(8) U8 userData[];
}  bbPool_Header;

typedef struct bbPool_common {

    //null is a public variable, because we might want to specify null element
    //when we initialise some object is would be nice to specify all of the
    // elements at compile time to skip the de-referencing of function pointers
    bbPool_Handle null;
    I32 (*deletePool)(struct bbPool_common* pool);
    I32 (*clearPool)(struct bbPool_common* pool);
    I32 (*new)(struct bbPool_common* pool, void** address);
    I32 (*delete)(struct bbPool_common* pool, void* address);
    I32 (*lookup)(struct bbPool_common* pool, void** address, bbPool_Handle handle);
    I32 (*reverseLookup)(struct bbPool_common* pool, void* address, bbPool_Handle* handle);
    U32 sizeOf;

} bbPool_common;

/// delete pool and free memory
static I32 bbPool_deletePool(bbPool_common* pool){
    return pool->deletePool(pool);
}
/// delete everything that's in the pool but keep the reserved data
static I32 bbPool_clearPool(bbPool_common* pool){
    return pool->clearPool(pool);
}
/// create a new object and return the address / handle
static I32 bbPool_new(struct bbPool_common* pool, void** address){
    return pool->new(pool, address);
}
/// delete a member from the pool given its memory address / handle
static I32 bbPool_delete(struct bbPool_common* pool, void* address){
    return pool->delete(pool, address);
}
/// return the address of an element given its handle, or NULL
/// NULL may come in handy, to warn if we are accessing an object that no
// longer exists
static I32 bbPool_lookup(struct bbPool_common* pool, void** address, bbPool_Handle handle){
    return pool->lookup(pool, address, handle);
}
/// return the handle of an element given its address
static I32 bbPool_reverseLookup(struct bbPool_common* pool, void* address, bbPool_Handle* handle){
    return pool->reverseLookup(pool, address, handle);
}

#endif // POOL_H