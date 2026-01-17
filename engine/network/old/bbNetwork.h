//Translated into a module from bbNetwork_test.c, which is somewhat ad-hoc
#ifndef BB_NETWORK_H
#define BB_NETWORK_H

#include <pthread.h>
#include <stdatomic.h>

#include "engine/includes/CSFML.h"

#include "engine/network/bbNetworkPacket.h"
#include "engine/threadsafe/bbThreadedQueue.h"




//Defined outside
typedef bbFlag bbNetwork_ProcessPacket (void* network, void* args);
typedef bbFlag bbNetworkPacketToStruct (sfPacket* packet, void* Struct);
typedef bbFlag bbNetwork_StructToPacket (void* Struct, sfPacket* packet);


typedef struct
{
    sfIpAddress address;
    I32 port;
    sfTcpSocket* socket;

    //receive packets over network and add to inbox
    pthread_t receive_thread;
    bbThreadedQueue inbox;

    //take packets from outbox and send over network
    pthread_t send_thread;
    bbThreadedQueue outbox;

    // behavior is defined outside this module
    bbNetwork_ProcessPacket* process_packet;
    bbNetworkPacketToStruct* packet_to_struct;
    bbNetwork_StructToPacket* struct_to_packet;

    atomic_bool quit;
} bbNetwork;

bbFlag bbNetwork_init(bbNetwork* network, sfIpAddress address, I32 port,
    bbNetwork_ProcessPacket* process_packet, bbNetworkPacketToStruct* packet_to_struct,bbNetwork_StructToPacket* struct_to_packet);
bbFlag bbNetwork_destroy(bbNetwork* network);
void* bbNetwork_receiveThread(void* args);
void* bbNetwork_sendThread(void* args);
bbFlag bbNetwork_checkInbox(bbNetwork* network);
bbFlag bbNetworkPacketToStruct(bbNetwork network, sfPacket* packet, void* Struct);
bbFlag bbNetwork_structToPacket(bbNetwork network, sfPacket* packet, void* Struct);

#endif //BB_NETWORK_H