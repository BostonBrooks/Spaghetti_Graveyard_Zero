#include <stdio.h>

//Similar but not the same as one of the answers on
// https://stackoverflow.com/questions/314401/how-to-read-a-line-from-the-console-in-c
int get_line(char* string, int length, FILE* fp)
{
    int chars = 0;
    int c = '\0';

    while(1){
        c = fgetc(fp);

        if(c == EOF || c == '\n') break;

        string[chars] = c;

        if(chars >= length-1) break;
        chars++;
    }

    string[chars+1] = '\0';

    return chars+1;
}

int main (void)
{
    char string[8];
    int len;
    while(1) {

        printf("enter txt\n");

        len = get_line(string, 8, stdin);

        printf("length = %d, string \"%s\"]\n", len, string);
    }
}