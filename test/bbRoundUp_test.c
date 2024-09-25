#include "engine/logic/bbArith.h"
#include <stdio.h>
#include <stdlib.h>

static int main(void){
	for (int i = 0; i < 16; i++){
		int a = rand() % 4096;
		int b = rand() % 16;
		int c = bbArith_roundUp(a, b);
		printf("%d roundup %d = %d, remainder = %d\n", a, b, c, c-a);
	}
}
