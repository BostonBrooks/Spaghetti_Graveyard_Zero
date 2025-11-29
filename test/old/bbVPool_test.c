#include <stdio.h>
#include <stdlib.h>
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbBloatedPool.h"
#include "engine/logic/bbLeanPool.h"
#include "engine/logic/bbVPool.h"


typedef struct {
	I32 i;
	char str[64];
} testStruct;

int main(void){
	bbVPool* Pool;

	bbPool_Handle elements[100];
	testStruct* element;
	bbPool_Handle handle;

	printf("Lean Pool:\n");
	bbVPool_newLean(&Pool, sizeof(testStruct), 5);

	for (I32 i = 0; i < 5; i++){
		bbVPool_alloc(Pool, &element);
		element->i = i;
		sprintf(element->str, "i = %d", i);

		bbVPool_reverseLookup(Pool, element, &elements[i]);
		printf("i = %d, element @%d\n", i, (U64)element%32);

	}
	for (I32 i = 0; i < 5; i++){
		bbVPool_lookup(Pool, &element, elements[i]);
		printf("i = %d, element->i = %d, str = \"%s\"\n", i, element->i, element->str);
	}

	bbVPool_delete(Pool);
	printf("\n");

	printf("Bloated Pool:\n");

/* TODO something wrong with second call to bbBloatedPool_expand,
 * bad collision check
	bbVPool_newBloated(&Pool, sizeof(testStruct), 5, 5);

	for (I32 i = 0; i < 6; i++){
		bbVPool_alloc(Pool, (void**)&element);
		element->i = i;
		sprintf(element->str, "i = %d", i);
		bbVPool_reverseLookup(Pool, element, &elements[i]);
		//printf("elements[%d].self = %d\n", i, elements[i].bloated.index);
	}
	for (I32 i = 0; i < 6; i++){
		bbVPool_lookup(Pool, (void**)&element, elements[i]);
		printf("elements[%d].bloated.index = %d ", i ,elements[i].bloated.index);
		printf("i = %d, str = \"%s\"\n", element->i, element->str);
	}
*/
	bbVPool_delete(Pool);

	exit(0);
}