/** Deals with objects stored in a priority queue
 * EG a drawable is stored in a priority queue,
 * used to decide the order in which drawables are
 * drawn to the screen
 * For now, priority queue is used to implement a timer
 * (as usual, this could be done with less overhead...)
 *
 * a Pool can contain objects in many priority Queues, but a
 * Queue can contain only objects from one Pool
 */

#ifndef BBPRIORITYQUEUE_H
#define BBPRIORITYQUEUE_H


#include "bbIntTypes.h"
#include "bbPool.h"


/*
typedef struct {
    I32 Higher;
    I32 Lower;
    I32 Priority;

} bbPQ_data;

typedef struct {
    bbPool_data p_Pool;
    bbPQ_data p_Queue;
} bbPQNode;
*/

typedef struct {
    bbPool_data p_Pool;
    char* m_string;
    I32 m_integer;
} bbTestListNode;

typedef struct {
    bbPool* p_Pool;
    I32 m_Highest;
    I32 m_Lowest;
} bbList;


typedef struct {
    I32 time;
} timePtr;

///wrapper to bbPool_NewPool
I32 bbList_new(void** RBR, I32 map, I32 SizeOf, I32 level1, I32 Level2);

///new priority queue uses objects in existing pool
I32 bbList_existingPool(void** RBR, bbPool* pool);

///wrapper to bbPool_New
I32 bbListNode_new(void** RBR, bbList* Queue, I32 address);

///remove from queue and free up data
I32 bbListNode_delete(bbList* Queue, I32 address);

///remove from queue but keep object in pool
I32 bbListNode_remove(bbList* Queue, I32 address);

/** Insert node in queue after the last element greater than or equal itself
 *  Other variations on where to place the node in the queue may be defined later
 */
I32 bbListNode_insertAfter(bbList* Queue, I32 i_node);

/// for searching through priority queue
typedef I32 bbListFunction (void* reference, void* node);
/// search through nodes, applying myFunc(node) to each node
I32 bbList_ascendingSearch(void* RBR, bbList* queue, bbListFunction* myFunc);

I32 bbListFunction_print(void* UNUSED, void* node);
I32 bbListFunction_timer(void* time_ptr, void* node);


#endif //BBPRIORITYQUEUE_H