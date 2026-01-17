#include <stdio.h>
#include "engine/logic/bbIntTypes.h"
int main (void){
    U64 pTen = 10;
    U64 prevpTen = 10;

    for (U64 i = 0;; i++){
        if (i > pTen){
            pTen *= 10;
            if (pTen < prevpTen) break;
            prevpTen = pTen;
        }
        if (i == (i * i) % pTen) printf("%llu, ", i);
    }
    printf("\nSuccess\n");
}