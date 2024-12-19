#include <stdio.h>
#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbPrime.h"
#include "engine/logic/bbIntTypes.h"
int main (void){

    bbDictionary* dict;
    bbDictionary_new(&dict, nextPrime(10));
    char str[KEY_LENGTH];
    bbPool_Handle handle;

    for (I32 i = 0; i < 64; i++){
        sprintf(str,"VIEWPORT_696969%d", i);
        handle.u64 = i;
        bbDictionary_add(dict, str, handle);
    }

    for (I32 i = 0; i < 64; i++){
        sprintf(str,"VIEWPORT_696969%d", i);
        bbDictionary_lookup(dict, str, &handle);
        printf("%llu\n", handle.u64);
    }


}