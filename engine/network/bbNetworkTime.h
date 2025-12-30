
#include <SFML/System.h>

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
    //remember last 16 sent timestamps
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
bbFlag bbNetworkTimeStamp_request(bbNetworkTime* network_time, bbNetwork_timestamp* timestamp);

//consume timestamp immediately after receiving packet
bbFlag bbNetworkTimeStamp_consume(bbNetworkTime* network_time, bbNetwork_timestamp* timestamp);

/* What am I doing?
 * client sends packet N and notes local send time
 *                                                  Server receives packet N. notes server receiveTime
 *                                                  Server  notes server sendTime, responds to packet N,
 * client receives packet N and notes local receive time
 *
 * RTT = local receive time - local send time - (server receive time - server send time)
 *
 * server time at the time the message is received = sendTime - RTT/2
 * calculate difference in clocks to give client/server time difference.
 *
 */