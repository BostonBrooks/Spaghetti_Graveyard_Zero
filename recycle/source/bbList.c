#include "headers/bbPool.h"
#include "headers/bbIntTypes.h"
#include "headers/bbList.h"
#include "headers/bbFlags.h"
#include "headers/bbPrintf.h"




///wrapper to bbPool_NewPool
I32 bbList_new(void** RBR, I32 map, I32 SizeOf, I32 level1, I32 Level2){
    bbList* list = malloc(sizeof(bbList));
	bbAssert(list != NULL, "malloc failed\n");
    list->m_Highest = f_None;
    list->m_Lowest = f_None;
    bbPool_NewPool(&list->p_Pool, map, SizeOf, level1, Level2);
    *RBR = list;
    return f_Success;
}

I32 bbList_existingPool(void** RBR, bbPool* pool){
    bbList* list = malloc(sizeof(bbList));
	bbAssert(list != NULL, "malloc failed\n");
    list->m_Highest = f_None;
    list->m_Lowest = f_None;
    list->p_Pool = pool;
	*RBR = list;
    return f_Success;
}

I32 bbListNode_new(void** RBR, bbList* list, I32 address){
    bbPool* pool = list->p_Pool;
    bbPool_data* node;
    I32 flag = bbPool_New(&node, pool, address);
    node->Next = -1;
    node->Prev = -1;
    *RBR = node;
    return flag;
}


I32 bbListNode_delete(bbList* list, I32 address){
    bbPool* pool = list->p_Pool;
    bbPool_data* node;
    bbPool_Lookup(&node, pool, address);

    I32 i_Higher = node->Next;
    I32 i_Lower = node->Prev;

    bbPool_data* Higher;
    bbPool_data* Lower;

    if (i_Higher != f_None && i_Lower != f_None){

        bbPool_Lookup(&Higher, pool, i_Higher);
        bbPool_Lookup(&Lower, pool, i_Lower);

        Lower->Next = i_Higher;
        Higher->Prev = i_Lower;

        //its nice to clean these up as they are returned to the pool
        node->Prev = f_None;
        node->Next = f_None;
        bbPool_Delete(pool, address);
        return f_Success;
    }

    if(i_Lower != f_None){ //i_Higher == f_None

        bbPool_Lookup(&Lower, pool, i_Lower);
        Lower->Next = f_None;
        list->m_Highest = i_Lower;

        //its nice to clean these up as they are returned to the pool
        node->Next = f_None;
        node->Prev = f_None;
        bbPool_Delete(pool, address);

        return f_Success;
    }
    if(i_Higher != f_None){ //i_lower == f_None

        bbPool_Lookup(&Higher, pool, i_Higher);
        Higher->Prev = f_None;
        list->m_Lowest = i_Higher;

        //its nice to clean these up as they are returned to the pool
        node->Next = f_None;
        node->Prev = f_None;
        bbPool_Delete(pool, address);

        return f_Success;
    }
    //(i_Higher == f_None && i_Lower == f_None)

    list->m_Lowest = f_None;
    list->m_Highest = f_None;

    node->Prev = f_None;
    node->Next = f_None;

    bbPool_Delete(pool, address);

    return f_Success;
}
I32 bbListNode_insertAfter(bbList* Queue, I32 i_node) {

    bbPool* pool = Queue->p_Pool;
    bbPool_data* newNode;
    I32 flag = bbPool_Lookup(&newNode, pool, i_node);




    if (Queue->m_Highest == f_None) {

        bbAssert(Queue->m_Lowest == f_None, "head/tail mismatch");
        Queue->m_Highest = newNode->Self;
        Queue->m_Lowest = newNode->Self;
        newNode->Next = -1;
        newNode->Prev = -1;

        return f_Success;
    }

    bbPool_data* Highest;
    bbPool_Lookup(&Highest, pool, Queue->m_Highest);

    if (Highest->Priority <= newNode->Priority){
        //insert newNode as next highest;
        newNode->Next = -1;
        newNode->Prev = Highest->Self;
        Highest->Next = newNode->Self;
        Queue->m_Highest = newNode->Self;

        return f_Success;
    }
    bbPool_data* node;

    bbPool_Lookup(&node, pool, Highest->Prev);

    while(1) {
        if (node->Priority <= newNode->Priority) {

            //insert newNode after Next
            bbPool_data* node2;
            bbPool_Lookup(&node2, pool, node->Next);

            //node < newNode < node2

            node->Next = newNode->Self;
            newNode->Prev = node->Self;
            newNode->Next = node2->Self;
            node2->Prev = newNode->Self;



            return f_Success;
        }
        if (node->Prev == f_None) {
            node->Prev = newNode->Self;
            newNode->Next = node->Self;
            newNode->Prev = f_None;
            Queue->m_Lowest = newNode->Self;
            return f_Success;
        }
        bbPool_Lookup(&node, pool, node->Prev);
    }

}

I32 bbList_ascendingSearch(void* RBR, bbList* list, bbListFunction* myFunc){
    bbPool* pool = list->p_Pool;
    I32 nodeInt = list->m_Lowest;
    bbTestListNode* node;
    I32 flag;
    while(nodeInt >= 0){

        flag = bbPool_Lookup(&node, pool, nodeInt);
        flag = myFunc(RBR, node);
        nodeInt = node->p_Pool.Next;
        if (flag == f_Delete) bbListNode_delete(list, node->p_Pool.Self);
        if (flag == f_Break) break;
    }
    return f_Success;
}


I32 bbListFunction_print(void* UNUSED, void* node){

    bbTestListNode* testNode = node;
    printf("NODE: Self = %d, Priority = %d\n", testNode->p_Pool.Self, testNode->p_Pool.Priority);
    return f_Success;
}


I32 bbListFunction_timer(void* time_ptr, void* node){
    bbTestListNode* testNode = node;
    timePtr* ptr = time_ptr;
    I32 time = ptr->time;
    if (testNode->p_Pool.Priority <= time){
        printf("NODE: Self = %d, Time = %d\n", testNode->p_Pool.Self, testNode->p_Pool.Priority);
        return f_Delete;
    }
    return f_Break;
}
