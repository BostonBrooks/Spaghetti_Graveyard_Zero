///I'm starting things over, network connection must not block spawning thread

#include <stdatomic.h>
#include <SFML/Network.h>

#include "engine/threadsafe/bbThreadedQueue.h"


typedef bbFlag bbNetwork_ProcessPacket (void* network, void* args);
typedef bbFlag bbNetwork_PacketToStruct (sfPacket* packet, void* Struct);
typedef bbFlag bbNetwork_StructToPacket (void* Struct, sfPacket* packet);
typedef bbFlag bbNetwork_onConnect (void* network);
typedef bbFlag bbNetwork_onDisconnect (void* network);

typedef struct bbNetwork
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

    // behaviors are defined outside this module:

    bbNetwork_PacketToStruct* packet_to_struct;
    bbNetwork_StructToPacket* struct_to_packet;
    //notify front end
    bbNetwork_onConnect* on_connect;
    //notify front end
    bbNetwork_onDisconnect* on_disconnect;

//if true,
    atomic_bool quit;

    //Does the server belong to this computer?
    bool isLocal;
} bbNetwork;


///create a new network object
bbFlag bbNetwork_new(bbNetwork** network,
    bbNetwork_ProcessPacket* process_packet,
    bbNetwork_PacketToStruct* packet_to_struct,
    bbNetwork_StructToPacket* struct_to_packet,
    bbNetwork_onConnect* on_connect,
    bbNetwork_onDisconnect* on_disconnect);

///Asynchronously try to connect to a server, if successful, call bbNetwork_onConnect, otherwise call bbNetwork_onDisconnect
///Launch bbNetwork_receiveThread
///Then wait on outbox to send packets
bbFlag bbNetwork_connect(bbNetwork* network, sfIpAddress address, I32 port);

///called by bbNetwork_connect to asynchronously connect
void* bbNetwork_spawn(void* args);
///call bbNetwork_onDisconnect and end connection
bbFlag bbNetwork_disconnect(bbNetwork* network);

//one of the following is spawned as a new thread, and the other is called like a normal function
/// this thread waits on inbox and sends packets over network
void* bbNetwork_sendThread(void* args);

/// this thread waits for incoming packets then outputs to inbox
void* bbNetwork_receiveThread(void* args);

//Functions to send to outbox or receive to inbox are called by main