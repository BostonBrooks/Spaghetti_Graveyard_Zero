#include <stdio.h>
#include <pthread.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Network.h>
#include <time.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbTerminal.h"
#include "chatroom/io.h"

void send_messages(sfTcpSocket* socket, char* username);
void receive_messages(sfTcpSocket* socket);
void* test_function(void* args);

int main(void){
    printf("Hello, client!\n");
    srand(time(NULL));

    I32 port = get_integer_input("Input desired server's port: ");
    sfIpAddress address = sfIpAddress_fromString("127.0.0.1");
    sfTcpSocket* socket = sfTcpSocket_create();
    sfSocketStatus status = sfTcpSocket_connect(socket, address, port, sfSeconds(10));
    if (status != sfSocketDone) {
        printf("Could not connect to the given port!");
        exit(EXIT_FAILURE);
    }


    sfTcpSocket_setBlocking(socket, sfFalse);

    bbDebug("Connected to server!\n");

    char username[64];
    get_valid_username(username, "Please input your username: ");

    sfPacket* startingPacket = sfPacket_create();
    char packetString[80];
    sprintf(packetString, "%s connected.", username);
    sfPacket_writeString(startingPacket, packetString);

    pthread_t test_thread;
    pthread_create(&test_thread, NULL, test_function, NULL);

    while(1) {
        //status = sfTcpSocket_sendPacket(socket, startingPacket);
        //sfSocketStatus_print(status);
        printf("main thread\n");
        sfSleep(sfSeconds(1));
    }
}

void* test_function(void* args)
{
    while(1){
        printf("Test messages thread\n");
        sfSleep(sfSeconds(1));
    }
}

void send_messages(sfTcpSocket* socket, char* username)
{
    while(1){
        printf("Send messages thread\n");
        sfSleep(sfSeconds(1));
    }
}

void receive_messages(sfTcpSocket* socket)
{
    while(1){
        printf("receive messages thread\n");
        sfSleep(sfSeconds(1));
    }
}