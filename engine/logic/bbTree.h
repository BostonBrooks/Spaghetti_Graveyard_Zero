/**
 * @file
 * @brief bbTree defines a structure where each member has a parent and a list of daughter nodes.
 *
 */
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbVPool.h"

typedef struct {
	bbPool_Handle parent;
	bbPool_ListElement peers;
	bbPool_List children;
	I32 numchildren;
	bool visible;
	bool childrenvisible;

} bbTree_Node;

typedef struct {
	bbVPool* pool;
	bbTree_Node (*get_node)(void* element);
	bbPool_Handle root;
} bbTree;

typedef I32 bbTreeFunction(bbTree* tree, void* node, void* cl);

/// add a new node as a daughter node to parent;
I32 bbNode_setParent(bbTree* tree, void* node, void* parent);
///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 descending_search(bbTree* tree,
					  void* root,
					  bbTreeFunction* myFunc,
					  void* cl);
///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 ascending_search(bbTree* tree,
					 void* root,
					 bbTreeFunction* myFunc,
					 void* cl);

///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 descending_searchVisible(bbTree* tree,
							 void* root,
							 bbTreeFunction* myFunc,
							 void* cl);
///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 ascending_searchVisible(bbTree* tree,
							void* root,
							bbTreeFunction* myFunc,
							void* cl);
