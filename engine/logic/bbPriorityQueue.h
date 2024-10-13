/**
 * @file
 * @brief A priority queue is a sorted list of objects that are defined by
 * the pool that contains them. I could have ignored the existence of pools
 * but objects in a priority queue will be in the same pool anyway
 * Using different getList functions will allow elements to exist in multiple
 * queues.
 *
 * may want a pool of objects given by
 * typedef struct {
 *     bbPool_ListElement list;
 *     void* data;
 * } bbExtrusiveList;
 */

#include "engine/logic/bbIntTypes.h"
#include "engine/logic/recycle/bbPool.h"

typedef struct {
    bbPool_common* pool;
    // head and tail of list
    bbPool_List list;
    //return a pointer to the list element tracking prev/next
    bbPool_ListElement* (*getList)(void*);
    //comparison operator used to sort list
    I32 (*isGreater)(void*, void*);
} bbPriorityQueue;

/// Initialise priority queue and attach to pool
I32 bbPriorityQueue_newQueue(bbPriorityQueue** Queue,
                             bbPool_common* Pool,
                             bbPool_ListElement* (*get_List)(void*),
                             I32 (*is_Greater)(void*, void*));

/// create a new element to put on priority queue
I32 bbPriorityQueue_new(bbPriorityQueue* queue,
                               void** address,
                               bbPool_Handle* handle);

/// delete an element from priority queue
I32 bbPriorityQueue_delete(bbPriorityQueue* queue,
                                  void* address,
                                  bbPool_Handle handle);

/// add an element to priority queue
I32 bbPriorityQueue_add(bbPriorityQueue* queue,
                                  void* address,
                                  bbPool_Handle handle);

/// remove an element from priority queue
I32 bbPriorityQueue_remove(bbPriorityQueue* queue,
                                  void* address,
                                  bbPool_Handle handle);

/// re-sort an element in priority queue
I32 bbPriorityQueue_resort(bbPriorityQueue* queue,
                                  void* address,
                                  bbPool_Handle handle);

/// return the address of an element given its handle, or NULL
I32 bbPriorityQueue_lookup(bbPriorityQueue* queue,
                                  void** address,
                                  bbPool_Handle handle);
/// return the handle of an element given its address
I32 bbPriorityQueue_reverseLookup(bbPriorityQueue* queue,
                                         void* address,
                                         bbPool_Handle* handle);

/// the whole point of having a priority queue
I32 bbPriorityQueue_getNext(bbPriorityQueue* queue,
                            void* address, bbPool_Handle handle,
                            void** nextAddress, bbPool_Handle* nextHandle);

/// the whole point of having a priority queue
I32 bbPriorityQueue_getPrev(bbPriorityQueue* queue,
                            void* address, bbPool_Handle handle,
                            void** prevAddress, bbPool_Handle* prevHandle);