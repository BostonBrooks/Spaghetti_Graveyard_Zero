#include "engine/logic/bbList.h"
#include "engine/logic/bbString.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbFlag.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


#define isEqual(A, B) bbVPool_handleIsEqual(list->pool, A, B)
#define isNULL(A) bbVPool_handleIsEqual(list->pool, A, list->pool->null)


bbFlag bbList_insertAfter(bbList* list, void* Node, void* Key){
    bbPool_Handle NodeHandle;
    bbVPool_reverseLookup(list->pool, Node, &NodeHandle);
    bbPool_ListElement* NodeList = Node + list->offsetOf;

    bbPool_Handle KeyHandle;
    bbVPool_reverseLookup(list->pool, Key, &KeyHandle);
    bbPool_ListElement* KeyList = Key + list->offsetOf;

    bbPool_Handle NextHandle = KeyList->next;
    void* Next;
    bbVPool_lookup(list->pool, &Next, NextHandle);
    bbPool_ListElement* NextList = Next + list->offsetOf;

    KeyList->next = NodeHandle;
    NodeList->prev = KeyHandle;
    NodeList->next = NextHandle;
    NextList->prev = NodeHandle;

    if (isEqual(KeyHandle, list->listPtr->tail)){
        list->listPtr->tail = NodeHandle;
    }

    return Success;
}

bbFlag bbList_insertBefore(bbList* list, void* Node, void* Key){
    bbPool_Handle NodeHandle;
    bbVPool_reverseLookup(list->pool, Node, &NodeHandle);
    bbPool_ListElement* NodeList = Node + list->offsetOf;

    bbPool_Handle KeyHandle;
    bbVPool_reverseLookup(list->pool, Key, &KeyHandle);
    bbPool_ListElement* KeyList = Key + list->offsetOf;

    bbPool_Handle PrevHandle = KeyList->prev;
    void* Prev;
    bbVPool_lookup(list->pool, &Prev, PrevHandle);
    bbPool_ListElement* PrevList = Prev + list->offsetOf;

    PrevList->next = NodeHandle;
    NodeList->prev = PrevHandle;
    NodeList->next = KeyHandle;
    KeyList->prev = NodeHandle;

    if(isEqual(KeyHandle, list->listPtr->head)){
        list->listPtr->head = NodeHandle;
    }

    return Success;
}