#include "engine/network/bbNetworkPacket.h"

#include <stdio.h>


int main(void)
{
    bbNetworkPacket bb_packet;
    bb_packet.type = PACKETTYPE_TIMESTAMP;
    bb_packet.data.timestamp.packetN = 123456789012ULL;
    bb_packet.data.timestamp.receive_time = 345678901234ULL;
    bb_packet.data.timestamp.send_time = 567890123456ULL;

    sfPacket* sf_packet = sfPacket_create();
    bbNetworkPacket_fromStruct(sf_packet, &bb_packet);
    bbNetworkPacket bb_packet2;
    bbNetworkPacket_toStruct(sf_packet, &bb_packet2);

    printf("type = %d\npacketN = %llu\nreceive_time = %llu\nsend_time = %llu\n",
        bb_packet2.type, bb_packet2.data.timestamp.packetN, bb_packet2.data.timestamp.receive_time, bb_packet2.data.timestamp.send_time);

    return 0;
}
