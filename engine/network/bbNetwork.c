#include "bbNetwork.h"

#include <stdio.h>
#include <stdlib.h>


bbFlag bbNetwork_init(bbNetwork** self, sfIpAddress address, I32 port)
{




    sfTcpSocket* socket = sfTcpSocket_create();
    sfSocketStatus status;
    status = sfTcpSocket_connect(socket, address,port, sfSeconds(15));

    if (status != sfSocketDone)
    {
        printf("Could not connect to the given port!\n\n");
        return None;
    }


    return Success;
}
