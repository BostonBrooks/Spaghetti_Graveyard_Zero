/** bbMessages simulates a web server by adding lag and then returning the
 * message */
#ifndef BBMESSAGES_H
#define BBMESSAGES_H

#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbList.h"
#include "engine/core/bbCore.h"

#include "engine/data/bbHome.h"

typedef enum {
    bbSentMessage_txt,
    bbSentMessage_bbCoreDo
} bbSendMessage_type;

typedef union {
    char txt[64];
    //bbRedoData redo;
} bbSendMessage_data;

typedef struct {
    bbPool_ListElement listElement;
    U64 sendTime;
    bbSendMessage_data data;
    bbSendMessage_type type;
} bbSendMessage;

typedef enum {
    bbReceiveMessage_txt,
    bbReceiveMessage_bbCoreDo
} bbReceiveMessage_type;


typedef union {
    char txt[64];
} bbReceiveMessage_data;


typedef struct {
    bbPool_ListElement listElement;
    U64 receiveTime;
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
bbFlag bbMessage_send(bbSendMessage* self, bbMessages* messages, U64 time);
//4) Move messages from sent to received
bbFlag bbMessages_send(bbMessages* messages, U64 time);
//5) React to messages received
bbFlag bbMessages_receive(bbMessages* messages, U64 time);

#endif //BBMESSAGES_H
