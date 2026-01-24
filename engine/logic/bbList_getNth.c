
#include "engine/logic/bbList.h"
#include "engine/logic/bbVPool.h"

bbFlag bbList_getNth(bbList* list, void** element, I32 N)
{
    int index = 0;
    void* nth_element;
    bbPool_ListElement* list_element;

    bbPool_Handle handle = list->list.head;
    //bbDebug("handle.index = %d, handle.collision = %d\n", handle.bloated.index, handle.bloated.collision);
    bbVPool_lookup(list->pool, (void**)&nth_element,handle);

    for (I32 i = 0; i < N; i++)
    {
        list_element = nth_element + list->offsetOf;
        handle = list_element->next;
    //bbDebug("handle.index = %d, handle.collision = %d\n", handle.bloated.index, handle.bloated.collision);
        bbVPool_lookup(list->pool, (void**)&nth_element,handle);
    }

    *element = nth_element;
    return Success;
}
