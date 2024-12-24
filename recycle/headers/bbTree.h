/**
 * @file
 * @brief bbTree defines a structure where each member has a parent and a list of daughter nodes.
 * the first element of the member should start with :
 *
 *	bbNode p_Pool
 *
 *	Any such structure can be referred to as bbNode
 *
 *	bbPool_data p_Pool is the first element of bbNode
 *  bbNode p_Pool is the first element of bbTest_Node
 *  bbTestNode is an example of the kind of object to be stored in a bbTree
 *
 *  as such bbTestNode can be cast as bbNode and bbNode can be cast as bbPool
 */

#ifndef BBTREE_H
#define BBTREE_H

#include <stdbool.h>
#include <inttypes.h>
#include "bbPool.h"
#include "bbIntTypes.h"

typedef struct {
	// Integer address (location in pool) of parent node
	I32 Parent;
	// Start of list of daughter nodes
	I32 Head;
	// End of list of daughter nodes
	I32 Tail;
	// Previous in list of daughter nodes
	I32 Prev;
	// Next in list of daughter nodes
	I32 Next;
    // Do not include this widget in search if !Visible
    bool Visible;
    // Do not include subwidgets in search if !SubwidgetsVisible.
    bool SubwidgetsVisible;

} bbTree_data;

typedef struct {
	bbPool_data p_Pool;
	bbTree_data p_Tree;
} bbNode;

typedef struct {
	bbNode p_Node;
	char* string;
	I32 integer;
} bbTestNode;

typedef I32 bbTreeFunction (void* reference, void* node);

/// add a new node (with no daughter nodes) as a daughter node to parent;
I32 bbNode_setParent(void* node, void* parent, bbPool* pool);
///recursively search through nodes until myFunc(node); returns f_Break
I32 descending_search(void* reference, void* root, bbTreeFunction* myFunc, bbPool* pool);
///recursively search through nodes until myFunc(node); returns f_Break
I32 ascending_search(void* reference, void* root, bbTreeFunction* myFunc, bbPool* pool);

///recursively search through nodes until myFunc(node); returns f_Break
I32 descending_searchVisible(void* reference, void* root, bbTreeFunction* myFunc, bbPool* pool);
///recursively search through nodes until myFunc(node); returns f_Break
I32 ascending_searchVisible(void* reference, void* root, bbTreeFunction* myFunc, bbPool* pool);

#endif // BBTREE_H;