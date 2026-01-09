#include "engine/logic/bbTerminal.h"
#include "engine/core(old)/bbCore.h"
#include <string.h>

//wait time is introduced to make sure all messages are received before any
// are enacted upon

#define WAIT_TIME 10

I32 bbStateChange_isSooner(void* one, void* two){
    bbStateChange* message1 = one;
    bbStateChange* message2 = two;

    return message1->enactTime < message2->enactTime;
}

bbFlag bbCore_new(bbCore** self){
    bbCore* core = malloc(sizeof(bbCore));
    bbAssert(core != NULL, "malloc failed!\n");


    bbList_init(&core->redo, core->pool, NULL, offsetof(bbStateChange,
                        listElement),bbStateChange_isSooner);
    *self = core;
    return Success;
}

bbFlag bbCore_receiveMessage(bbCore* core, bbStateChange* stateChange){
    bbStateChange* stateChange1;
    bbVPool_alloc(core->pool, &stateChange1);
    memcpy(stateChange1, stateChange, sizeof(bbStateChange));
    stateChange1->enactTime = stateChange1->sentTime + WAIT_TIME;

    bbList_sortR(&core->redo, stateChange1);

    return Success;
}