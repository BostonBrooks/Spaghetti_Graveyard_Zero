

#include <pthread.h>
#include <stdio.h>

#include "engine/logic/bbTerminal.h"
#include "engine/network/bbNetwork.h"
#include "engine/network/bbNetwork_packet.h"

_Thread_local char* thread;


//typedef bbFlag bbNetwork_onConnect (void* network);
bbFlag connect(void* network)
{
    bbDebug("Connect to server in thread %s\n", thread);
    return Success;
}
//typedef bbFlag bbNetwork_onDisconnect (void* network);
bbFlag disconnect(void* network)
{
    bbDebug("Disconnect from server in thread %s\n", thread);
    return Success;
}

int main(void)
{

    printf("Hello Main\n");
    thread = "main";
    bbNetwork network;
    bbFlag flag;


    flag = bbNetwork_init(&network,
            bbNetwork_packet_toStruct,
            bbNetwork_struct_toPacket,
            connect,disconnect);

    sfIpAddress address = bbGetIPAddress("Input desired server's IP address: ");
    I32 port = bbGetInt("Input desired server's port: ");

    flag = bbNetwork_connect(&network, address, port);

    sfSleep(sfSeconds(120));

    exit(EXIT_SUCCESS);

}
