#include "engine/logic/bbPool.h"
#include "engine/logic/bbTerminal.h"

typedef struct {
	I32 integer;
	char string[128];
} structure;

int main(void){
	bbPool_common* pool;
	bbComplexPool_newPool(&pool, sizeof (structure), 7, 5);

	structure* structure1;
	bbPool_Handle handle[143];

	for(U32 i = 0; i < 143; i++) {
		bbPool_new(pool, &structure1, &handle[i]);
		bbPrintf("i = %d\n", i);
	}
}