

#include <pthread.h>
#include <stdio.h>

#include "engine/logic/bbTerminal.h"
#include "engine/network/bbNetwork.h"
#include "engine/network/bbNetworkPacket.h"

_Thread_local char* thread;


//typedef bbFlag bbNetwork_onConnect (void* network);
//Notify user interface of network connection
bbFlag bbConnect(void* network)
{
    bbDebug("Connect to server in thread %s\n", thread);
    return Success;
}
//typedef bbFlag bbNetwork_onDisconnect (void* network);
//Notify user interface of network connection
bbFlag bbDisconnect(void* network)
{
    bbDebug("Disconnect from server in thread %s\n", thread);
    return Success;
}


///react immediately to incoming message
bbFlag filterInbox (void* network, void* packet);
///react to outgoing message immediately before sending
bbFlag filterOutbox (void* network, void* packet);


int main(void)
{

    printf("Hello Main\n");
    thread = "main";
    bbNetwork network;
    bbFlag flag;


    flag = bbNetwork_init(&network,
            bbNetworkPacket_toStruct,
            bbNetwork_struct_toPacket,
            bbConnect,bbDisconnect,
            filterInbox,filterOutbox,NULL);

    sfIpAddress address = bbGetIPAddress("Input desired server's IP address: ");
    I32 port = bbGetInt("Input desired server's port: ", 1701);

    bbClearLine(1);
    printf("The port is %d\n", port);
    flag = bbNetwork_connect(&network, address, port);

    sfSleep(sfSeconds(2));
    bbNetworkPacket* packet;
    char str[64];
    for (int i = 0; true; i++)
    {
        //bbHere()
        sprintf(str, "i = %d", i);

        bbNetwork_sendStr(&network, str);
        bbNetwork_requestTimestamp(&network);
        printf("packet sent: %s\n", str);

        while (1)
        {
            flag = bbThreadedQueue_popR(&network.inbox, (void**)&packet);
            if (flag != Success) break;
            if (packet->type == PACKETTYPE_STRING)
            {
                printf("packet received: %s\n", packet->data.str);
            } else if (packet->type == PACKETTYPE_TIMESTAMP)
            {
                printf("packet received timestamp: %lu\n", packet->data.timestamp.receive_time);
            }else if (packet->type == PACKETTYPE_REQUESTTIMESTAMP)
            {
                bbHere()
            }
            bbThreadedQueue_free(&network.inbox, (void**)&packet);

        }

        //Do other things
        sfSleep(sfSeconds(0.2));
    }

    exit(EXIT_SUCCESS);

}


///react immediately to incoming message
bbFlag filterInbox (void* network, void* packet)
{
    bbHere()
    return Success;
}
///react to outgoing message immediately before sending
bbFlag filterOutbox (void* network, void* packet)
{
    bbHere()
    return Success;
}