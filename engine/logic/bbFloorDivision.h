/**
 * @brief Divide two integers and round down
 *
*/


#include "engine/logic/bbTerminal.h"
#include <stdlib.h>

/// divide two integers and round down
static int floordiv (int a , int b){
    bbAssert(b != 0, "divide by zero\n");

    int c = abs(b);
    int d = a / c;
    if (a % c == 0) return d;
    if (a < 0) return (d - 1);
    return d;

}