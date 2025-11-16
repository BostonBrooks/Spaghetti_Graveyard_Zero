#include "engine/dumbserver/bbDumbServer.h"

#include <string.h>

#include "engine/logic/bbFlag.h"


bbFlag bbDumbServer_new(bbDumbServer** server)
{

    bbDumbServer* dumbServer = (bbDumbServer *)malloc(sizeof(bbDumbServer));
    bbAssert(dumbServer != NULL, "bad malloc\n");
    bbVPool* pool;
    bbVPool_newBloated(&pool, sizeof(bbDumbServer_msg), 128, 128);
    bbList_init(&dumbServer->message_queue, pool,NULL, offsetof(bbDumbServer_listElement, listElement), NULL);

    *server = dumbServer;
    return Success;


}

bbFlag bbDumbServer_queueMsg(bbDumbServer* server, bbDumbServer_msg* message, U64 gameTime )
{
    const int lag = 5;
    message->header.timestamp = gameTime + lag;
    bbDumbServer_listElement* listElement;
    bbVPool* pool = server->message_queue.pool;
    bbVPool_alloc(pool, (void**)&listElement);
    memcpy(listElement->msg.string.string, message, sizeof(bbDumbServer_msg));
    bbList_pushR(&server->message_queue, listElement);

    return Success;
}


bbFlag bbDumbServer_react(bbDumbServer* server, U64 gameTime )
{
    bbDumbServer_listElement* listElement;
    bbDumbServer_msg* message;

    while (1) {
        bbFlag flag = bbList_peakL(&server->message_queue, (void**)&listElement);
        if (flag == None) break;
        message = &listElement->msg;
        if (message->header.timestamp > gameTime ) break;

        if (message->header.type == bbDumbServerMsgType_sendMsg){
            bbPrintf("Message Received: %s", message->string.string);
        }
        bbList_popL(&server->message_queue, (void**)&listElement);
        bbVPool_free(server->message_queue.pool, listElement);
    }

    return Success;
}


bbFlag bbDumbServer_netSend(bbDumbServer* server, char* string, U64 gameTime)
{
    const int lag = 5;

    bbDumbServer_listElement* listElement;
    bbVPool* pool = server->message_queue.pool;
    bbVPool_alloc(pool, (void**)&listElement);
    listElement->msg.header.type = bbDumbServerMsgType_sendMsg;
    listElement->msg.header.timestamp = gameTime + lag;
    bbStr_setStr(listElement->msg.string.string, string, 64);

    bbList_pushR(&server->message_queue, listElement);
    return Success;
}

