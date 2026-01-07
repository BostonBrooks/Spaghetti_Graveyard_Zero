#include <pthread.h>
#include <stdio.h>

#include "engine/logic/bbTerminal.h"
#include "engine/network/bbNetwork.h"
#include "engine/network/bbNetworkPacket.h"
_Thread_local char* thread;




int main(void)
{

    thread = "main";
    bbNetwork network;
    bbFlag flag;

    printf("Connect to server\n");

    while (1){
        sfIpAddress address = bbGetIPAddress("Input desired server's IP address: ");
        I32 port = bbGetInt("Input desired server's port: ", 1701);
        flag = bbNetwork_init(&network,  bbNetworkPacket_toStruct, bbNetworkPacket_fromStruct, NULL, NULL)

        if (flag != Success) {
            printf("Could not connect to the given port!\n\n");
            continue;
        }
        break;
    }

    while (1)
    {

        sfSleep(sfSeconds(1));
        bbNetwork_checkInbox(&network);
    }
}
