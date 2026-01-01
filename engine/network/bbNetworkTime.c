#include "engine/network/bbNetworkTime.h"

#include "bbNetwork.h"
#include "engine/threadsafe/bbThreadedPool.h"
#include "engine/threadsafe/bbThreadedQueue.h"

bbFlag bbNetworkTime_init(bbNetworkTime* network_time)
{
    network_time->localClock = sfClock_create();
    network_time->packets_sent = 0;
    bbThreadedQueue_init(&network_time->pending, NULL, sizeof(bbNetworkTime_record),
    200, offsetof(bbNetworkTime_record, list_element));
    bbThreadedQueue_init(&network_time->pending,network_time->pending.pool, sizeof(bbNetworkTime_record),
        200, offsetof(bbNetworkTime_record, list_element));

    return Success;
}

/* //
bbFlag bbNetworkTime_filterOutbox (void* Network, bbNetwork_packet* Struct)
{
    bbNetwork* network = Network;
    bbNetworkTime* network_time = (bbNetworkTime*)network->extra_data;
    bbNetworkTime_record* record;
    bbThreadedQueue_alloc(network_time->pending,...)

    bbNetwork_packet* packet = Struct;

    if packet.type == PACKETTYPE_REQUESTTIMESTAMP{
    packet...packetN = network_time->packets_sent

    record->packetN = network_time->packets_sent;
    network_time->packets_sent++;
    record->local_send_time = sfTime_asMilliseconds(sfClock_getElapsedTime(network_time->localClock));

    //bbThreadedQueue_pushL record, network_time.pending
    }
    return Success;
}

//
bbFlag bbNetworkTime_filterInbox (void* Network, bbNetwork_packet* Struct)
{
    bbNetwork_packet* packet = Struct;
    bbNetwork* network = Network;
    bbNetworkTime* network_time = (bbNetworkTime*)network->extra_data;
    bbNetworkTime_record* record;

    search network_time->pending for record.packetN = packet...packetN

    fill out:
        packet.server_receive_time;
        packet.server_send_time;
        packet.local_receive_time;

    bbThreadedQueue_pushL record, network_time.completed
}
*/