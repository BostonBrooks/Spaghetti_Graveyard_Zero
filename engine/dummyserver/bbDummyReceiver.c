#include "engine/dummyserver/bbDummyReceiver.h"

bbFlag bbDummySender_react(bbDummySender* server, U64 gameTime )
{
    bbDummySender_listElement* listElement;
    bbDummySender_msg* message;

    while (1) {
        bbFlag flag = bbList_peakL(&server->message_queue, (void**)&listElement);
        if (flag == None) break;
        message = &listElement->msg;
        if (message->header.timestamp > gameTime ) break;

        if (message->header.type == bbDummySenderMsgType_sendMsg){
            bbPrintf("Message Received: %s", message->string.string);
        }

        if (message->header.type == bbDummySenderMsgType_activateSpell)
        {
            bbDebug("Spell Activated\n");
            server->widgets->currentSpell->frames[0].handle
                    = message->handle.handle;
        }
        bbList_popL(&server->message_queue, (void**)&listElement);
        bbVPool_free(server->message_queue.pool, listElement);


    }

    return Success;
}