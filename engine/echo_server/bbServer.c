#include <stdio.h>
#include "engine/includes/CSFML.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbIntTypes.h"
int main(void)
{
    printf("hello server!\n");

    sfIpAddress localAddress;
    localAddress = sfIpAddress_getLocalAddress();
    char localAddressString[64];
    sfIpAddress_toString(localAddress, localAddressString);


    sfIpAddress publicAddress;
    publicAddress = sfIpAddress_getPublicAddress(sfSeconds(120));
    char publicAddressString[64];
    sfIpAddress_toString(publicAddress, publicAddressString);

    bbPrintf("Local address = %s\nPublic address = %s\nLoopback address = 127.0.0.1\n",
       localAddressString, publicAddressString);

    I32 port = 1701;

    bbPrintf("Listening on port %d\n", port);

    sfTcpListener* listener = sfTcpListener_create();
    sfSocketStatus status = sfTcpListener_listen(listener,port,sfIpAddress_Any);

    if (status != sfSocketDone) {
        bbPrintf("Could not connect to port 1701\n");
        exit(EXIT_FAILURE);
    }

    bbPrintf("Waiting for clients to connect...\n");

    sfSocketSelector* selector = sfSocketSelector_create();
    sfSocketSelector_addTcpListener(selector, listener);

    while (1)
    {
        sfBool flag = sfFalse;
        I32 i = 1;
        while (flag == sfFalse)
        {
            flag = sfSocketSelector_wait(selector, sfSeconds(10));
            bbClr_line(1);
            bbPrintf("Waiting for clients to connect...(%d0 seconds)\n", i++);
        }
    }
    bbPrintf("We made it to the end!\n");
    return 0;
}
