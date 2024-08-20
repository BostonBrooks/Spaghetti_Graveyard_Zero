#include "engine/logic/bbTerminal.h"
#include <stdio.h>


#define printc(c) printf("%s\n", #c);

int main(void){

    printc(0 == 1);


    bbPrintf("Plain old printf\n");
    bbHere();
    bbDebug("debug message\n");
    bbWarning (0 == 1, "huge load\n");

    bbAssert(0 == 1, "message %d\n", 193);

}