#ifndef BBNETWORKTIME_H
#define BBNETWORKTIME_H

#include <SFML/System.h>

#include "bbNetwork.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbList.h"
// send data used to calculate difference between clocks
typedef struct
{
    U64 packetN;
    U64 receive_time;
    U64 send_time;
} bbNetwork_timestamp;

typedef struct
{
    U64 packetN;
    U64 local_send_time;
    U64 server_receive_time;
    U64 server_send_time;
    U64 local_receive_time;
    U64 time_difference;
    bbPool_List list_element;
} bbNetwork_record;

// keep data to track difference between clocks
typedef struct
{
    sfClock* localClock;
    U64 packets_sent;

    bbVPool* pool;
    bbList pending;
    bbList recorded;


} bbNetworkTime;



// get in synch with server
bbFlag bbNetworkTime_init(bbNetworkTime* network_time);

// get the time since the server started
bbFlag bbNetworkTime_get(bbNetworkTime* network_time, sfTime time);

// get the number of ticks/frames since the server started
bbFlag bbNetworkTime_getInt(bbNetworkTime* network_time, U64 tick);

// wait until the start of tick N
bbFlag bbNetworkTime_waitInt(bbNetworkTime* network_time, U64 tick);

//create timestamp immediately before sending packet
bbFlag bbNetworkTimeStamp_request(bbNetwork* network, bbNetworkTime* network_time, bbNetwork_timestamp* timestamp);

///react immediately to incoming message
bbFlag bbNetworkTime_filterInbox (void* network, bbNetwork_packet* Struct);
///react to outgoing message immediately before sending
bbFlag bbNetworkTime_filterOutbox (void* network, bbNetwork_packet* Struct);

/* What am I doing?
 * bbNetwork.extra_data points to bbNetworkTime
 *
 * main thread puts a timestamp request in outbox
 *
 * filter_outbox creates a bbNetwork_record and records time,
 * then sends on the request to the server, filling out bbNetwork_timestamp.packetN
 *
 *                                                                         server adds receive time and send time
 *                                                                         sends the packet back to the client
 * filter_inbox adds server receive and send times, and current time to bbNetwork_record
 * bbdebug round trip time (RTT)
 *
 */

#endif //BBNETWORKTIME_H
