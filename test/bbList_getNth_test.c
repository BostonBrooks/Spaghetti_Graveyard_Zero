#include "engine/logic/bbBloatedPool.h"
#include "engine/logic/bbLeanPool.h"
#include "engine/logic/bbList.h"

//TODO this shouldn't need t be here (used in bbTerminal)
_Thread_local char* thread;


typedef struct
{
    I32 integer;
    bbPool_ListElement listElement;
} testElement;

I32 testCompare(void* a, void* b)
{
    testElement* A = (testElement*)a;
    testElement* B = (testElement*)b;

    return (A->integer > B->integer);
}
int main (void)
{
    bbList* list;
    bbVPool* vPool;
    testElement* test_element;

    bbVPool_newLean(&vPool,sizeof(testElement),1000);
    bbList_new(&list, vPool,NULL, offsetof(testElement, listElement),testCompare);

    for (I32 i=0; i<10; i++)
    {
        bbList_alloc(list, (void**)&test_element);
        test_element->integer = rand();
        bbList_sortL(list,test_element);
    }

    while (1)
    {
        bbHere()
        bbList_getNth( list, (void**)&test_element, 5);
        bbHere()
        bbList_remove(list, test_element);
        bbHere()
        bbVPool_free(list->pool, (void**)&test_element);
        bbHere()
        bbList_alloc(list, (void**)&test_element);
        bbHere()
        test_element->integer = rand();
        bbHere()
        bbList_sortL(list,test_element);
        bbHere()
    }
    return 0;
}