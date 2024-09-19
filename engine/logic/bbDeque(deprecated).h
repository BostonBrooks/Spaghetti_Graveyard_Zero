
/**
 * @file
 * @brief Objects are allocated in a pool and then can be pushed and popped
 * from either end of the queue
 *
 **/

#ifndef DEQUE_H
#define DEQUE_H

#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbFlags.h"
#include "engine/logic/bbSlowPool.h"

//TODO move to .c file unless needed
#define bbDequePool_Handle          bbSlowPool_Handle
#define bbDequePool_Header          bbSlowPool_Header
#define bbDequePool_Available       bbSlowPool_Available
#define bbDequePool                 bbSlowPool
#define bbDequePool_HeaderIsNULL(x) bbSlowPool_HeaderIsNULL(x)
#define bbDequePool_NULL            bbSlowPool_NULL
#define bbDequePool_newPool         bbSlowPool_newPool
#define bbDequePool_deletePool      bbSlowPool_deletePool
#define bbDequePool_clearPool       bbSlowPool_clearPool
#define bbDequePool_newA            bbSlowPool_newA
#define bbDequePool_newH            bbSlowPool_newH
#define bbDequePool_deleteA         bbSlowPool_deleteA
#define bbDequePool_deleteH         bbSlowPool_deleteH
#define bbDequePool_getAddress      bbSlowPool_getAddress
#define bbDequePool_getHandle       bbSlowPool_getHandle

//TODO multiple deques use same pool
//EG AI publishes messages to drawables
//prevent calls that modify the entire pool

typedef struct {

    bbDequePool* p_pool;
    bbDequePool_Handle p_head;
    bbDequePool_Handle p_tail;
} bbDeque;

typedef struct {
    bbDequePool_Handle p_prev;
    bbDequePool_Handle p_next;
    U8 p_InUse; //TODO why?
} bbDeque_Element;

/// initialise new deque
I32 bbDeque_newDeque(void** deque, I32 sizeOf, I32 level1, I32 level2, I32 map);
/// delete deque entirely
I32 bbDeque_deleteDeque(void* deque);
/// delete everything contained in deque but keep deque alive
I32 bbDeque_clearDeque(void* deque);
/// allocate space for new element
I32 bbDeque_new(void* deque, void** element);
/// deallocate space used by element
I32 bbDeque_delete(void* deque, void* element);

/// add element to list head
I32 bbDeque_pushHead(void* deque, void* element);
/// remove element from list and return address
I32 bbDeque_popHead(void* deque, void** element);
/// add element to list tail
I32 bbDeque_pushTail(void* deque, void* element);
/// remove element and return address
I32 bbDeque_popTail(void* deque, void** element);

#endif // DEQUE_H