//Copied form https://github.com/BostonBrooks/chatroom-in-c
//Which was translated from https://github.com/orichalcink/chatroom

#include <stdio.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Network.h>

#include "io.h"

int main(void){
    printf("Hello, server!\n");

    sfIpAddress localAddress;
    localAddress = sfIpAddress_getLocalAddress();
    char localAddressString[64];
    sfIpAddress_toString(localAddress, localAddressString);


    sfIpAddress publicAddress;
    publicAddress = sfIpAddress_getPublicAddress(sfSeconds(120));
    char publicAddressString[64];
    sfIpAddress_toString(publicAddress, publicAddressString);


    printf("Loopback address = 127.0.0.1\nLocal address = %s\nPublic address = %s\n",
        localAddressString, publicAddressString);

    int port = get_integer_input("Input server port: ");

    sfTcpListener* listener = sfTcpListener_create();
    sfSocketStatus status = sfTcpListener_listen(listener,port,sfIpAddress_Any);
    //sfSocketStatus_print(status);
    if (status != sfSocketDone) {
        printf("Could not connect to the given port!");
        exit(EXIT_FAILURE);
    }
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


        }

        if (sfSocketSelector_isTcpListenerReady(selector,listener) == sfTrue) {
            sfTcpSocket *socket = NULL;
            //socket = sfTcpSocket_create();
            status = sfTcpListener_accept(listener, &socket);
            //sfSocketStatus_print(status);
            if (status != sfSocketDone) {
                printf("Could not accept socket\n");
            } else {}

            int i = 0;
            while (sockets[i] != NULL) {
                i++;
                //bbDebug("i = %d\n", i)
            }
            if (i < 8) {

                sockets[i] = socket;
                sfSocketSelector_addTcpSocket(selector, socket);
            } else {

                sfTcpSocket_destroy(socket);
                printf("Socket array full\n");
            }

        }



        sfPacket* packet;
        packet = sfPacket_create();
        for(int i = 0; i < 8;i++){
            if (sockets[i] == NULL) continue;

            if(sfSocketSelector_isTcpSocketReady(selector, sockets[i]) ==
            sfTrue){

                sfPacket* packet;
                packet = sfPacket_create();
                status = sfTcpSocket_receivePacket(sockets[i], packet);
                if (status != sfSocketDone){
                    sfTcpSocket_destroy(sockets[i]);
                    sockets[i] = NULL;
                    continue;
                }

                printf("Received packet\n");

                //Send out incoming packet
                //sfPacket* echoPacket;
                //echoPacket = sfPacket_create();
                //sfPacket_writeString(echoPacket,data);

                for (int j = 0; j < 8; j++){
                    //send to self
                    //if (j == i) continue;
                    if(sockets[j] == NULL) continue;
                    status = sfTcpSocket_sendPacket(sockets[j], packet);

                    if (status != sfSocketDone){
                        printf("Failed to echo user %d's message!\n", j);
                    } else
                    {
                        printf("Sent packet\n");
                    }
                }
                sfPacket_clear(packet);

                continue;
            }

        }



    }

    printf("Server disconnected.\n");

    for (int i = 0; i < 8; i++){
        if(sockets[i]== NULL) continue;

        sfTcpSocket_disconnect(sockets[i]);
    }

    exit(EXIT_SUCCESS);



}
