#include "engine/network/bbNetwork_packet.h"

#include "bbNetwork.h"
#include "engine/logic/bbString.h"
#include "engine/logic/bbTerminal.h"


extern _Thread_local char* thread;

bbFlag bbNetwork_packet_toStruct (sfPacket* packet, bbNetwork_packet* Struct)
{

    Struct->type = sfPacket_readInt32(packet);

    switch (Struct->type)
    {
        case PACKETTYPE_STRING:
            sfPacket_readString(packet, Struct->data.str);
        break;
        case PACKETTYPE_TIMESTAMP:

            U64 packetN_lower = sfPacket_readUint32(packet);
            U64 packetN_upper = sfPacket_readUint32(packet);
            U64 receive_time_lower = sfPacket_readUint32(packet);
            U64 receive_time_upper = sfPacket_readUint32(packet);
            U64 send_time_lower = sfPacket_readUint32(packet);
            U64 send_time_upper = sfPacket_readUint32(packet);

            Struct->data.timestamp.packetN = packetN_upper * 0x100000000 + packetN_lower;
            Struct->data.timestamp.receive_time = receive_time_upper * 0x100000000  + receive_time_lower;
            Struct->data.timestamp.send_time = send_time_upper * 0x100000000 + send_time_lower;

    case PACKETTYPE_REQUESTTIMESTAMP:
        break;
    }
    return Success;
}
bbFlag bbNetwork_struct_toPacket (sfPacket* packet, bbNetwork_packet* Struct)
{
    switch (Struct->type)
    {
    case PACKETTYPE_STRING:
        sfPacket_writeInt32(packet, Struct->type);
        sfPacket_writeString(packet, Struct->data.str);
        break;
    case PACKETTYPE_TIMESTAMP:
        sfPacket_writeInt32(packet, Struct->type);

        U64 packetN_lower = Struct->data.timestamp.packetN & 0xFFFFFFFF;
        U64 packetN_upper = Struct->data.timestamp.packetN / 0x100000000;
        U64 receive_time_lower = Struct->data.timestamp.receive_time & 0xFFFFFFFF;
        U64 receive_time_upper = Struct->data.timestamp.receive_time / 0x100000000;
        U64 send_time_lower = Struct->data.timestamp.send_time & 0xFFFFFFFF;
        U64 send_time_upper = Struct->data.timestamp.send_time / 0x100000000;

        sfPacket_writeUint32(packet, (U32)packetN_lower);
        sfPacket_writeUint32(packet, (U32)packetN_upper);
        sfPacket_writeUint32(packet, (U32)receive_time_lower);
        sfPacket_writeUint32(packet, (U32)receive_time_upper);
        sfPacket_writeUint32(packet, (U32)send_time_lower);
        sfPacket_writeUint32(packet, (U32)send_time_upper);
        break;
    case PACKETTYPE_REQUESTTIMESTAMP:
        sfPacket_writeInt32(packet, Struct->type);
        break;
    }
    return Success;
}


bbFlag bbNetwork_sendStr(void* Network, char* str)
{
    bbNetwork* network = (bbNetwork*)Network;
    bbNetwork_packet* packet;
    bbThreadedQueue_alloc(&network->outbox, (void**)&packet);
    packet->type = PACKETTYPE_STRING;
    bbStr_setStr(packet->data.str, str, 64);

    bbThreadedQueue_pushL(&network->outbox, (void*)packet);

    return Success;
}


bbFlag bbNetwork_requestTimestamp(void* Network)
{
    bbNetwork* network = (bbNetwork*)Network;
    bbNetwork_packet* packet;
    bbThreadedQueue_alloc(&network->outbox, (void**)&packet);
    packet->type = PACKETTYPE_REQUESTTIMESTAMP;

    bbThreadedQueue_pushL(&network->outbox, (void*)packet);

    return Success;
}