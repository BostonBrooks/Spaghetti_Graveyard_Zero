#include <stdbool.h>
#include "headers/bbTree.h"
#include "headers/bbFlags.h"
#include "headers/bbPrintf.h"
#include "headers/bbPool.h"
#include "headers/bbIntTypes.h"

I32 bbNode_setParent(void* void_node, void* void_parent, bbPool* pool){

    bbNode* node = void_node;
    bbNode* parent = void_parent;

    if (parent == NULL){
        node->p_Tree.Parent = f_None;
        node->p_Tree.Head = f_None;
        node->p_Tree.Tail = f_None;
        node->p_Tree.Prev = f_None;
        node->p_Tree.Next = f_None;

        return f_Success;
    }


    node->p_Tree.Parent = parent->p_Pool.Self;
	node->p_Tree.Head = f_None;
	node->p_Tree.Tail = f_None;
	node->p_Tree.Prev = f_None;
	node->p_Tree.Next = f_None;

	if (parent->p_Tree.Head == f_None){
		bbAssert(parent->p_Tree.Tail == f_None, "head/tail mismatch\n");
		parent->p_Tree.Head = node->p_Pool.Self;
		parent->p_Tree.Tail	= node->p_Pool.Self;
		return f_Success;
	}

	bbNode* tailNode;
	I32 flag = bbPool_Lookup(&tailNode, pool, parent->p_Tree.Tail);
    bbAssert(flag >= 0,"pool lookup failed\n");

    tailNode->p_Tree.Next = node->p_Pool.Self;
    node->p_Tree.Prev = tailNode->p_Pool.Self;
    node->p_Tree.Next = f_None;
    parent->p_Tree.Tail = node->p_Pool.Self;
    return f_Success;
}



I32 descending_search(void* reference, void* void_root, bbTreeFunction* myFunc, bbPool* pool){

    bbNode* root = void_root;

    I32 flag = myFunc(reference, root);
    if (flag == f_Break) return f_Break;

    I32 intHead = root->p_Tree.Head;

    while (intHead != f_None){
        bbNode* node;
        flag = bbPool_Lookup(&node, pool, intHead);
        bbAssert(flag >= 0, "bbPool_Lookup() returns bad flag\n");
        flag = descending_search(reference, node, myFunc, pool);
        if (flag == f_Break) return f_Break;
        if (flag == f_Continue) intHead = node->p_Tree.Next;
        // flag == f_Repeat or flag == f_Delete?
    }
    return f_Continue;
}
I32 ascending_search(void* reference, void* void_root, bbTreeFunction* myFunc, bbPool* pool){

    bbNode* root = void_root;

    I32 flag;
    I32 intTail = root->p_Tree.Tail;

    while (intTail != f_None){
        bbNode* node;
        flag = bbPool_Lookup(&node, pool, intTail);
        bbAssert(flag >= 0, "bbPool_Lookup() returns bad flag\n");
        flag = ascending_search(reference, node, myFunc, pool);
        if (flag == f_Break) return f_Break;
        if (flag == f_Continue) intTail = node->p_Tree.Prev;
        // flag == f_Repeat or flag == f_Delete?
    }
    flag = myFunc(reference, root);
    if (flag == f_Break) return f_Break;

    return f_Continue;
}

I32 descending_searchVisible(void* reference, void* void_root, bbTreeFunction* myFunc, bbPool* pool){

    bbNode* root = void_root;
    I32 flag;
    if (root->p_Tree.Visible) {
        flag= myFunc(reference, root);
        if (flag == f_Break) return f_Break;
    }
    I32 intHead = root->p_Tree.Head;

    if(root->p_Tree.SubwidgetsVisible) {
        while (intHead != f_None) {
            bbNode *node;
            flag = bbPool_Lookup(&node, pool, intHead);
            bbAssert(flag >= 0, "bbPool_Lookup() returns bad flag\n");
            flag = descending_searchVisible(reference, node, myFunc, pool);
            if (flag == f_Break) return f_Break;
            if (flag == f_Continue) intHead = node->p_Tree.Next;
            // flag == f_Repeat or flag == f_Delete?
        }
    }
    return f_Continue;
}
I32 ascending_searchVisible(void* reference, void* void_root, bbTreeFunction* myFunc, bbPool* pool){

    bbNode* root = void_root;

    I32 flag;
    I32 intTail = root->p_Tree.Tail;
    if(root->p_Tree.SubwidgetsVisible) {
        while (intTail != f_None) {
            bbNode *node;
            flag = bbPool_Lookup(&node, pool, intTail);
            bbAssert(flag >= 0, "bbPool_Lookup() returns bad flag\n");
            flag = ascending_searchVisible(reference, node, myFunc, pool);
            if (flag == f_Break) return f_Break;
            if (flag == f_Continue) intTail = node->p_Tree.Prev;
            // flag == f_Repeat or flag == f_Delete?
        }
    }
    if (root->p_Tree.Visible) {
        flag = myFunc(reference, root);
        if (flag == f_Break) return f_Break;
    }
    return f_Continue;
}