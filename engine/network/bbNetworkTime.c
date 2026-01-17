#include "engine/network/bbNetworkTime.h"

#include "engine/network/bbNetwork.h"
#include "engine/logic/bbTerminal.h"
#include "engine/threadsafe/bbThreadedPool.h"
#include "engine/threadsafe/bbThreadedQueue.h"
#include "engine/threadsafe/bbTheadedQueue_search.h"

bbFlag bbNetworkTime_init(bbNetworkTime* network_time)
{
    I32 queue_size = 5;
    network_time->localClock = sfClock_create();
    network_time->packets_sent = 0;
    bbThreadedQueue_init(&network_time->pending, NULL, sizeof(bbNetworkTime_record),
    queue_size, offsetof(bbNetworkTime_record, list_element));
    bbThreadedQueue_init(&network_time->completed,network_time->pending.pool, sizeof(bbNetworkTime_record),
        queue_size, offsetof(bbNetworkTime_record, list_element));

    return Success;
}


bbFlag bbNetworkTime_filterOutbox (void* Network, void* Struct)
{

        bbNetworkPacket* packet = Struct;
    if (packet->type == PACKETTYPE_REQUESTTIMESTAMP)
    {

        bbNetwork* network = Network;
        bbNetworkTime* network_time = (bbNetworkTime*)network->extra_data;
        bbNetworkTime_record* record;
        bbThreadedPool* pool = network_time->pending.pool->pool;
        bbThreadedQueue_alloc(&network_time->pending, (void**)&record);
        packet->data.timestamp.packetN = network_time->packets_sent;
        record->packetN = network_time->packets_sent;

        network_time->packets_sent++;
        record->local_send_time = sfTime_asMicroseconds(sfClock_getElapsedTime(network_time->localClock));
        bbThreadedQueue_pushL(&network_time->pending,record);
        return Success;
    }

    return Success;
}

bbFlag packetN_equals(void* Callback, bbPool_Handle handle)
{

    bbCallback* callback = (bbCallback*)Callback;
    I32 packet_n = callback->args.u64;
    bbNetworkTime_record* record = handle.ptr;

    if (record->packetN == packet_n) return Success;
    return None;
}

bbFlag bbNetworkTime_filterInbox (void* Network, void* Struct)
{

    bbNetwork* network = Network;
    bbNetworkTime* network_time = (bbNetworkTime*)network->extra_data;
    bbNetworkPacket* packet = Struct;
    if (packet->type == PACKETTYPE_TIMESTAMP)

        {
        bbCallback callback;
        callback.function = packetN_equals;
        callback.args.u64 = packet->data.timestamp.packetN;

        bbNetworkTime_record* record;

        bbFlag flag = bbThreadedQueue_search(&network_time->pending,  (void**)&record, &callback);

        if (flag == Success)
        {
            record->local_receive_time = sfTime_asMicroseconds(sfClock_getElapsedTime(network_time->localClock));
            record->server_receive_time = packet->data.timestamp.receive_time;
            record->server_send_time = packet->data.timestamp.send_time;

            //printf("packetN = %llu, local_send_time = %llu, server_receive_time = %llu, server_send_time = %llu, local_receive_time = %llu\n",
            //    record->packetN, record->local_send_time, record->server_receive_time, record->server_send_time, record->local_receive_time);


            bbThreadedQueue_pushL(&network_time->completed,record);
        }
        // "None" implies that the packet does not have to be placed in the network inbox
        return None;
    }

return Success;
}

///place a PACKETTYPE_REQUESTTIMESTAMP in outbox
bbFlag bbNetworkTime_ping(void* Network)
{
    bbNetwork* network = Network;
    bbNetworkPacket* packet;
    bbThreadedQueue_alloc(&network->outbox, (void**)&packet);

    packet->type = PACKETTYPE_REQUESTTIMESTAMP;

    bbThreadedQueue_pushL(&network->outbox,packet);

    return Success;
}

//TODO what time is it on the server?
bbFlag bbNetworkTime_get(bbNetworkTime* network_time, sfTime* time)
{
    *time = sfClock_getElapsedTime(network_time->localClock);
    return Success;
}