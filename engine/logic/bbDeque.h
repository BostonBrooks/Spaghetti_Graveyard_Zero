/**
 * @file
 * @brief A deque is a linked list where elements can be pushed and popped from
 * each end
 * The deque is used to implement the reactor pattern
 * EG the main loop is one reactor
 * every entity in the gameworld is a reactor attached to the same pool
 *
 * thoughts on entities:
 * - one loop looks at the surrounding entities and posts updates to itself
 * - another loop looks at the list of updates and applies them to itself
 *  - in the second loop, an entity can (re)post updates to itself to be
 *  handled on the next iteration
 *
 *  We avoid malloc-ing many deques by storing the deque as part of an
 *  existing struct. otherwise we'd need to draw from a pool of deques
 **/

#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbFlags.h"
#include "engine/logic/bbPool.h"

typedef struct {
    bbPool* p_pool;
    bbPool_List p_list;
} bbDeque;

typedef struct {
    bbPool_Header p_header;
    bbPool_ListElement p_listElement;
} bbDeque_Element;


/// create an new pool and attach to existing deque, init deque to empty
I32 bbDeque_newPool(bbDeque* deque, U32 sizeOf, U32 level1, U32 level2);
/// delete pool from existing deque
I32 bbDeque_deletePool(bbDeque* deque);
/// attach pool to existing deque and init deque as empty
I32 bbDeque_attachPool(bbDeque* deque);

/// allocate space for new element
I32 bbDeque_new(bbDeque* deque, bbDeque_Element** element);
/// deallocate space used by element
I32 bbDeque_delete(bbDeque* deque);
/// remove all elements in deque
I32 bbDeque_clearDeque(bbDeque* deque);

/// add element to list head
I32 bbDeque_pushHead(bbDeque* deque, bbDeque_Element* element);
/// remove element from list and return address
I32 bbDeque_popHead(bbDeque* deque, bbDeque_Element** element);
/// add element to list tail
I32 bbDeque_pushTail(bbDeque* deque, bbDeque_Element* element);
/// remove element and return address
I32 bbDeque_popTail(bbDeque* deque, bbDeque_Element** element);
