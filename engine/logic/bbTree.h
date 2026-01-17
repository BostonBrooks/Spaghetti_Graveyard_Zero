/**
 * @file
 * @brief bbTree defines a structure where each member has a parent and a list of daughter nodes.
 *
 */

#ifndef BBTREE_H
#define BBTREE_H

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


bbFlag bbTree_init (bbTree* tree, void* pool, size_t offset);

bbFlag bbTreeNode_setEmpty(bbTree* tree, void* element);
/// add a new node as a daughter node to parent;
bbFlag bbTreeNode_setParent(bbTree* tree, void* element, void* parent);
///recursively search through nodes until myFunc(node, cl); returns f_Break
bbFlag bbTree_descendingMap(bbTree* tree,
                            void* root,
                            bbTreeFunction* myFunc,
                            void* cl);
///recursively search through nodes until myFunc(node, cl); returns f_Break
bbFlag bbTree_ascendingMap(bbTree* tree,
                           void* root,
                           bbTreeFunction* myFunc,
                           void* cl);

///recursively search through nodes until myFunc(node, cl); returns f_Break
bbFlag bbTree_descendingMapVisible(bbTree* tree,
							void* root,
							bbTreeFunction* myFunc,
							void* cl);
///recursively search through nodes until myFunc(node, cl); returns f_Break
bbFlag bbTree_ascendingMapVisible(bbTree* tree,
							void* root,
							bbTreeFunction* myFunc,
							void* cl);

#endif //BBTREE_H