#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbString.h"


int main (void){

    while(1) {
        printf("enter a number or some gibberish\n");
        char str[64];

        scanf("%s", str);

        I32 number = bbStr_toI32(str);

        if (number == INT32_MAX){
            printf("you entered an invalid number\n");
        } else {

            printf("you entered the number %d\n", number);
        }
    }

}