/** The dumb server is a placeholder for a real server in a client-server architecture.
 * The dumb server receives requests from the client, adds some lag,
 * and then echos those requests back to the client.
 * The client side of the dumb server must have access to a well defined subset of the client side data
 * things will get confusing when it comes time to merge input streams
 */

#ifndef DUMBSERVER_H
#define DUMBSERVER_H

#include "engine/widgets/bbWidget.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbList.h"

typedef enum
{
    bbDumbServerMsgType_sendMsg
} bbDumbServer_msgType;

typedef struct
{
    bbDumbServer_msgType type;
    U64 timestamp;
} bbDumbserver_msgHeader;
typedef struct
{
    bbDumbserver_msgHeader header;
    char string[64];

} bbDumbServer_msgString;

typedef union
{
    bbDumbserver_msgHeader header;
    bbDumbServer_msgString string;
} bbDumbServer_msg;

typedef struct
{
    bbList message_queue;
    bbWidgets* widgets;
} bbDumbServer;

typedef struct
{
    bbPool_ListElement listElement;
    bbDumbServer_msg msg;
} bbDumbServer_listElement;

bbFlag bbDumbServer_new(/*args*/);

//the second argument in the following is a union of structs beginning with bbDumbserver_msgHeader
bbFlag bbDumbServer_queueMsg(bbDumbServer* server, bbDumbServer_msg* message, U64 gameTime);


//react to messages as in the (Re)Actor pattern?
bbFlag bbDumbServer_react(bbDumbServer* server, U64 gameTime );

bbFlag bbDumbServer_netSend(bbDumbServer* server, char* string, U64 gameTime);
#endif