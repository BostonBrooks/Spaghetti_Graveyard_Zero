/**
 * @brief Divide two integers and round down
 *
*/


#include "engine/logic/bbTerminal.h"
#include <stdlib.h>

/// divide two integers and round down
static int floordiv (int a , int b){
    bbAssert(b > 0, "denominator should be positive\n");

    int d = a / b;
    if (a % b == 0) return d;
    if (a < 0) return (d - 1);
    return d;

}