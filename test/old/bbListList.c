/**
 * @file
 * @brief List A is a list of lists of type B. List A is sorted by the largest
 * element of each list B. process largest element from the list B containing
 * the largest largest element. We then sort that list B back into list A
 *
 * list B represents a lost of drawables in a map square
 * list A represents a list of map squares visible to the player
 */


#include "engine/logic/bbList.h"
#include "engine/logic/bbTerminal.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "engine/logic/bbLeanPool.h"


typedef struct {
    int value;
	int i, j;
    bbPool_ListElement listElement;
} element;

typedef struct {

	bbList listB; //bbList is first element
    bbPool_ListElement listElement;

} listB;

I32 compare (void* A, void* B){
	element* elementA = A;
	element* elementB = B;
	return (elementA->value < elementB->value);
}

I32 compare_list(void* one, void* two){


	void *element1, *element2;

	bbList_getCurrent(one, &element1);
	bbList_getCurrent(two, &element2);
	bbList* list = one;

	return list->compare(element1, element2);


}

int main(void){

    bbVPool* poolB;
    bbVPool_newLean(&poolB, sizeof(element), 1000);
    bbVPool* poolA;
    bbVPool_newLean(&poolA, sizeof(listB), 16);

	// this represents populating the map with drawables
    bbDebug("Creating lists:\n");
	listB listBArray[16];
	for (int i=0;i<3;i++){
		bbList_init(&listBArray[i].listB, poolB, NULL, offsetof(element, listElement),compare);
		element* element1;

		for (int j = 0; j < 4; j++) {
			bbVPool_alloc(poolB, &element1);
			element1->listElement.prev = poolB->null;
			element1->listElement.next = poolB->null;
			element1->value = rand()%16;
			element1->i = i;
			element1->j = j;
			bbList_pushL(&listBArray[i].listB, element1);
		}
		bbList_sort(&listBArray[i].listB);
        bbList_setHead(&listBArray[i].listB, NULL);
	}

	// this represents populating a list of visible squares

	bbList listA;
	bbList_init(&listA, poolA, NULL, offsetof(listB, listElement),compare_list);

	listB* listB1;
    for (int n = 0; n < 3; n++){
        bbDebug("Creating list of lists:\n");
        for (int i=0;i<3;i++){
            bbVPool_alloc(poolA, &listB1);
            listB1->listB = listBArray[i].listB;
            listB1->listElement.prev = poolA->null;
            listB1->listElement.next = poolA->null;
            bbList_pushL(&listA, listB1);
        }

        bbList_sort(&listA);

        /* this is to check if the lists were populated correctly

        for (int i = 0; i<16;i++){
            bbList_popL(&listA, &listB1);
            element* element1;
            for (int j = 0; j < 1; j++){
                bbList_popL(&listB1->listB, &element1);

                printf("value = %d, i = %d, j = %d\n", element1->value, element1->i, element1->j);
            }
        }

        */

        /*
        while(1){
            bbList_popL(&listA,&listB1);
            element* element1;
            bbList_popL(&listB1->listB, &element1);
            printf("value = %d, i = %d, j = %d\n", element1->value, element1->i, element1->j);
            if(Success == bbList_setHead(&listB1->listB, NULL)) {
                bbList_sortL(&listA, listB1);
            }

        }
    */

        bbDebug("Iterating lists\n");
        while(1) {
            bbList_popL(&listA, &listB1);
            element *element1;
            bbList_getCurrent(&listB1->listB, &element1);
            printf("value = %d, i = %d, j = %d\n", element1->value, element1->i,
                   element1->j);
            bbFlag flag = bbList_increment(&listB1->listB, NULL);

            if (flag == Success) {
                bbList_sortL(&listA, listB1);
            } else {
                bbVPool_free(poolA, listB1);
                if (bbList_isEmpty(&listA)) break;
            }
        }
    }

}

