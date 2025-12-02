#include "engine/core/bbMessages.h"
#include "engine/logic/bbString.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbList.h"


#define MESSAGE_LAG 10;

I32 bbReceiveMessage_isSooner(void* one, void* two){
    bbReceiveMessage* message1 = one;
    bbReceiveMessage* message2 = two;

    return message1->receiveTime < message2->receiveTime;
}

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
                bbReceiveMessage_isSooner);
    *Messages = messages;
    return Success;
}

bbFlag bbMessage_new(bbSendMessage** self, bbMessages* messages){
    bbSendMessage* message;
    bbVPool_alloc(messages->sendMessages_pool, (void**)&message);
    *self = message;
    return Success;
}

bbFlag bbMessage_send(bbSendMessage* self, bbMessages* messages, U64 time){
    self->sendTime = time;
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

                receive->receiveTime = send->sendTime + rand()%MESSAGE_LAG;
                receive->type = bbReceiveMessage_txt;
                bbStr_setStr(receive->data.txt, send->data.txt, 64);
                bbList_sortR(&messages->receiveMessages_list,receive);
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
        if (receive->receiveTime > time) {
            bbList_pushL(&messages->receiveMessages_list, receive);
            break;
        };
        switch (receive->type) {
            case bbReceiveMessage_txt: {
                bbPrintf("receiveTime = %llu, %s\n",
                        receive->receiveTime, receive->data.txt);
                bbVPool_free(messages->receiveMessages_pool, receive);

            }

        }
    }

    return Success;
}