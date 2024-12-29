/**
 * @file
 * @brief List A is a list of lists of type B. List A is sorted by the largest
 * element of each list B. process largest element from the list B containing
 * the largest largest element. We then sort that list B back into list A
 */


#ifndef BBLISTLIST_H
#define BBLISTLIST_H

#include "engine/logic/bbList.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>


typedef struct {
    int value;
    bbPool_ListElement listElement;
} element;

typedef struct {

    bbPool_ListElement listElement;
    bbList listB;
} listB;


int main(void){
    bbVPool* poolB;
    bbVPool_newLean(&poolB, sizeof(element), 1000);
    bbVPool* poolA;
    bbVPool_newLean(&poolA, sizeof(listB), 16);




}

#endif //BBLISTLIST_H