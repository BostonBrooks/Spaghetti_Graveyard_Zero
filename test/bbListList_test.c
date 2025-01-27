/**
 * @file
 * @brief List A is a list of lists of type B. List A is sorted by the largest
 * element of each list B. process largest element from the list B containing
 * the largest largest element. We then sort that list B back into list A
 *
 * list B represents a lost of drawables in a map square
 * list A represents a list of map squares visible to the player
 */


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "engine/logic/bbList.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbNestedList.h"


typedef struct {
    int value;
	int i, j;
    bbPool_ListElement listElement;
} element;

typedef struct {
    element element1;
    int k;
} elementB;

I32 compare (void* A, void* B){
	element* elementA = A;
	element* elementB = B;
	return (elementA->value < elementB->value);
}


int main(void){

    bbVPool* pool1;
    bbVPool_newLean(&pool1, sizeof (element), 100);
    bbList listArray1[3];

    bbVPool* pool2;
    bbVPool_newLean(&pool2, sizeof (elementB), 100);
    bbList listArray2[3];


    bbDebug("Creating lists A:\n");
    for (int i = 0; i<3; i++){
        bbList_init(&listArray1[i],
                    pool1,
                    NULL,
                    offsetof(element, listElement),
                    compare);
        for (int j = 0; j < 4; j++){
            element* element1;
            bbVPool_alloc(pool1, &element1);
            element1->value = rand() % 16;
            element1->i = i;
            element1->j = j;
            element1->listElement.prev = pool1->null;
            element1->listElement.next = pool1->null;
            bbList_sortL(&listArray1[i], element1);
        }
    }
    bbDebug("Creating lists B:\n");
    for (int i = 0; i<3; i++){
        bbList_init(&listArray2[i],
                    pool2,
                    NULL,
                    offsetof(elementB, element1.listElement),
                    compare);
        for (int j = 0; j < 4; j++){
            elementB* element1;
            bbVPool_alloc(pool2, &element1);
            element1->element1.value = rand() % 16;
            element1->element1.i = i;
            element1->element1.j = j;
            element1->element1.listElement.prev = pool2->null;
            element1->element1.listElement.next = pool2->null;
            bbList_sortL(&listArray2[i], element1);
        }
    }

    bbDebug("Creating list of list\n");
    bbNestedList listA;
    bbNestedList_init(&listA);

    bbDebug("Populating list of list\n");
    for(int i = 0; i < 3; i++){
        bbNestedList_attach(&listA, &listArray1[i]);
    }

    bbDebug("Populating list of list 2: electric boogaloo\n");

    for(int i = 0; i < 3; i++){
        bbNestedList_attach(&listA, &listArray2[i]);
    }


    bbDebug("Iterating list of list\n");

    while (1){
        element* element1;
        bbFlag flag = bbNestedList_getNext(&listA, &element1);
        if (flag != Success) break;
        printf("value = %d, i = %d, j = %d\n",
               element1->value, element1->i, element1->j);
    }

    bbDebug("We made it to the end\n");
}




