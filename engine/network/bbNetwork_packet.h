#ifndef BB_NETWORK_PACKET_H
#define BB_NETWORK_PACKET_H

#include <SFML/Network.h>

#include "bbNetworkTime.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbPoolHandle.h"
#include "engine/network/bbNetworkTime.h"

#define PACKETTYPE_STRING            0
#define PACKETTYPE_TIMESTAMP         1
#define PACKETTYPE_REQUESTTIMESTAMP  2


typedef union
{
    bbNetwork_timestamp timestamp;
    char str[64];
} bbNetwork_packet_data;



typedef struct
{
    I32 type;
    bbNetwork_packet_data data;
    bbPool_ListElement listElement;

} bbNetwork_packet;


bbFlag bbNetwork_packet_toStruct (sfPacket* packet, bbNetwork_packet* Struct);
bbFlag bbNetwork_struct_toPacket (sfPacket* packet, bbNetwork_packet* Struct);

//depends on above functions, so not included in bbNetwork.c, which is meant to be more generic
bbFlag bbNetwork_sendStr(void* Network, char* str);


bbFlag bbNetwork_requestTimestamp(void* Network);

#endif //BB_NETWORK_PACKET_H