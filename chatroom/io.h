#ifndef NETWORKING_IO_H
#define NETWORKING_IO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//io.hpp defines a colour palette for windows/not windows

 void clear_line(int lines)
{
//    \r     #go to the start of the current line
//    \033[F #back to previous line
//    \033[K #delete everything from the cursor to the end of the line

    for(int i = 0; i <= lines;i++)
    {
        printf("\r\033[K");
        if (i<lines) printf("\033[F");
    }
     fflush(stdout);
}

 int get_integer_input(char* prompt)
{
    int number;
    char answer[64];
    while(1){
        printf("%s", prompt);

        scanf("%s", answer);

        int len = strlen(answer);
        char digits[] = "0123456789";
        int int_len = strspn(answer, digits);

        if(len == int_len) {

            number = atoi(answer);
            return (number);
        }
        clear_line(2);

        printf("Invalid input. Please enter a valid integer.\n");


    }
}

int get_valid_username(char* username, char* prompt)
{

    printf("%s", prompt);
    char answer[64];
    int len;

    scanf("%s", answer);
    len = strlen(answer);

    while (len > 24 || len < 3)
    {
        clear_line(1);
        printf("Invalid username length, try again: ");
        scanf("%s", answer);
        len = strlen(answer);
    }
    strcpy(username, answer);

    return 1;

}
#endif //NETWORKING_IO_H