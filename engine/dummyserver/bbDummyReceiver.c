#include "engine/dummyserver/bbDummyReceiver.h"

bbFlag bbDummyReceiver_receive(bbDummySender* server, U64 gameTime )
{
    bbDummySender_listElement* listElement;
    bbDummySender_msg* message;

    while (1) {
        bbFlag flag = bbList_peakL(&server->message_queue, (void**)&listElement);
        if (flag == None) break;
        message = &listElement->msg;
        if (message->header.timestamp > gameTime ) break;

        if (message->header.type == bbDummySenderMsgType_sendMsg){
            bbDummyReceiver_textMessage(message);
        }

        if (message->header.type == bbDummySenderMsgType_activateSpell)
        {

        }
        bbList_popL(&server->message_queue, (void**)&listElement);
        bbVPool_free(server->message_queue.pool, listElement);


    }

    return Success;
}


bbFlag bbDummyReceiver_textMessage(bbDummySender_msg* message) {

    bbPool_Handle handle;
    handle.u64 = '\n';
    bbWidget_onCommand(home.private.widgets.dialog, &home.private.widgets,
                       bbWC_putChar, handle);
    handle.ptr = message->string.string;
    bbWidget_onCommand(home.private.widgets.dialog, &home.private.widgets,
                       bbWC_putStr, handle);

    return Success;
}
//notify the server that the spell has been activated
bbFlag bbDummyReceiver_setActiveSpell(bbDummySender_msg* message)
{
    bbDebug("Spell Activated\n");
    home.private.widgets.currentSpell->frames[0].handle
            = message->handle.handle;
    return Success;
}
bbFlag bbDummyReceiver_castSpell(bbDummySender_msg* message)
{
    return Success;
}