#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbPoolHandle.h"
#include <stdio.h>
#include <stdlib.h>


int main (void){
    printf("sizeof I32 = %llu\n", sizeof(I32));
    printf("sizeof I64 = %llu\n", sizeof(I64));
    printf("sizeof I32x2 = %llu\n", sizeof(I32x2));
    printf("sizeof bbPool_Handle = %llu\n", sizeof(bbPool_Handle));
    exit(1);
}