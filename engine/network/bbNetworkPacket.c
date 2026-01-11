#include "engine/network/bbNetworkPacket.h"

#include "bbNetwork.h"
#include "engine/logic/bbString.h"
#include "engine/logic/bbTerminal.h"


extern _Thread_local char* thread;

bbFlag bbNetworkPacket_toStruct (sfPacket* packet, void* Struct)
{
    bbNetworkPacket* struct1 = Struct;
    struct1->type = sfPacket_readInt32(packet);

    switch (struct1->type)
    {
        case PACKETTYPE_STRING:
            sfPacket_readString(packet, struct1->data.str);
        break;
        case PACKETTYPE_TIMESTAMP:
        case PACKETTYPE_REQUESTTIMESTAMP:

            U64 packetN_lower = sfPacket_readUint32(packet);
            U64 packetN_upper = sfPacket_readUint32(packet);
            U64 receive_time_lower = sfPacket_readUint32(packet);
            U64 receive_time_upper = sfPacket_readUint32(packet);
            U64 send_time_lower = sfPacket_readUint32(packet);
            U64 send_time_upper = sfPacket_readUint32(packet);



            struct1->data.timestamp.packetN = packetN_upper * 0x100000000 + packetN_lower;
            struct1->data.timestamp.receive_time = receive_time_upper * 0x100000000  + receive_time_lower;
            struct1->data.timestamp.send_time = send_time_upper * 0x100000000 + send_time_lower;

        break;
    }
    return Success;
}
bbFlag bbNetworkPacket_fromStruct (sfPacket* packet, void* Struct)
{
    bbNetworkPacket* struct1 = Struct;
    switch (struct1->type)
    {
    case PACKETTYPE_STRING:
        sfPacket_writeInt32(packet, struct1->type);
        sfPacket_writeString(packet, struct1->data.str);
        break;
    case PACKETTYPE_TIMESTAMP:
    case PACKETTYPE_REQUESTTIMESTAMP:
        sfPacket_writeInt32(packet, struct1->type);

        U64 packetN_lower = struct1->data.timestamp.packetN & 0xFFFFFFFF;
        U64 packetN_upper = struct1->data.timestamp.packetN / 0x100000000;
        U64 receive_time_lower = struct1->data.timestamp.receive_time & 0xFFFFFFFF;
        U64 receive_time_upper = struct1->data.timestamp.receive_time / 0x100000000;
        U64 send_time_lower = struct1->data.timestamp.send_time & 0xFFFFFFFF;
        U64 send_time_upper = struct1->data.timestamp.send_time / 0x100000000;



        sfPacket_writeUint32(packet, (U32)packetN_lower);
        sfPacket_writeUint32(packet, (U32)packetN_upper);
        sfPacket_writeUint32(packet, (U32)receive_time_lower);
        sfPacket_writeUint32(packet, (U32)receive_time_upper);
        sfPacket_writeUint32(packet, (U32)send_time_lower);
        sfPacket_writeUint32(packet, (U32)send_time_upper);
        break;
    }
    return Success;
}


bbFlag bbNetwork_sendStr(void* Network, char* str)
{
    bbNetwork* network = (bbNetwork*)Network;
    bbNetworkPacket* packet;
    bbThreadedQueue_alloc(&network->outbox, (void**)&packet);
    packet->type = PACKETTYPE_STRING;
    bbStr_setStr(packet->data.str, str, 64);
    bbThreadedQueue_pushL(&network->outbox, (void*)packet);

    return Success;
}


