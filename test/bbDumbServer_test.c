#include "engine/dumbserver/bbDumbServer.h"

int main (void)
{
    bbDumbServer* server;
    bbDumbServer_new(&server);

    U64 gameTime = 0;
    bbDumbServer_msg* msg;

    char str[64];
    while (1)
    {
        printf("Message sent: %d\n", gameTime);
        sprintf(str, "%d\n", gameTime);


        bbDumbServer_netSend(server, str, gameTime);
        bbDumbServer_react(server, gameTime );

        sfSleep(sfMilliseconds(16));
        gameTime++;
    }
}