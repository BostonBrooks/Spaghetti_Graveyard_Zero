#include <stdio.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Network.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbTerminal.h"

int main(void){
    bbDebug("Hello, server!\n");

    I32 port = 80;
    sfTcpListener* listener = sfTcpListener_create();
    sfSocketStatus status = sfTcpListener_listen(listener,port,sfIpAddress_Any);
    bbAssert(status == sfSocketDone, "Could not connect to client");

    sfSocketSelector* selector = sfSocketSelector_create();
    sfSocketSelector_addTcpListener(selector, listener);

    sfSocketSelector_wait(selector, sfSeconds(60));
    if (sfSocketSelector_isTcpListenerReady(selector,listener) == sfFalse)
        exit(EXIT_FAILURE);

    bbDebug("we made it this far!");

    exit(EXIT_SUCCESS);



}