#include <stdio.h>
#include <stdlib.h>
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbTree.h"

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
    bbVPool_newLean(&pool, sizeof(testStruct), 1024);

    bbTree* tree;
    bbTree_new(&tree, pool, offsetof(testStruct, tree));

    testStruct* element;
    bbVPool_alloc(pool, &element);
    bbNode_setEmpty(tree, element);
    sprintf(element->str, "ROOT ELEMENT");
    bbPool_Handle handle;
    bbVPool_reverseLookup(pool, element, &handle);

    tree->root = handle;

    for (I32 i = 0; i < 3; i++){
        testStruct* elementI;
        bbVPool_alloc(pool, &elementI);
        bbNode_setEmpty(tree, elementI);
        sprintf(elementI->str, "    i = %d", i);
        bbNode_setParent(tree, elementI, element);

        for (I32 j = 0; j < 4; j++){
            testStruct* elementJ;
            bbVPool_alloc(pool, &elementJ);
            bbNode_setEmpty(tree, elementJ);
            sprintf(elementJ->str, "        j = %d", j);
            bbNode_setParent(tree, elementJ, elementI);

            for (I32 k = 0; k < 0; k++){
                testStruct* elementK;
                bbVPool_alloc(pool, &elementK);
                bbNode_setEmpty(tree, elementK);
                sprintf(elementK->str, "            k = %d", k);
                bbNode_setParent(tree, elementK, elementJ);

            }

        }

    }

    descending_search(tree, element, testFunc, NULL);

}