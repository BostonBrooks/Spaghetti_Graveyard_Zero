#ifndef BB_NETWORK_PACKET_H
#define BB_NETWORK_PACKET_H

#include "engine/logic/bbFlag.h"
#include "engine/logic/bbPoolHandle.h"

typedef struct
{

    char data[64];
    bbPool_ListElement listElement;

} bbNetwork_packet;


bbFlag bbNetwork_packet_toStruct (sfPacket* packet, void* Struct);
bbFlag bbNetwork_struct_toPacket (void* Struct, sfPacket* packet);



#endif //BB_NETWORK_PACKET_H