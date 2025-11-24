#ifndef BBDUMMYRECEIVER_H
#define BBDUMMYRECEIVER_H

#include "engine/dummyserver/bbDummySender.h"
#include "engine/data/bbHome.h"


bbFlag bbDummyReceiver_receive(bbDummySender* server, U64 gameTime );



bbFlag bbDummyReceiver_textMessage(bbDummySender_msg* message);
bbFlag bbDummyReceiver_setActiveSpell(bbDummySender_msg* message);
bbFlag bbDummyReceiver_castSpell(bbDummySender_msg* message);







#endif //BBDUMYYRECEIVER