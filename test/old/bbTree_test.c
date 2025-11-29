#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbTree.h"
#include "engine/logic/bbTerminal.h"

typedef struct {
    char str[64];
    bbTree_Node tree;
} testStruct;

//typedef bbFlag bbTreeFunction(bbTree* tree, void* node, void* cl);
bbFlag testFunc(bbTree* tree, void* node, void* cl){
    testStruct* test = node;
    printf("%s\n", test->str);
    return Continue;
}

int main(void){
    bbVPool* pool;
    bbVPool_newLean(&pool, sizeof(testStruct), 76);
    //bbVPool_newBloated(&pool, sizeof(testStruct), 4, 19);

    bbTree* tree;
    bbTree_new(&tree, pool, offsetof(testStruct, tree));

    testStruct* element;
    bbVPool_alloc(pool, &element);
    bbTreeNode_setEmpty(tree, element);
    sprintf(element->str, "ROOT ELEMENT");
    bbPool_Handle handle;
    bbVPool_reverseLookup(pool, element, &handle);

    tree->root = handle;

    bbPrintf("Constructing Tree\n");
    for (I32 i = 0; i < 3; i++){
        testStruct* elementI;
        bbVPool_alloc(pool, &elementI);
        bbTreeNode_setEmpty(tree, elementI);
        sprintf(elementI->str, "    i = %d", i);
        printf("    i = %d\n", i);
        bbTreeNode_setParent(tree, elementI, element);

        for (I32 j = 0; j < 4; j++){
            testStruct* elementJ;
            bbVPool_alloc(pool, &elementJ);
            bbTreeNode_setEmpty(tree, elementJ);
            sprintf(elementJ->str, "        j = %d", j);
            printf("        j = %d\n", j);
            bbTreeNode_setParent(tree, elementJ, elementI);

            for (I32 k = 0; k < 5; k++){
                testStruct* elementK;
                bbVPool_alloc(pool, &elementK);
                bbTreeNode_setEmpty(tree, elementK);
                sprintf(elementK->str, "            k = %d", k);
                printf("            k = %d\n", k);
                bbTreeNode_setParent(tree, elementK, elementJ);

            }

        }

    }
    bbPrintf("Descending Tree Map\n");
    bbTree_descendingMap(tree, element, testFunc, NULL);
	bbPrintf("Ascending Tree Map\n");

    bbTree_ascendingMap(tree, element, testFunc, NULL);
    exit(EXIT_SUCCESS);
}