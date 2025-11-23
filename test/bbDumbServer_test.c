#include "engine/dummyserver/bbDummySender.h"

int main (void)
{
    bbDummySender* server;
    bbDummySender_new(&server);

    U64 gameTime = 0;
    bbDummySender_msg* msg;

    char str[64];
    while (1)
    {
        printf("Message sent: %d\n", gameTime);
        sprintf(str, "%d\n", gameTime);


        bbDummySender_netSend(server, str, gameTime);
        bbDummySender_react(server, gameTime );

        sfSleep(sfMilliseconds(16));
        gameTime++;
    }
}