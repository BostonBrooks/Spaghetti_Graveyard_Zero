/**
 * @brief String manipulations, with safety checks
 *
*/

#ifndef BBSTRING_H
#define BBSTRING_H

#include <stdlib.h>
#include <string.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbFlag.h"


/**if the string can be represented as an I32, the function
 * should return that number, otherwise, the function should
 * return I32_MAX = 2147483647
 * the minimum value the function can return is: I32_MIN + 1 = -2147483646
 **/


static I32 bbStr_toI32(char* Str){
    char* str = Str;
    I64 sign = 1;
    if (str[0] == '-'){
        sign = -1;
        str = &str[1];
    }

    int len = strlen(str);
    if (len > 16) return I32_MAX;

    char digits[] = "0123456789";
    int int_len = strspn(str, digits);

    if(len != int_len) return I32_MAX;

    I64 number = strtol(str,NULL, 10);
    number *= sign;

    if (number >= I32_MAX) return I32_MAX;
    if (number <= I32_MIN) return I32_MAX;

    return (I32)number;

}

/// strcpy()
static I32 bbStr_setStr(char* dest, char* src, I32 max){
    for(I32 i = 0; i < max; i++){
        dest[i] = src[i];
        if (src[i] == '\0') return f_Success;
    }
    dest[max - 1] = '\0';
    return f_None;
}

/// strcat()
static I32 bbStr_putStr(char* dest, char* src, I32 max){
    I32 i = 0;
    while(1){
        if(dest[i] == '\0') break;
        i++;
        if (i >= max){
            dest[max - 1] = '\0';
            return f_None;
        }
    }
    I32 j = 0;

    while(1){
        dest[i] = src[j];
        if (src[j] == '\0') return f_Success;
        i++;
        j++;
        if (i >= max){
            dest[max - 1] = '\0';
            return f_None;
        }
    }
}

/// add char to end of string
static I32 bbStr_putChar(char* dest, char src, I32 max){
    I32 i = 0;

    if (src == '\b')
    {
        if (dest[0] == '\0') return f_Success;

        while (1)
        {
            i++;
            if (i >= max)
            {
                dest[max - 1] = '\0';
                return f_Success;
            }
            if (dest[i] == '\0')
            {
                dest[i-1] = '\0';
                return f_Success;
            }
        }
    }


    while(1){
        if(dest[i] == '\0') break;
        i++;
        //the following:
        if (i >= max){
            dest[max - 1] = '\0';
            return f_None;
        }
    }


    //could be modified to include:
    if(i+1 >= max){
        dest[i] = '\0';
        return f_None;
    }
    dest[i] = src;
    dest[i+1] = '\0';
    return f_Success;
}

/// used to fit text to textbox size
// Works correctly by some inspiration and by some trial and error
//TODO final string may be longer than original string, take max into account
static I32 bbStr_setBounds(char* str, I32 columns, I32 rows, I32 max){

    if(str[0] == '\0') return f_Success;

    //temp could be a global
    char temp[1028];  //heap is slower than stack? stack overflow possible?

    // copy from str to temp, keeping track of chars since last \n
    // insert \n when necessary

    I32 i_str = 0;
    I32 i_temp = 0;
    I32 column = 0;

    while(1){

//Go through str and copy to temp, adding newlines when needed

        if (str[i_str] == '\0') {
            temp[i_temp] = '\0';
            break;
        }

        if (column > columns){
            if (str[i_str] != '\n'){
                temp[i_temp] = '\n';
                column = 0;
                i_temp++;
            }
        }


        if(str[i_str] == '\n') column = -1;

        temp[i_temp] = str[i_str];
        i_str++;
        i_temp++;
        column++;

    }

    // work backward and count off the number of rows to display
    I32 row = 0;


    i_temp--; //dont count final newline
    while (1) {
        if (i_temp <= 0) break;
        if (temp[i_temp - 1] == '\n') row++;
        if (row >= rows) break;
        i_temp--;
    }
    //Copy output back to str
    //TODO if output is larger than max, the start of the output should be
    // clipped
    bbStr_setStr(str, &temp[i_temp], max);

    return f_Success;
}

#endif //BBSTRING_H