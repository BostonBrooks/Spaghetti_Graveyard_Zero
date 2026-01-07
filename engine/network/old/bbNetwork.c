#include "engine/network/bbNetwork.h"

#include "engine/logic/bbTerminal.h"

bbFlag bbNetwork_init(bbNetwork* network, sfIpAddress address, I32 port,
    bbNetwork_ProcessPacket* process_packet, bbNetworkPacketToStruct* packet_to_struct,bbNetwork_StructToPacket* struct_to_packet)
{
    const I32 connect_timeout = 60;
    const I32 queue_length = 100;
    network->address = address;
    network->port = port;
    network->process_packet = process_packet;
    network->struct_to_packet = struct_to_packet;
    network->packet_to_struct = packet_to_struct;
    network->quit = false;

    sfSocketStatus status;
    sfTcpSocket* socket = sfTcpSocket_create();
    bbAssert(socket!=NULL, "bad socket constructor\n");
    status = sfTcpSocket_connect(socket, address, port, sfSeconds(connect_timeout));
    if (status != sfSocketDone)
    {
        sfTcpSocket_destroy(socket);
        return None;
    }
    sfTcpSocket_setBlocking(socket, sfFalse);
    network->socket = socket;

    bbThreadedQueue_init(&network->inbox,NULL,sizeof(bbNetworkPacket),queue_length,offsetof(bbNetworkPacket, listElement));
    bbThreadedQueue_init(&network->outbox,NULL,sizeof(bbNetworkPacket),queue_length,offsetof(bbNetworkPacket, listElement));

    pthread_create(&network->send_thread,NULL, bbNetwork_sendThread, network);
    pthread_create(&network->receive_thread,NULL, bbNetwork_receiveThread, network);

    return Success;
}

bbFlag bbNetwork_destroy(bbNetwork* network)
{
    network->quit = true;
    pthread_join(network->send_thread, NULL);
    pthread_join(network->send_thread, NULL);
    sfTcpSocket_destroy(network->socket);

    return Success;
}


void* bbNetwork_receiveThread(void* args){
    bbNetwork* network = args;
    bbThreadedQueue* queue = &network->inbox;
    sfTcpSocket* socket = network->socket;
    sfPacket* packet = sfPacket_create();
    sfSocketStatus status;
    I32 i = 0;
    while (1)
    {
        if (network->quit) return 0;
        status = sfTcpSocket_receivePacket(socket, packet);

        if (status != sfSocketDone) continue;

        char message[512];
        //TODO Convert network packet to struct
        bbNetworkPacket* test;
        bbThreadedQueue_alloc(queue, (void**)&test);
        bbNetworkPacket_toStruct(packet, test);

        bbThreadedQueue_pushL(queue, test);

        sfPacket_clear(packet);
        i++;
    }

    sfSleep(sfSeconds(1));
    return NULL;
}

/// TODO Take struct from queue, Convert struct to packet, send
void* bbNetwork_sendThread(void* args)
{
    I32 i = 0;
    bbNetwork* network = args;
    sfTcpSocket* socket = network->socket;
    sfPacket* packet = sfPacket_create();
    sfSocketStatus status;

    char message[512];
    while (1)
    {
        if (network->quit) return 0;

        //TODO Convert network struct to packet
        bbNetworkPacket test;
        test.type = PACKETTYPE_STRING;
        sprintf(test.data.str, "i= %d", i);
        bbNetwork_struct_toPacket(packet, &test);
        status = sfTcpSocket_sendPacket(socket, packet);

        sfPacket_clear(packet);
        //sfSocketStatus_print(status);

        sfSleep(sfSeconds(0.1));

        i++;
    }
    return NULL;

}

bbFlag bbNetwork_checkInbox(bbNetwork* network)
{
    bbThreadedQueue* queue = &network->inbox;
    bbFlag flag = Success;

        //check queue
        while (flag == Success)
        {
            bbNetworkPacket* test;
            flag = bbThreadedQueue_popR(queue, (void**)&test);
            if (flag != Success) break;
            // call network->processPacket
            printf("Processed: %s\n", test->data.str);
            bbThreadedQueue_free(queue, (void**)&test);

        }

    return 0;
}