#include "engine/logic/bbBloatedPool.h"
#include "engine/logic/bbList.h"

//TODO this shouldn't need t be here (used in bbTerminal)
_Thread_local char* thread;

typedef struct
{
    I32 integer;
    bbPool_ListElement listElement;
} testElement;

int main (void)
{
    bbList* list;
    bbVPool* vPool;
    testElement* test_element;

    bbVPool_newBloated(&vPool,sizeof(testElement),100,100);
    bbList_new(&list, vPool,NULL, offsetof(testElement, listElement),NULL);

    for (I32 i=0; i<10; i++)
    {
        bbList_alloc(list, (void**)&test_element);
        test_element->integer = i;
        bbList_pushR(list,test_element);
    }

    bbList_getNth( list, (void**)&test_element, 5);
    printf("i = %d\n", test_element->integer);

    return 0;
}