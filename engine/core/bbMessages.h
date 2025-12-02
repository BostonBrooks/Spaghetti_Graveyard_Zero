/** bbMessages simulates a web server by adding lag and then returning the
 * message */

#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbList.h"

typedef enum {
    bbSentMessage_txt
} bbSendMessage_type;

typedef union {
    char txt[64];
} bbSendMessage_data;

typedef struct {
    bbPool_ListElement listElement;
    U64 time_sent;
    bbSendMessage_data data;
    bbSendMessage_type type;
} bbSendMessage;

typedef enum {
    bbReceiveMessage_txt
} bbReceiveMessage_type;


typedef union {
    char txt[64];
} bbReceiveMessage_data;


typedef struct {
    bbPool_ListElement listElement;
    U64 time_sent;
    bbReceiveMessage_data data;
    bbReceiveMessage_type type;
} bbReceiveMessage;

typedef struct {
    bbVPool *sendMessages_pool;
    bbList sendMessages_list;
    bbVPool *receiveMessages_pool;
    bbList receiveMessages_list;
} bbMessages;

//1) Initialise system
bbFlag bbMessages_new(bbMessages** messages);
//2) Allocate an empty message
bbFlag bbMessage_new(bbSendMessage** self, bbMessages* messages);
//3) Pass message to system
bbFlag bbMessage_send(bbSendMessage* self, bbMessages* messages);
//4) Move messages from sent to received
bbFlag bbMessages_send(bbMessages* messages, U64 time);
//5) React to messages received
bbFlag bbMessages_receive(bbMessages* messages, U64 time);


