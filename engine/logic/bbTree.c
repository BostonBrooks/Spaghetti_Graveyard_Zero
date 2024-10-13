#include "engine/logic/bbTree.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbTerminal.h"
#include <stdlib.h>

bbFlag bbTree_new (bbTree** tree, void* pool, bbTree_Node* (*get_node)(void*
element)){
    bbTree* Tree = malloc(sizeof(*Tree));
    bbVPool* Pool = pool;
    Tree->pool = Pool;
    Tree->root = Pool->null;
    Tree->get_node = get_node;
    *tree = Tree;

    return Success;
}

bbFlag bbNode_setParent(bbTree* tree, void* element, void* parent){

    bbVPool* pool = tree->pool;

    bbPool_Handle elementHandle;
    bbPool_Handle parentHandle;

    bbVPool_reverseLookup(pool, element, &elementHandle);
    bbVPool_reverseLookup(pool, parent, &parentHandle);

    bbTree_Node* elementNode = tree->get_node(element);
    bbTree_Node* parentNode = tree->get_node(parent);

    bbPool_Handle headHandle = elementNode->children.head;
    bbPool_Handle tailHandle = elementNode->children.tail;

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

    bbTree_Node* tailNode = tree->get_node(tailElement);
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
    bbTree_Node* rootNode = tree->get_node(root);
    bbFlag flag = myFunc(tree, root, cl);
    //TODO switch on bbFlag
    if(flag == Break) return Break;

    bbPool_Handle elementHandle = rootNode->children.head;
    void* element;
    bbTree_Node* elementNode;

    //TODO if elementNode->peers.next == elementNode, infinite loop
    while(!bbVPool_handleIsEqual(pool, elementHandle, pool->null)){
        bbVPool_lookup(pool, &element, elementHandle);
        elementNode = tree->get_node(element);
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
    bbTree_Node *rootNode = tree->get_node(root);
    bbFlag flag;

    bbPool_Handle elementHandle = rootNode->children.tail;
    void* element;
    bbTree_Node* elementNode;

    //TODO if elementNode->peers.next == elementNode, infinite loop
    while(!bbVPool_handleIsEqual(pool, elementHandle, pool->null)){
        bbVPool_lookup(pool, &element, elementHandle);
        elementNode = tree->get_node(element);
        flag = descending_search(tree, element,myFunc,cl);
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