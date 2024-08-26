
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
#include "engine/logic/bbFastpool.h"

typedef struct {
    bbFastPool* p_pool;
    bbFastPool_Handle p_head;
    bbFastPool_Handle p_tail;
} bbDeque;

typedef struct {
    bbFastPool_Handle p_prev;
    bbFastPool_Handle p_next;
    U8 p_InUse;
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