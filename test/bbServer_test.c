#include <SFML/Network.h>
#include <pthread.h>
#include <stdio.h>
#include "engine/logic/bbFlag.h"
#include "engine/threadsafe/bbThreadedQueue.h"
#include "engine/logic/bbTerminal.h"

typedef struct
{
    char data[64];
    bbPool_ListElement listElement;
} listPacket;


///Take messages from a queue and send them to the server
void* send_messages(void*);

typedef struct
{
    sfTcpSocket* socket;
    bbThreadedQueue* queue;
} send_thread_args;

///Take messages from server and place on a queue
void* receive_messages(void*);

typedef struct
{
    sfTcpSocket* socket;
    bbThreadedQueue* queue;
} receive_thread_args;

///check messages in receive queue;
bbFlag check_inbox(bbThreadedQueue* queue);

pthread_mutex_t mutex;
_Thread_local char* thread;

int main(void)
{
    thread = "main";
    pthread_mutex_init(&mutex, NULL);

    printf("Connect to server\n");

    sfIpAddress address;
    sfSocketStatus status;
    int port;
    sfTcpSocket* socket = sfTcpSocket_create();

    bbThreadedQueue inbox;
    bbThreadedQueue_init(&inbox,NULL,sizeof(listPacket),100,offsetof(listPacket, listElement));

    bbThreadedQueue outbox;
    bbThreadedQueue_init(&outbox,NULL,sizeof(listPacket),100,offsetof(listPacket, listElement));

    while (1){
        address = bbGetIPAddress("Input desired server's IP address: ");
        port = bbGetInt("Input desired server's port: ",1701);
        status = sfTcpSocket_connect(socket, address, port, sfSeconds(20));

        if (status != sfSocketDone) {
            printf("Could not connect to the given port!\n\n");
            continue;
        }
        break;
    }

    sfTcpSocket_setBlocking(socket, sfFalse);
    printf("Connected to server\n");

    pthread_t send_thread;
    send_thread_args send_args;
    send_args.socket = socket;
    send_args.queue = &outbox;

    pthread_t receive_thread;
    receive_thread_args receive_args;
    receive_args.socket = socket;
    receive_args.queue = &inbox;


    pthread_create(&send_thread,NULL, send_messages, &send_args);
    pthread_create(&receive_thread,NULL, receive_messages, &receive_args);



    while (1)
    {
        //printf("Send data to server\n");

        //Do somesthing else
        sfSleep(sfSeconds(1));

        //printf("Receive data from server\n");
        check_inbox(&inbox);

    }
}

void* send_messages(void* Args)
{
    send_thread_args* args = Args;
    sfTcpSocket* socket = args->socket;
    sfPacket* packet = sfPacket_create();
    sfSocketStatus status;

    sfPacket_writeString(packet, "send message");

while (1)
{
    status = sfTcpSocket_sendPacket(socket, packet);

    sfSocketStatus_print(status);

    sfSleep(sfSeconds(1));
}
    return NULL;
}

void* receive_messages(void* Args)
{
    receive_thread_args* args = Args;
    sfTcpSocket* socket = args->socket;
    sfPacket* packet = sfPacket_create();
    sfSocketStatus status;

    while (1)
    {
        status = sfTcpSocket_receivePacket(socket, packet);

        if (status != sfSocketDone) continue;

        char message[512];
        sfPacket_readString(packet, message);

        printf("Received: %s\n", message);

        sfPacket_clear(packet);

    }

    sfSleep(sfSeconds(1));
    return NULL;
}

bbFlag check_inbox(bbThreadedQueue* queue)
{
    return None;
}