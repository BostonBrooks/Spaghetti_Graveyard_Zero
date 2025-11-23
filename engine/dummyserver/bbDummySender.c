#include "engine/dummyserver/bbDummySender.h"

#include <string.h>

#include "engine/logic/bbFlag.h"


bbFlag bbDummySender_new(bbDummySender** server)
{

    bbDummySender* dumbServer = (bbDummySender *)malloc(sizeof(bbDummySender));
    bbAssert(dumbServer != NULL, "bad malloc\n");
    bbVPool* pool;
    bbVPool_newBloated(&pool, sizeof(bbDummySender_msg), 128, 128);
    bbList_init(&dumbServer->message_queue, pool,NULL, offsetof(bbDummySender_listElement, listElement), NULL);

    *server = dumbServer;
    return Success;


}

bbFlag bbDummySender_queueMsg(bbDummySender* server, bbDummySender_msg* message, U64 gameTime )
{
    const int lag = 5;
    message->header.timestamp = gameTime + lag;
    bbDummySender_listElement* listElement;
    bbVPool* pool = server->message_queue.pool;
    bbVPool_alloc(pool, (void**)&listElement);
    memcpy(listElement->msg.string.string, message, sizeof(bbDummySender_msg));
    bbList_pushR(&server->message_queue, listElement);

    return Success;
}


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


bbFlag bbDummySender_netSend(bbDummySender* server, char* string, U64 gameTime)
{
    const int lag = 5;

    bbDummySender_listElement* listElement;
    bbVPool* pool = server->message_queue.pool;
    bbVPool_alloc(pool, (void**)&listElement);
    listElement->listElement.next = pool->null;
    listElement->listElement.prev = pool->null;

    listElement->msg.header.type = bbDummySenderMsgType_sendMsg;
    listElement->msg.header.timestamp = gameTime + lag;
    bbStr_setStr(listElement->msg.string.string, string, 64);

    bbList_pushR(&server->message_queue, listElement);
    return Success;
}

bbFlag bbDummySender_setActiveSpell(bbDummySender* server, bbPool_Handle spell, U64 gameTime)
{
    const int lag = 5;

    bbDummySender_listElement* listElement;

    //TODO roll the following 4 lines into one function call
    bbVPool* pool = server->message_queue.pool;
    bbVPool_alloc(pool, (void**)&listElement);
    listElement->listElement.next = pool->null;
    listElement->listElement.prev = pool->null;


    listElement->msg.header.type = bbDummySenderMsgType_activateSpell;
    listElement->msg.header.timestamp = gameTime + lag;
    listElement->msg.handle.handle = spell;

    bbList_pushR(&server->message_queue, listElement);
    return Success;
}


bbFlag bbDummySender_castSpell(bbDummySender* server, bbMapCoords MC, U64 gameTime)
{
    //TODO
    return Success;
}