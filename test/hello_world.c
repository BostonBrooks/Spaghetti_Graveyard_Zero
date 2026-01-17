#include <stdio.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Network.h>
int main(void)
{
    printf("Hello World!\n");

    sfTime time;
    time = sfSeconds(60);
    int milliseconds = sfTime_asMicroseconds(time);

    printf("60 seconds is %d milliseconds\n", milliseconds);
    return 0;
}
