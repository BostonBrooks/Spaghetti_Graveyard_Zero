

#include "engine/logic/bbListList.h"

bbVPool* bbListList_pool;



bbFlag bbListList_init(bbListList* listList) {
    if (bbListList_pool == NULL){
        bbVPool_newLean(&bbListList_pool, sizeof(bbListListElement), 100);
    }
    bbList_init(&listList->list,
                bbListList_pool,
                NULL,
                offsetof(bbListListElement,listElement),
                compare_list);


    return Success;
}




bbFlag bbListList_attach(bbListList* listList, bbList* list){


    bbList_setHead(list, NULL);


    bbListListElement* listListElement;
    bbVPool_alloc(bbListList_pool, &listListElement);
    listListElement->list = list;
    listListElement->listElement.prev = bbListList_pool->null;
    listListElement->listElement.next = bbListList_pool->null;

    bbList_sortR(&listList->list, listListElement);



    return Success;
}


bbFlag bbListList_getNext(bbListList* listList, void** element){
    bbListListElement* listListElement;
    bbFlag flag = bbList_popL(&listList->list, &listListElement);
    if(flag != Success) return flag;


    void* element1;
    flag = bbList_getCurrent(listListElement->list, &element1);
    if(flag != Success) return flag;

    flag = bbList_increment(listListElement->list, NULL);
    if(flag == Success){
        bbList_sortL(&listList->list, listListElement);
    } else {
        bbVPool_free(bbListList_pool, listListElement);
    }

    *element = element1;
    return Success;
}


bbFlag bbListList_map(bbListList* list, bbMapFunction* fn, void* cl){
    void* element;

    while(1){
        bbFlag flag = bbListList_getNext(list, &element);
        if (flag != Success) break;
        fn(element, cl);
    }
}


I32 compare_list(void* one, void* two){

    bbListListElement* bbListListElement1 = one;
    bbListListElement* bbListListElement2 = two;

    bbList* list1 = bbListListElement1->list;
    bbList* list2 = bbListListElement2->list;

    void* element1;
    void* element2;

    bbList_getCurrent(list1, &element1);
    bbList_getCurrent(list2, &element2);
    I32 flag = list1->compare(element1, element2);

    return flag;

}

