/**
 * @file
 * @brief Pools pre-allocate space for objects in the game to quickly allocate
 * and de-allocate individual objects. this particular pool is designed for
 * size and safety and not speed
 *
 */

#ifndef POOL_H
#define POOL_H

#include <stdbool.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbFlags.h"

typedef U32 bbPool_Handle;


typedef struct{
    bbPool_Handle head;
    bbPool_Handle tail;
}  bbPool_List;


typedef struct{
    bbPool_Handle prev;
    bbPool_Handle next;
}  bbPool_Element;

typedef struct {
    bbPool_Handle p_self;
    bool p_InUse;
} bbPool_Header;

typedef struct {
    bbPool_Header p_header;
    bbPool_Element p_list;
} bbPool_Available;

typedef struct {
    U16 p_sizeOf;
    U16 p_level1;
    U16 p_level2;
    bbPool_List p_list;

    //list of dynamically allocated lists of element
    void* p_elements[];
} bbPool;

#define bbPool_NULL 0

I32 bbPool_HandleIsNULL(bbPool_Handle handle);

/// create a new pool
I32 bbPool_newPool(bbPool** pool, I32 sizeOf, I32 level1, I32 level2);
/// free memory then free pool
I32 bbPool_deletePool(bbPool* pool);
/// free memory
I32 bbPool_clearPool(bbPool* pool);
/// create a new object and return the handle / address
I32 bbPool_new(bbPool* pool, void** address, bbPool_Handle* handle);
/// delete a member from the pool given its address / handle
I32 bbPool_delete(bbPool* pool, void* address, bbPool_Handle handle);
/// return the address of an element given its handle, or NULL
I32 bbPool_getAddress(bbPool* pool, void** address, bbPool_Handle handle);
/// return the handle of an element given its address
I32 bbPool_getHandle(bbPool* pool, bbPool_Handle* handle, void* address);


#endif // POOL_H