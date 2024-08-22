
/**
 * @file
 * @brief Pools pre-allocate space for objects in the game to quickly allocate
 * and de-allocate individual objects. this particular pool is designed for
 * speed and not size or safety
 *
 **/
#ifndef FASTPOOL_H
#define FASTPOOL_H

#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbFlags.h"

/// elements of pool are addressed by their memory address
typedef void* bbFastPool_Handle;

/// members of a pool know what pool they are in
typedef struct {
    void* p_pool;
} bbFastPool_Header;

/// unused slots in pool are stored in a double linked list
typedef struct {
    bbFastPool_Header p_header;
    void* p_prev;
    void* p_next;
} bbFastPool_Available;

/// pool keeps track of its objects, and a bit of metadata
typedef struct {

    U16 p_sizeOf;
    U16 p_num;
    U16 p_map;
    void* p_availableHead;
    void* p_availableTail;
    char p_objects[];
}bbFastPool ;

/// null handle is just NULL
#define bbFastPool_HeaderIsNULL(x) (x == NULL ? 1 : 0)

/// create a new pool
I32 bbFastPool_newPool(void** pool, I32 sizeOf, I32 num, I32 unused, I32 map);
/// delete pool and free memory
I32 bbFastPool_deletePool(void* pool);
/// delete everything that's in the pool but keep the reserved data
I32 bbFastPool_clearPool(void* pool);
/// create a new object and return the address
I32 bbFastPool_newA(void* pool, void** address);
/// create a new object and return the handle
I32 bbFastPool_newH(void* pool, bbFastPool_Handle* handle);
/// delete a member from the pool given its memory address
I32 bbFastPool_deleteA(void* pool, void* address);
/// delete a member from the pool given its handle
I32 bbFastPool_deleteH(void* pool, bbFastPool_Handle handle);
/// return the address of an element given its handle
I32 bbFastPool_getAddress(void* pool, void** address, bbFastPool_Handle handle);
/// return the handle of an element given its address
I32 bbFastPool_getHandle(void* pool, bbFastPool_Handle* handle, void* address);

#endif // FASTPOOL_H