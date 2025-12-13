#include <stdio.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Network.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbTerminal.h"
#include "chatroom/io.h"

int main(void)
{
    get_IPAddress("enter some text that might be an IP address: ");
    return 0;
}