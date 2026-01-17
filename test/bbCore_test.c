#include "engine/core/bbCore.h"
#include "engine/core/bbCoreInputs.h"
#include "engine/core/bbInstruction.h"
#include "engine/data/bbHome.h"
//TODO this should not depend on all the other c files
_Thread_local char* thread;
bbWidgets* testWidgets;
bbMapCoords testGoalPoint;
bbHome home;

int main (void)
{
    bbCore core;
    bbCore_init(&core);
    bbScreenPoints SP;
    SP.x = 100; SP.y = 100;
    bbCore_printIndex(&core, SP, 10,true);
    bbCore_react(&core);
    bbCore_rewind(&core);
    bbCore_react(&core);
    return 0;
}