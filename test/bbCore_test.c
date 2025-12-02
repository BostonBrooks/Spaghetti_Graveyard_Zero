#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbTerminal.h"

#include "engine/userinterface/bbWidget.h"
#include "engine/core/bbMessages.h"
#include "engine/data/bbHome.h"

bbWidgets* testWidgets;
bbMapCoords testGoalPoint;
bbHome home;

int main(void){


    U64 time = 0;

    bbMessages* messages;
    bbMessages_new(&messages);
    bbSendMessage* send;

    for (time = 0; time<1000; time++){
        bbPrintf("time = %d\n", time);
        bbMessage_new(&send, messages);
        sprintf(send->data.txt, "message_created t=%llu", time);
        bbMessage_send(send, messages, time);
        bbMessages_send(messages, time);
        bbMessages_receive(messages, time);

    }
    exit(EXIT_SUCCESS);
}