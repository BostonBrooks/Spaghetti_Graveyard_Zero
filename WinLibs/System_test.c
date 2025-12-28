#include <stdio.h>
#include <stdlib.h>
#include <SFML/System.h>
#include <unistd.h>

int main (void)
{
    char cwd[1024];
    getcwd(cwd, 1024);
    char command[1024];
    printf("cwd = %s\n", cwd);
    sprintf(command, "start test.cmd", cwd);
    system(command);
    sfSleep(sfSeconds(10));
    exit(0);
}
