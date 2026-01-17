#include "engine/logic/bbArith.h"
#include <stdio.h>

int main(void){
    int result;

    result = bbArith_div(5, 7);
    printf("5 // 7 = %d\n", result);

    result = bbArith_div(-5, 7);
    printf("-5 // 7 = %d\n", result);

    result = bbArith_div(5, -7);
    printf("5 // -7 = %d\n", result);

    result = bbArith_div(-5, -7);
    printf("-5 // -7 = %d\n", result);



    result = bbArith_div(14, -7);
    printf("14 // -7 = %d\n", result);

    //printf("The next line is expected to fail:\n");
    //result = bbArith_div(-5, 0);
    //printf("-5 // -7 = %d\n", result);

    result = (-69) % 10;
    printf("-69 %% 10 = %d\n", result);

    result = bbArith_mod(-69, 10);
    printf("-69 mod 10 = %d\n");

    result = bbArith_ceiling(2,3);
    printf("ceil(2/3) = %d\n", result);

    result = bbArith_floor(2,3);
    printf("floor(2/3) = %d\n", result);

    result = bbArith_roundUp(15, 10);
    printf("15 rounded up to the nearest 10 is %d\n", result);

    result = bbArith_roundDown(15, 10);
    printf("15 rounded down to the nearest 10 is %d\n", result);

}