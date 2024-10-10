/**
 * @file
 * @brief bbTree defines a structure where each member has a parent and a list of daughter nodes.
 *
 */

#include "engine/logic/bbPool.h"

typedef struct {
    bbPool_Handle parent;
    bbPool_ListElement peers;
    bbPool_List children;
    I32 numchildren;
    bool visible;
    bool childrenvisible;
} bbTree;

typedef I32 bbTreeFunction(void* node, void* cl);

/// add a new node (with no daughter nodes) as a daughter node to parent;
I32 bbNode_setParent(bbPool_common* pool, void* node, void* parent);
///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 descending_search(bbPool_common* pool,
                      void* root,
                      bbTreeFunction* myFunc,
                      void* cl);
///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 ascending_search(bbPool_common* pool,
                     void* root,
                     bbTreeFunction* myFunc,
                     void* cl);

///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 descending_searchVisible(bbPool_common* pool,
                             void* root,
                             bbTreeFunction* myFunc,
                             void* cl);
///recursively search through nodes until myFunc(node, cl); returns f_Break
I32 ascending_searchVisible(bbPool_common* pool,
                            void* root,
                            bbTreeFunction* myFunc,
                            void* cl);
