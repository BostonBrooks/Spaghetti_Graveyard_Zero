#include <stdio.h>
#include <pthread.h>
#include <SFML/System.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/Network.h>
#include <time.h>
#include <stdatomic.h>
#include <string.h>
#include "chatroom/io.h"

//used for debugging:
#include "engine/logic/bbTerminal.h"

pthread_mutex_t mutex;
atomic_bool quit = false;

typedef struct {
    sfTcpSocket* socket;
    char* username;
} send_messages_args;

//void send_messages(sfTcpSocket* socket, char* username);
void* send_messages(void* args);
//void receive_messages(sfTcpSocket* socket);
void* receive_messages(void* args);
void* test_function(void* args);

int main(void){
    printf("Hello, client!\n");
    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);

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

//void send_messages(sfTcpSocket* socket, char* username)
void* send_messages(void* Args)
{
    send_messages_args* args = (send_messages_args*) Args;
    sfTcpSocket* socket = args->socket;
    char* username = args->username;


    while(1)
    {
        printf("Input your message ('exit' to exit): ");
        fflush(stdout);

        char message[512];
        scanf("%s", message);
        clear_line(1);

        if (strcmp(message,"exit") == 0)
        {
            quit = true;
            printf( "Exiting...\n");
            return NULL;
        }
        char full_message[512];
        sprintf(full_message, "%s: %s", username, message);

        sfPacket* packet = sfPacket_create();
        sfPacket_writeString(packet, full_message);

        pthread_mutex_lock(&mutex);

        sfSocketStatus status;
        status = sfTcpSocket_sendPacket(socket, packet);


        if (status != sfSocketDone){
            printf("Could not send data!");
            exit(1);
        }
        pthread_mutex_unlock(&mutex);
    }
}

//void receive_messages(sfTcpSocket* socket)
void* receive_messages(void* Socket)
{
    sfTcpSocket* socket = (sfTcpSocket*) Socket;

}