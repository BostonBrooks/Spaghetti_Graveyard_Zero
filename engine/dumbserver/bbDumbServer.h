/** The dumb server is a placeholder for a real server in a client-server architecture.
 * The dumb server receives requests from the client, adds some lag,
 * and then echos those requests back to the client.
 * The client side of the dumb server must have access to a well defined subset of the client side data
 */

#ifndef DUMBSERVER_H
#define DUMBSERVER_H

#include "engine/widgets/bbWidget.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"

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

typedef struct
{
    //store messages in a circular buffer. I don't know how big this should be...
    //bbCircularBuffer* buffer;
    bbWidgets* widgets;
} bbDumbServer;

bbFlag bbDumbServer_new(/*args*/);

//the second argument in the following is a union of structs beginning with bbDumbserver_msgHeader
bbFlag bbDumbServer_queueMsg(bbDumbServer* server, bbDumbserver_msgHeader* message );

//send queued messages to nonexistant server
bbFlag bbDumbServer_sendMsgs(/*args*/);

//receive messages from nonexistant server
bbFlag bbDumbServer_receiveMsgs(/*args*/);

//react to messages as in the (Re)Actor pattern?
bbFlag bbDumbServer_react(/*args*/);
#endif