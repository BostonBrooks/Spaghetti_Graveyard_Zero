#include "bbTree.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbFlags.h"

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
    bbPool_reverseLookup(pool, Parent, &parent_handle);
    bbPool_Handle node_handle;
    bbPool_reverseLookup(pool, Node, &node_handle);

    Node->parent = parent_handle;
    Node->peers.prev = pool->null;
    Node->peers.next = pool->null;
    Node->children.head = pool->null;
    Node->children.tail = pool->null;
    Node->numchildren = 0;

    if (bbPool_handleIsEqual(pool, Parent->children.head,pool->null)){
        bbAssert(bbPool_handleIsEqual(pool, Parent->children.tail,pool->null)
                 && Parent->numchildren == 0,
                 "head/tail mismatch\n");
        Parent->children.head = node_handle;
        Parent->children.tail = node_handle;
        Parent->numchildren = 1;
    }

    bbTree* Tail;
    bbPool_lookup(pool, &Tail, Parent->children.tail);
    Tail->peers.next = node_handle;
    Node->peers.prev = Parent->children.tail;
    Node->peers.next = pool->null;
    Parent->children.tail = node_handle;
    Parent->numchildren += 1;
    return f_Success;

}
///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 descending_search(bbPool_common* pool,
                      void* root,
                      bbTreeFunction* myFunc,
                      void* cl)
{
    bbTree* Root = root;
    I32 flag = myFunc(Root, cl);
    if (flag == f_Break) return f_Break;

    bbPool_Handle head = Root->children.head;

    while (!bbPool_handleIsEqual(pool, head, pool->null)){
        bbTree* tree;
        bbPool_lookup(pool, &tree, head);
        flag = descending_search(pool, tree, myFunc, cl);
        if (flag == f_Break) return f_Break;
        if (flag == f_Continue) head = tree->peers.next;
        //what if flag == f_Repeat or flag == f_Delete?
    }
    return f_Continue;
}
///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 ascending_search(bbPool_common* pool,
                     void* root,
                     bbTreeFunction* myFunc,
                     void* cl)
{
    bbTree* Root = root;
    I32 flag;
    bbPool_Handle tail_handle = Root->children.tail;

    while (!bbPool_handleIsEqual(pool, tail_handle, pool->null)){
        bbTree* tree;
        bbPool_lookup(pool, &tree, tail_handle);
        flag = ascending_search(pool, tree, myFunc, cl);
        if (flag == f_Break) return f_Break;
        if (flag == f_Continue) tail_handle = tree->peers.prev;
        //what if flag == f_Repeat or flag == f_Delete?
    }
    flag = myFunc(Root, cl);
    if (flag == f_Break) return f_Break;
    return f_Continue;
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