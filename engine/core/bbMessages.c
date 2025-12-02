#include "engine/core/bbMessages.h"
#include "engine/logic/bbString.h"
#include "engine/logic/bbTerminal.h"

bbFlag bbMessages_new(bbMessages** Messages){
    bbMessages* messages = malloc(sizeof(bbMessages));


    bbVPool_newBloated(&messages->sendMessages_pool, sizeof
            (bbSendMessage), 1000,1000);
    bbList_init(&messages->sendMessages_list,
                messages->sendMessages_pool,
                NULL,
                offsetof(bbSendMessage, listElement),
                NULL);
    
    bbVPool_newBloated(&messages->receiveMessages_pool, sizeof
    (bbReceiveMessage), 1000,1000);
    bbList_init(&messages->receiveMessages_list,
                messages->receiveMessages_pool,
                NULL,
                offsetof(bbReceiveMessage, listElement),
                NULL);
    *Messages = messages;
    return Success;
}

bbFlag bbMessage_new(bbSendMessage** self, bbMessages* messages){
    bbSendMessage* message;
    bbVPool_alloc(messages->sendMessages_pool, (void**)&message);
    *self = message;
    return Success;
}

bbFlag bbMessage_send(bbSendMessage* self, bbMessages* messages){
    bbList_pushR(&messages->sendMessages_list, self);
    return Success;
}

bbFlag bbMessages_send(bbMessages* messages, U64 time){
    bbSendMessage* send;
    while (bbList_popL(&messages->sendMessages_list, &send) == Success)
    {
        switch (send->type) {
            case bbSentMessage_txt: {
                bbReceiveMessage *receive;
                bbVPool_alloc(messages->receiveMessages_pool,
                              (void **) &receive);

                receive->time_sent = send->time_sent;
                receive->type = bbReceiveMessage_txt;
                bbStr_setStr(receive->data.txt, send->data.txt, 64);
                bbList_pushR(&messages->receiveMessages_list,receive);
            }

        }
    }
    return Success;
}

bbFlag bbMessages_receive(bbMessages* messages, U64 time){
    bbReceiveMessage* receive;
    while (bbList_popL(&messages->receiveMessages_list, (void**)&receive) ==
    Success)
    {
        switch (receive->type) {
            case bbReceiveMessage_txt: {
                bbDebug("time_sent = %llu, message = %s\n",
                        receive->time_sent, receive->data.txt);
                bbVPool_free(messages->receiveMessages_pool, receive);

            }

        }
    }

    return Success;
}