/**
 * @file
 * @brief bbTree defines a structure where each member has a parent and a list of daughter nodes.
 *
 */
#include <stddef.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbFlag.h"

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
	size_t offset;
	bbPool_Handle root;
} bbTree;

typedef bbFlag bbTreeFunction(bbTree* tree, void* node, void* cl);

bbFlag bbTree_new (bbTree** tree, void* pool, size_t offset);

bbFlag bbNode_setEmpty(bbTree* tree, void* element);
/// add a new node as a daughter node to parent;
bbFlag bbNode_setParent(bbTree* tree, void* node, void* parent);
///recursively search through nodes until myFunc(node, cl); returns f_Break
bbFlag descending_map(bbTree* tree,
					  void* root,
					  bbTreeFunction* myFunc,
					  void* cl);
///recursively search through nodes until myFunc(node, cl); returns f_Break
bbFlag ascending_map(bbTree* tree,
					 void* root,
					 bbTreeFunction* myFunc,
					 void* cl);

///recursively search through nodes until myFunc(node, cl); returns f_Break
bbFlag descending_searchVisible(bbTree* tree,
							 void* root,
							 bbTreeFunction* myFunc,
							 void* cl);
///recursively search through nodes until myFunc(node, cl); returns f_Break
bbFlag ascending_searchVisible(bbTree* tree,
							void* root,
							bbTreeFunction* myFunc,
							void* cl);
