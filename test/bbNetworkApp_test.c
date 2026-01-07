

#include "engine/network/bbNetworkApp.h"

#include <pthread.h>
#include <stdio.h>

#include "engine/logic/bbTerminal.h"
#include "engine/network/bbNetwork.h"
#include "engine/network/bbNetworkPacket.h"
#include "engine/network/bbNetworkTime.h"

#include "engine/threadsafe/bbThreadedPool.h"

_Thread_local char* thread;



int main(void)
{

    printf("Hello Main\n");
    thread = "main";
    bbNetwork network;
    bbFlag flag;

    bbNetworkApp_init(&network);

    char address[64];
    bbStr_setStr(address, "127.0.0.1", 64);
    char port[64];
    bbStr_setStr(port, "1701", 64);


    //usually we would wait for the user to click before repeating
    while (1)
    {
        flag = bbNetworkApp_connect(&network, address, port);
        if (flag == Success) break;
    }
    printf("IP Address: %s, Port: %s\n", address, port);


    //use mutex
    sfSleep(sfSeconds(5));

    char str[64];
    for (int i = 0; true; i++)
    {


        sprintf(str, "i = %d", i);

        bbNetworkApp_sendString(&network, str);
        bbNetworkApp_sendTime(&network);


        //Do other things
        sfSleep(sfSeconds(0.2));

        bbNetworkApp_checkInbox(&network);
        bbNetworkApp_checkTime(&network);
    }

    exit(EXIT_SUCCESS);

}