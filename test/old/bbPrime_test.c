#include "engine/logic/bbPrime.h"
#include "engine/logic/bbIntTypes.h"
#include <stdio.h>

I32 main (void){

	I32 j = 2;
	printf("j = %d\n", j);

	for (I32 i = 0; i < 1028;i++){
		j = nextPrime(j+1);

		printf("j = %d\n", j);
	}

}