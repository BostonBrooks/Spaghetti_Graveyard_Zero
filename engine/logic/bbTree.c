#include "engine/logic/bbTree.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbTerminal.h"
#include <stdlib.h>

bbFlag bbTree_new (bbTree** tree, void* pool, size_t offset){
    bbTree* Tree = malloc(sizeof(*Tree));
    bbVPool* Pool = pool;
    Tree->pool = Pool;
    Tree->root = Pool->null;
    Tree->offset = offset;
    *tree = Tree;

    return Success;
}


bbFlag bbNode_setEmpty(bbTree* tree, void* element){
    bbTree_Node* node = element+tree->offset;
    node->parent = tree->pool->null;
    node->peers.prev = tree->pool->null;
    node->peers.next = tree->pool->null;
    node->children.head = tree->pool->null;
    node->children.tail = tree->pool->null;
    node->numchildren = 0;
    node->visible = 1;
    node->childrenvisible = 1;
    return Success;
}

bbFlag bbNode_setParent(bbTree* tree, void* element, void* parent){

    bbVPool* pool = tree->pool;

    bbPool_Handle elementHandle;
    bbPool_Handle parentHandle;

    bbVPool_reverseLookup(pool, element, &elementHandle);
    bbVPool_reverseLookup(pool, parent, &parentHandle);

    bbTree_Node* elementNode = element + tree->offset;
    bbTree_Node* parentNode = parent + tree->offset;

    bbPool_Handle headHandle = parentNode->children.head;
    bbPool_Handle tailHandle = parentNode->children.tail;

    if (bbVPool_handleIsEqual(pool, headHandle, pool->null)){
        bbAssert(bbVPool_handleIsEqual(pool, tailHandle, pool->null),
                 "head/tail\n");
        bbAssert(parentNode->numchildren == 0, "empty list but num != 0\n");
        parentNode->numchildren = 1;
        parentNode->children.head = elementHandle;
        parentNode->children.tail = elementHandle;
        elementNode->peers.prev = elementHandle;
        elementNode->peers.next = elementHandle;
        elementNode->parent = parentHandle;

        return Success;

    }
    void* tailElement;
    bbVPool_lookup(pool, &tailElement, tailHandle);

    bbTree_Node* tailNode = tailElement + tree->offset;
    parentNode->numchildren += 1;
    tailNode->peers.next = elementHandle;
    elementNode->peers.prev = tailHandle;
    elementNode->peers.next = pool->null;
    parentNode->children.tail = elementHandle;
    elementNode->parent = parentHandle;

    return Success;
}

bbFlag descending_search(bbTree* tree, void* root, bbTreeFunction* myFunc,
                         void* cl)
{
    bbVPool* pool = tree->pool;
    bbTree_Node* rootNode = root + tree->offset;
    bbFlag flag = myFunc(tree, root, cl);
    //TODO switch on bbFlag
    if(flag == Break) return Break;

    bbPool_Handle elementHandle = rootNode->children.head;
    void* element;
    bbTree_Node* elementNode;

    //TODO if elementNode->peers.next == elementNode, infinite loop
    // element.next == element indicates only element in list
    // element.next == NULL indicates not in any list



    while(!bbVPool_handleIsEqual(pool, elementHandle, pool->null)){
        bbVPool_lookup(pool, &element, elementHandle);
        elementNode = element + tree->offset;
        flag = descending_search(tree, element,myFunc,cl);
        switch (flag) {
            case Break:
                return Break;
            case Continue:
                elementHandle = elementNode->peers.next;
                break;
            case Repeat:
                bbHere();
                break;
            default:
                bbHere();
        }

    }
    return Continue;
}

bbFlag ascending_search(bbTree* tree, void* root, bbTreeFunction* myFunc,
                         void* cl) {
    bbVPool *pool = tree->pool;
    bbTree_Node *rootNode = root  + tree->offset;
    bbFlag flag;

    bbPool_Handle elementHandle = rootNode->children.tail;
    void* element;
    bbTree_Node* elementNode;

    //TODO if elementNode->peers.next == elementNode, infinite loop
    while(!bbVPool_handleIsEqual(pool, elementHandle, pool->null)){
        bbVPool_lookup(pool, &element, elementHandle);
        elementNode = element  + tree->offset;
        flag = ascending_search(tree, element,myFunc,cl);
        switch (flag) {
            case Break:
                return Break;
            case Continue:
                elementHandle = elementNode->peers.prev;
                break;
            case Repeat:
                bbHere();
                break;
            default:
                bbHere();
        }

    }

    flag = myFunc(tree, element, cl);
    //TODO switch on bbFlag
    if(flag == Break) return Break;
    return Continue;

}