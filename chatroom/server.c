#include <stdio.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Network.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbTerminal.h"

int main(void){
    printf("Hello, server!\n");

    I32 port = 80;
    sfTcpListener* listener = sfTcpListener_create();
    sfSocketStatus status = sfTcpListener_listen(listener,port,sfIpAddress_Any);
    //sfSocketStatus_print(status);

    sfTcpSocket* sockets[8];
    for (int i = 0; i < 8; ++i) {
        sockets[i] = NULL;
    }


    printf("Waiting for clients to connect...\n");

    sfSocketSelector* selector = sfSocketSelector_create();
    sfSocketSelector_addTcpListener(selector, listener);

    while(1){
        sfBool flag = sfFalse;
        while (flag == sfFalse) {
            flag = sfSocketSelector_wait(selector, sfSeconds(10));

            //bbHere();
        }
//bbHere()
        if (sfSocketSelector_isTcpListenerReady(selector,listener) == sfTrue) {
            sfTcpSocket *socket = NULL;
            //socket = sfTcpSocket_create();
            status = sfTcpListener_accept(listener, &socket);
            //sfSocketStatus_print(status);
            if (status != sfSocketDone) {
                printf("Could not accept socket\n");
            } else {}
            //bbHere();
            int i = 0;
            while (sockets[i] != NULL) {
                i++;
                //bbDebug("i = %d\n", i)
            }
            if (i < 8) {
                //bbHere();
                sockets[i] = socket;
                sfSocketSelector_addTcpSocket(selector, socket);
            } else {
                //bbHere();
                sfTcpSocket_destroy(socket);
                printf("Socket array full\n");
            }

        }



        for(int i = 0; i < 8;i++){
            if (sockets[i] == NULL) continue;
            //bbHere();
            if(sfSocketSelector_isTcpSocketReady(selector, sockets[i]) ==
            sfTrue){
                //bbHere();
                sfPacket* packet;
                packet = sfPacket_create();
                status = sfTcpSocket_receivePacket(sockets[i], packet);
                if (status != sfSocketDone){
                    sfTcpSocket_destroy(sockets[i]);
                    sockets[i] = NULL;
                    continue;
                }
//bbHere();
                char data[512];

                sfPacket_readString(packet,data);
                printf("message: %s\n", data);

                sfPacket* echoPacket;
                echoPacket = sfPacket_create();
                sfPacket_writeString(echoPacket,data);

                for (int j = 0; j < 8; j++){
                    //bbDebug("j = %d, socket = %p\n",j, sockets[j]);
                    if (j == i) continue;
                    if(sockets[j] == NULL) continue;
                    status = sfTcpSocket_sendPacket(sockets[j], echoPacket);

                    if (status != sfSocketDone){
                        printf("Failed to echo user %d's message!\n", j);
                    }
                }

                continue;
            }
            //bbHere();
        }

        //bbHere();

    }

    bbDebug("Server disconnected.\n");

    for (int i = 0; i < 8; i++){
        if(sockets[i]== NULL) continue;

        sfTcpSocket_disconnect(sockets[i]);
    }

    exit(EXIT_SUCCESS);



}