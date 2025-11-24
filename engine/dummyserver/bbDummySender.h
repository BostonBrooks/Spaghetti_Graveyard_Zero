/** The dumb server is a placeholder for a real server in a client-server architecture.
 * The dumb server receives requests from the client, adds some lag,
 * and then echos those requests back to the client.
 * The client side of the dumb server must have access to a well defined subset of the client side data
 * things will get confusing when it comes time to merge input streams
 */

#ifndef BBDUMMYSENDER_H
#define BBDUMMYSENDER_H

#include "engine/widgets/bbWidget.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbList.h"

typedef enum
{
    bbDummySenderMsgType_sendMsg,
    bbDummySenderMsgType_activateSpell,
    bbDummySenderMsgType_castSpell
} bbDummySender_msgType;

typedef struct
{
    bbDummySender_msgType type;
    U64 timestamp;
} bbDummySender_msgHeader;
typedef struct
{
    bbDummySender_msgHeader header;
    char string[64];

} bbDummySender_msgString;

typedef struct
{
    bbDummySender_msgHeader header;
    bbPool_Handle handle;
} bbDummySender_poolHandle;

typedef union
{
    bbDummySender_msgHeader header;
    bbDummySender_msgString string;
    bbDummySender_poolHandle handle;
} bbDummySender_msg;

typedef struct
{
    bbList message_queue;
    bbWidgets* widgets;
} bbDummySender;

typedef struct
{
    bbPool_ListElement listElement;
    bbDummySender_msg msg;
} bbDummySender_listElement;

bbFlag bbDummySender_new(/*args*/);

//the second argument in the following is a union of structs beginning with bbDummySender_msgHeader
bbFlag bbDummySender_queueMsg(bbDummySender* server, bbDummySender_msg* message, U64 gameTime);



bbFlag bbDummySender_textMessage(bbDummySender* server, char* string, U64 gameTime);
bbFlag bbDummySender_setActiveSpell(bbDummySender* server, bbPool_Handle spell, U64 gameTime);
bbFlag bbDummySender_castSpell(bbDummySender* server, bbMapCoords MC, U64 gameTime);

#endif //BBDUMMYSENDER_H