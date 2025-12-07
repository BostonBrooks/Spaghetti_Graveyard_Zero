#include <stdio.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Network.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbTerminal.h"


int main(void){
    printf("Hello, client!\n");


    I32 port = 80;
    sfIpAddress address = sfIpAddress_fromString("127.0.0.1");
    sfTcpSocket* socket = sfTcpSocket_create();
    sfSocketStatus status = sfTcpSocket_connect(socket, address, port, sfSeconds(10));
    sfSocketStatus_print(status);


    sfTcpSocket_setBlocking(socket, sfFalse);

    bbDebug("Connected to server!\n");
    sfSleep(sfSeconds(1));
    bbDebug("Sending message...\n");

    char username[] = "Toblerone rollo combo\n";

    sfPacket* startingPacket = sfPacket_create();
    sfPacket_writeString(startingPacket, "Celebrate good times!\n");
    while(1) {
        status = sfTcpSocket_sendPacket(socket, startingPacket);
        sfSocketStatus_print(status);
        sfSleep(sfSeconds(1));
    }
}