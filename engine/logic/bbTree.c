#include "engine/logic/bbTree.h"
#include "engine/logic/bbTerminal.h"

/// add a new node (with no daughter nodes) as a daughter node to parent;
I32 bbNode_setParent(bbPool_common* pool, void* node, void* parent)
{
    bbAssert(node != NULL, "passed null pointer\n");
    bbTree* Node = node;
    bbTree* Parent = parent;
    if(parent == NULL){
        Node->parent = pool->null;
        Node->peers.prev = pool->null;
        Node->peers.next = pool->null;
        Node->children.head = pool->null;
        Node->children.tail = pool->null;

        return f_Success;
    }
    bbPool_Handle parent_handle;
    bbPool_reverseLookup(pool, parent, &parent_handle);

    Node->parent = parent_handle;
    Node->peers.prev = pool->null;
    Node->peers.next = pool->null;
    Node->children.head = pool->null;
    Node->children.tail = pool->null;

    //TODO pool handle equal?
    if (Parent->children.head == pool->null){
        bbAssert(Parent->children.tail == pool->null, "head/tail mismatch\n");

    }

}
///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 descending_search(bbPool_common* pool,
                      void* root,
                      bbTreeFunction* myFunc,
                      void* cl)
{

}
///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 ascending_search(bbPool_common* pool,
                     void* root,
                     bbTreeFunction* myFunc,
                     void* cl)
{

}

///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 descending_searchVisible(bbPool_common* pool,
                             void* root,
                             bbTreeFunction* myFunc,
                             void* cl)
{

}
///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 ascending_searchVisible(bbPool_common* pool,
                            void* root,
                            bbTreeFunction* myFunc,
                            void* cl)
{

}