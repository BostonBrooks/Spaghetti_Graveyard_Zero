
/**
 * @file
 * @brief Pools pre-allocate space for objects in the game to quickly allocate
 * and de-allocate individual objects. this particular pool is designed for
 * size and safety and not speed
 * TODO attach new deque to existing pool
 * TODO 64 bit alignment
 **/
#ifndef SLOWPOOL_H
#define SLOWPOOL_H

#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbFlags.h"

typedef U32 bbSlowPool_Handle;

#define bbSlowPool_NULL 0

typedef struct {
    void* p_Pool;
    bbSlowPool_Handle p_Handle;
} bbSlowPool_Header;

typedef struct {
    bbSlowPool_Header p_header;
    bbSlowPool_Handle p_prev;
    bbSlowPool_Handle p_next;

} bbSlowPool_Available;

typedef struct {

    U16 p_sizeOf;
    U16 p_level1;
    U16 p_level2;
    U16 p_map;
    bbSlowPool_Handle p_availableHead;
    bbSlowPool_Handle p_availableTail;
    
    void* p_elements[];

} bbSlowPool;




I32 bbSlowPool_HandleIsNULL(bbSlowPool_Handle handle);


/// create a new pool
I32 bbSlowPool_newPool(void** pool, I32 sizeOf, I32 level1, I32 level2, I32
map);
/// delete pool and free memory
I32 bbSlowPool_deletePool(void* pool);
/// delete everything that's in the pool but keep the reserved data
I32 bbSlowPool_clearPool(void* pool);
/// create a new object and return the address
I32 bbSlowPool_newA(void* pool, void** address);
/// create a new object and return the handle
I32 bbSlowPool_newH(void* pool, bbSlowPool_Handle* handle);
/// delete a member from the pool given its memory address
I32 bbSlowPool_deleteA(void* pool, void* address);
/// delete a member from the pool given its handle
I32 bbSlowPool_deleteH(void* pool, bbSlowPool_Handle handle);
/// return the address of an element given its handle, or NULL
I32 bbSlowPool_getAddress(void* pool, void** address, bbSlowPool_Handle handle);
/// return the handle of an element given its address
I32 bbSlowPool_getHandle(void* pool, bbSlowPool_Handle* handle, void* address);

// Address_getMap(), Address_getPool?
// Pool_getNum, Pool_getMap;
//

#endif // SLOWPOOL_H