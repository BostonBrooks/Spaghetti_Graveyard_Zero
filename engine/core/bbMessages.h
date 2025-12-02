/** bbMessages simulates a web server by adding lag and then returning the
 * message */

#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbList.h"

typedef enum {
    bbSentMessage_txt
} bbSentMessage_type;

typedef union {
    char txt[64];
} bbSentMessage_data;

typedef struct {

    U64 time_sent;
    U64 time_enacted;
    bbPool_ListElement listElement;
    bbSentMessage_data data;
} bbSendMessage;

typedef enum {
    bbReceivedMessage_txt
} bbReceivedMessage_type;


typedef union {
    char txt[64];
} bbReceivedMessage_data;


typedef struct {
    U64 time_sent;
    U64 time_enacted;
    bbPool_ListElement listElement;
    bbReceivedMessage_data data;
} bbReceiveMessage;

typedef struct {
    bbVPool sentMessages_pool;
    bbList sentMessages_list;
    bbVPool receivedMessages_pool;
    bbVPool receivedMessages_list;
} bbMessages;

//1) Initialise system
bbFlag bbMessages_new(bbMessages** messages);
//2) Allocate an empty message
bbFlag bbMessage_new(bbSendMessage** self, bbMessages* messages);
//3) Pass message to system
bbFlag bbMessage_send(bbSendMessage* self, bbMessages* messages);
//4) Move messages from sent to received
bbFlag bbMessages_send(bbMessages* messages);
//5) React to messages received
bbFlag bbMessages_receive(bbMessages* messages);


