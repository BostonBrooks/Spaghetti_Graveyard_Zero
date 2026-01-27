#include "engine/network/bbNetworkClock.h"

#include "engine/logic/bbBloatedPool.h"

I32 sortByTimeDifference(void* a, void* b)
{
    bbNetworkClock_maths* A = a;
    bbNetworkClock_maths* B = b;
    return (A->time_difference > B->time_difference);
}


void* bbNetwork_clockThread(void* Network_clock)
{
    bbNetworkClock* network_clock = (bbNetworkClock*) Network_clock;
    bbNetworkClock_pingRecord* ping_record;
    while (1)
    {
        bbThreadedQueue_popRblock(&network_clock->pending_pingRecords,(void**)&ping_record);
        bbDebug("Round trip time = %lu, time_difference = %ld\n",
            ping_record->round_trip_time,
            ping_record->time_difference);
    }
}

bbFlag bbNetworkClock_init(bbNetworkClock* network_clock, bbNetworkTime* network_time)
{
    network_clock->network_time = network_time;
    network_time->networkClock = network_clock;

    network_clock->server_tick_time = 0;

    bbThreadedQueue_init(&network_clock->pending_pingRecords,
        NULL,
        sizeof(bbNetworkClock_pingRecord),
        32,
        offsetof(bbNetworkClock_pingRecord, list_element));

    bbVPool_newBloated(&network_clock->maths_pool,sizeof(bbNetworkClock_maths),100,100);

    bbList_init(&network_clock->maths_list_chronological,
                network_clock->maths_pool,
                NULL,
                offsetof(bbNetworkClock_maths,chronological),
                NULL);

    bbList_init(&network_clock->maths_list_sorted,
            network_clock->maths_pool,
            NULL,
            offsetof(bbNetworkClock_maths,sorted),
            sortByTimeDifference);

    network_clock->maths_list_length = 0;
    network_clock->time_difference = 0;
    network_clock->time_calibrated = false;

    pthread_create(&network_clock->clock_thread,NULL, bbNetwork_clockThread, network_clock);

    return Success;
}