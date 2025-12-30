#include "engine/network/bbNetworkTime.h"

#include "bbNetwork.h"
#include "engine/threadsafe/bbThreadedPool.h"
#include "engine/threadsafe/bbThreadedQueue.h"

bbFlag bbNetworkTime_init(bbNetworkTime* network_time)
{
    network_time->localClock = sfClock_create();
    network_time->packets_sent = 0;
    bbVPool_newLean(&network_time->pool, sizeof(bbNetwork_record), 200);
    bbList_init(&network_time->pending,network_time->pool,NULL,offsetof(bbNetwork_record,list_element),NULL);
    bbList_init(&network_time->recorded,network_time->pool,NULL,offsetof(bbNetwork_record,list_element),NULL);
    return Success;
}

