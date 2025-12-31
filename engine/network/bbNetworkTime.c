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


bbFlag bbNetworkTime_filterInbox (void* Network, bbNetwork_packet* Struct)
{
    bbNetwork* network = Network;
    bbNetworkTime* network_time = (bbNetworkTime*)network->extra_data;
    bbNetworkTime_record* record;
    bbThreadedQueue_alloc(network_time->pending,...)

    record->packetN = network_time->packets_sent;
    network_time->packets_sent++;
    record->local_send_time = sfTime_asMilliseconds(sfClock_getElapsedTime(network_time->localClock));
    return Success;
}

bbFlag bbNetworkTime_filterOutbox (void* Network, bbNetwork_packet* Struct)
{
    bbNetwork* network = Network;
    bbNetworkTime* network_time = (bbNetworkTime*)network->extra_data;
    bbNetworkTime_record* record;
}