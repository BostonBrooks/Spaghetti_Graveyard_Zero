#include "engine/logic/bbTree.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbFlag.h"
#include <stdlib.h>



#define isEqual(A, B) bbVPool_handleIsEqual(tree->pool, A, B)
#define isNULL(A) bbVPool_handleIsEqual(tree->pool, A, tree->pool->null)

bbFlag bbTree_new (bbTree** Tree, void* pool, size_t offset){
    bbTree* tree = malloc(sizeof(bbTree));
    bbVPool* Pool = pool;
    tree->pool = Pool;
    tree->root = Pool->null;
    tree->offset = offset;
    *Tree = tree;

    return Success;
}


bbFlag bbTreeNode_setEmpty(bbTree* tree, void* element){
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

//bbFlag bbList_pushR(bbList* list, void* element)
bbFlag bbTreeNode_setParent(bbTree* tree, void* element, void* parent){


    bbVPool* pool = tree->pool;

    bbPool_Handle elementHandle;
    bbPool_Handle parentHandle;

    bbVPool_reverseLookup(pool, element, &elementHandle);
    bbVPool_reverseLookup(pool, parent, &parentHandle);

    bbTree_Node* elementNode = element + tree->offset;
    bbTree_Node* parentNode = parent + tree->offset;

	bbAssert(isNULL(elementNode->peers.prev), "already in list\n");
	bbAssert(isNULL(elementNode->peers.next), "already in list\n");

    bbPool_Handle headHandle = parentNode->children.head;
    bbPool_Handle tailHandle = parentNode->children.tail;

    if (isNULL(headHandle)){
        bbAssert(isNULL(tailHandle), "head/tail\n");
        bbAssert(parentNode->numchildren == 0, "empty list but num != 0\n");
        parentNode->numchildren = 1;
        parentNode->children.head = elementHandle;
        parentNode->children.tail = elementHandle;
        elementNode->peers.prev = elementHandle;
        elementNode->peers.next = elementHandle;
        elementNode->parent = parentHandle;

        return Success;

    }

	void* head;
	bbVPool_lookup(tree->pool, &head, parentNode->children.head);
	bbTree_Node* headNode = head + tree->offset;

	void* tail;
	bbVPool_lookup(tree->pool, &tail, parentNode->children.tail);
	bbTree_Node* tailNode = tail + tree->offset;

	if(isEqual(headHandle, tailHandle)){
		bbAssert(parentNode->numchildren = 1, "only one element\n");


		elementNode->peers.prev = headHandle;
		elementNode->peers.next = tailHandle;

		headNode->peers.next = elementHandle;
		headNode->peers.prev = elementHandle;
		parentNode->children.tail = elementHandle;
		parentNode->numchildren = 2;

		return Success;
	}

	tailNode->peers.next = elementHandle;
	headNode->peers.prev = elementHandle;
	elementNode->peers.prev = tailHandle;
	elementNode->peers.next = headHandle;
	parentNode->children.tail = elementHandle;
	parentNode->numchildren++;

    return Success;
}


bbFlag bbTree_descendingMap(bbTree* tree, void* root, bbTreeFunction* myFunc,
                            void* cl)
{

	bbAssert(root != NULL, "null object address\n");
	bbTree_Node* rootNode = root + tree->offset;
	bbFlag flag = myFunc(tree, root, cl);


	if (flag == Break) return Break;

	if(isNULL(rootNode->children.head)){
		bbAssert(isNULL(rootNode->children.tail), "head/tail\n");
		return Continue;
	}

	bbPool_Handle elementHandle = rootNode->children.head;
	void* element;
	bbTree_Node* elementNode;

	while(1){

		bbVPool_lookup(tree->pool, &element, elementHandle);
		elementNode = element + tree->offset;
		flag = bbTree_descendingMap(tree, element, myFunc, cl);
		switch(flag){
			case Break:
				return Break;
			case Continue:
				if(isEqual(elementHandle, rootNode->children.tail))
					return Continue;
				elementHandle = elementNode->peers.next;
				break;
			case Repeat:
				bbHere();
				break;
			default:
				bbHere();
                break;
		}
	}

}


bbFlag bbTree_ascendingMap(bbTree* tree, void* root, bbTreeFunction* myFunc,
                           void* cl) {

	bbAssert(root != NULL, "null object address\n");
	bbTree_Node* rootNode = root + tree->offset;
	bbFlag flag;

	if(isNULL(rootNode->children.head)){
		bbAssert(isNULL(rootNode->children.tail), "head/tail\n");
		goto label;
	}

	bbPool_Handle elementHandle = rootNode->children.tail;
	void* element;
	bbTree_Node* elementNode;

	while(1){
		bbVPool_lookup(tree->pool, &element, elementHandle);
		elementNode = element + tree->offset;
		flag = bbTree_ascendingMap(tree, element, myFunc, cl);
		switch(flag){
			case Break:
				return Break;
			case Continue:
				if(isEqual(elementHandle, rootNode->children.head))
					goto label;
				elementHandle = elementNode->peers.prev;
				break;
			case Repeat:
				bbHere();
				break;
			default:
				bbHere();
		}
	}
label:

	flag = myFunc(tree, root, cl);
	if(flag == Break) return Break;

	return Continue;

}

bbFlag bbTree_descendingMapVisible(bbTree* tree, void* root, bbTreeFunction* myFunc,
							void* cl)
{

	bbAssert(root != NULL, "null object address\n");
	bbTree_Node* rootNode = root + tree->offset;

	if(rootNode->visible) {
		bbFlag flag = myFunc(tree, root, cl);
		if (flag == Break) return Break;
	}

	if(isNULL(rootNode->children.head)){
		bbAssert(isNULL(rootNode->children.tail), "head/tail\n");
		return Continue;
	}

	bbPool_Handle elementHandle = rootNode->children.head;
	void* element;
	bbTree_Node* elementNode;
	bbFlag flag;

	if (rootNode->childrenvisible == false) return Continue;
	while(1){

		bbVPool_lookup(tree->pool, &element, elementHandle);
		elementNode = element + tree->offset;
		flag = bbTree_descendingMapVisible(tree, element, myFunc, cl);
		switch(flag){
			case Break:
				return Break;
			case Continue:
				if(isEqual(elementHandle, rootNode->children.tail))
					return Continue;
				elementHandle = elementNode->peers.next;
				break;
			case Repeat:
				bbHere();
				break;
			default:
				bbHere();
				break;
		}
	}

}

bbFlag bbTree_ascendingMapVisible(bbTree* tree, void* root, bbTreeFunction* myFunc,
						   void* cl) {

	bbAssert(root != NULL, "null object address\n");
	bbTree_Node* rootNode = root + tree->offset;
	bbFlag flag;

	if(isNULL(rootNode->children.head)){
		bbAssert(isNULL(rootNode->children.tail), "head/tail\n");
		goto label;
	}

	bbPool_Handle elementHandle = rootNode->children.tail;
	void* element;
	bbTree_Node* elementNode;

	if(rootNode->childrenvisible == false) goto label;
	while(1){
		bbVPool_lookup(tree->pool, &element, elementHandle);
		elementNode = element + tree->offset;
		flag = bbTree_ascendingMapVisible(tree, element, myFunc, cl);
		switch(flag){
			case Break:
				return Break;
			case Continue:
				if(isEqual(elementHandle, rootNode->children.head))
					goto label;
				elementHandle = elementNode->peers.prev;
				break;
			case Repeat:
				bbHere();
				break;
			default:
				bbHere();
		}
	}
	label:

	if(rootNode->visible) {
		flag = myFunc(tree, root, cl);
		if (flag == Break) return Break;
	}

	return Continue;

}