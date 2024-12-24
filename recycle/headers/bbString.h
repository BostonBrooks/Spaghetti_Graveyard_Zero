/**
 * @file
 * @brief This file contains methods for manipulating strings
 * May want to do safety checks, later
 * these are small functions that are expected to be in-lined so I made them static
*/
#ifndef BBSTRING_H
#define BBSTRING_H

#include <inttypes.h>
#include "bbFlags.h"
#include "bbIntTypes.h"

// strcpy()
static I32 bbStr_setStr(char* dest, char* src){
    I32 i = 0;
    while(1){
        dest[i] = src[i];
        if (src[i] == '\0') return f_Success;
        i++;
    }
}

// strcat()
static I32 bbStr_putStr(char* dest, char* src){
    //search through string for \0
    I32 i = 0;

    while(1){
        if (dest[i] == '\0') break;
        i++;
    }
    //replace \0 with string

    bbStr_setStr(&dest[i], src);

}

// add char at end of string
static I32 bbStr_putChar(char* dest, char src){
    //search through string for \0
    I32 i = 0;

    while(1){
        if (dest[i] == '\0') break;
        i++;
    }
    dest[i] = src;
    dest[i+1]= '\0';
    //replace \0 with string

    //add \0 to end
}

// Works correctly by some inspiration and by some trial and error
static I32 bbStr_setBounds(char* str, I32 columns, I32 rows){

    if(str[0] == '\0') return f_Success;

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

    bbStr_setStr(str, &temp[i_temp]);

    return f_Success;
}


#endif //BBSTRING_H