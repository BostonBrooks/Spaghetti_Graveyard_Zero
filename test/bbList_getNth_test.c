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


bbFlag bbList_allocTest(bbList* list, void** element)
{
    void* lelement;
    bbFlag flag = bbVPool_alloc(list->pool, &lelement);
    if (flag == Success)
    {
        bbPool_ListElement* elementList = lelement + list->offsetOf;
        elementList->next = list->pool->null;
        elementList->prev = list->pool->null;
        *element = lelement;

        testElement* testElement = *element;
        bbDebug("integer = %d\n", testElement->integer);
        return Success;

    }
    *element = NULL;
    return flag;
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
        bbFlag flag = bbList_allocTest(list, (void**)&test_element);
        bbFlag_print(flag);
        bbDebug("test_element = %p\n", test_element);
        bbHere()
        //test_element->integer = rand();
bbHere();
        //this line causes the crash:
        bbDebug("integer = %d\n", test_element->integer);

        bbPool_Handle handle;


        bbVPool_reverseLookup(list->pool, test_element, &handle);
        bbHere()
        bbList_sortL(list,test_element);
        bbHere()
    }
    return 0;
}