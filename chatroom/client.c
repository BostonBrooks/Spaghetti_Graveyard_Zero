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
    bbAssert(status == sfSocketDone, "Could not connect to server\n");

    bbDebug("Connected!\n");
}