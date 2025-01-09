#ifndef BBLISTLIST_H
#define BBLISTLIST_H

#include "engine/logic/bbList.h"
#include "engine/logic/bbTerminal.h"

extern bbVPool* bbListList_pool;

typedef struct {
    bbList* list; //pointer to existing list
    bbPool_ListElement listElement; //element of list list
} bbListListElement;

typedef struct {
    bbList list;
} bbListList;


typedef bbFlag bbMapFunction(void* node, void* cl);

bbFlag bbListList_init(bbListList* listList);
bbFlag bbListList_attach(bbListList* listList, bbList* list);
bbFlag bbListList_getNext(bbListList* listList, void** element);
bbFlag bbListList_map(bbListList* list, bbMapFunction* fn, void* cl);


I32 compare_list(void* one, void* two);

#endif // BBLISTLIST_H