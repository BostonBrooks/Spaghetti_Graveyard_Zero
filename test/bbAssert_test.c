#include "engine/logic/bbFloorDivision.h"
#include <stdio.h>

int main(void){
    int result;

    result = floordiv(5, 7);
    printf("5 // 7 = %d\n", result);

    result = floordiv(-5, 7);
    printf("-5 // 7 = %d\n", result);

    result = floordiv(5, -7);
    printf("5 // -7 = %d\n", result);

    result = floordiv(-5, -7);
    printf("-5 // -7 = %d\n", result);



    result = floordiv(14, -7);
    printf("14 // -7 = %d\n", result);

    printf("The next line is expected to fail:\n");

    result = floordiv(-5, 0);
    printf("-5 // -7 = %d\n", result);

}