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
} send_thread_args;

void* send_messages(void* args);
void* receive_messages(void* Socket);

int main(void){
    printf("Hello, client!\n");
    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);

    sfIpAddress address;
    sfSocketStatus status;
    I32 port;
    sfTcpSocket* socket = sfTcpSocket_create();

while (1){
    address = get_IPAddress("Input desired server's IP address: ");
    port = get_integer_input("Input desired server's port: ");
    status = sfTcpSocket_connect(socket, address, port, sfSeconds(10));

    if (status != sfSocketDone) {
        printf("Could not connect to the given port!\n\n");
        continue;
    }
    break;
}

    sfTcpSocket_setBlocking(socket, sfFalse);

    bbDebug("Connected to server!\n");

    char username[64];
    get_valid_username(username, "Please input your username: ");

    sfPacket* startingPacket = sfPacket_create();
    char packetString[80];
    sprintf(packetString, "%s connected.", username);
    sfPacket_writeString(startingPacket, packetString);
    status = sfTcpSocket_sendPacket(socket, startingPacket);


    pthread_t send_thread, receive_thread;
    send_thread_args args;
    args.socket = socket;
    args.username = username;

    pthread_create(&send_thread,NULL, send_messages, &args);
    pthread_create(&receive_thread,NULL, receive_messages, socket);

    pthread_join(send_thread, NULL);
    pthread_join(receive_thread, NULL);

    sfPacket* disconnectPacket;
    disconnectPacket = sfPacket_create(); //destroy?
    sprintf(packetString, "%s disconnected", username);
    sfTcpSocket_sendPacket(socket, disconnectPacket);
    printf("Disconnected.\n");

    sfTcpSocket_destroy(socket);


}


//void send_messages(sfTcpSocket* socket, char* username)
void* send_messages(void* Args)
{
    send_thread_args* args = (send_thread_args*) Args;
    sfTcpSocket* socket = args->socket;
    char* username = args->username;


    while(1)
    {
        printf("Input your message ('exit' to exit): ");
        fflush(stdout);

        char message[128];
        //scanf("%s", message);
        get_line(message, 128, stdin);
        clear_line(1);

        if (strcmp(message,"exit") == 0)
        {
            quit = true;
            printf( "Exiting...\n");
            fflush(stdout);
            return NULL;
        }
        char full_message[512];
        sprintf(full_message, "%s: %s", username, message);

        sfPacket* packet = sfPacket_create(); //destroy?
        sfPacket_writeString(packet, full_message);

        pthread_mutex_lock(&mutex);

        sfSocketStatus status;
        status = sfTcpSocket_sendPacket(socket, packet);


        if (status != sfSocketDone){
            printf("Could not send data!");
            fflush(stdout);
            exit(1);
        }
        pthread_mutex_unlock(&mutex);
    }
}

//void receive_messages(sfTcpSocket* socket)
void* receive_messages(void* Socket)
{
    sfTcpSocket* socket = (sfTcpSocket*) Socket;

    while(1)
    {
        if(quit) return NULL;


        sfPacket* received;
        received = sfPacket_create(); //destroy?

        pthread_mutex_lock(&mutex);

        sfSocketStatus status;
        status = sfTcpSocket_receivePacket(socket, received);

        if(status == sfSocketDone)
        {
            char message[512];
            sfPacket_readString(received, message);
            clear_line(0);
            printf("%s\n", message);
            printf("Input your message ('exit' to exit): ");
            fflush(stdout);

        }

        pthread_mutex_unlock(&mutex);
    }

}