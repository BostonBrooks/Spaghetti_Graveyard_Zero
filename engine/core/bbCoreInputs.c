#include "engine/core/bbCoreInputs.h"

#include "engine/core/bbInstruction.h"
#include "engine/logic/bbFlag.h"

bbFlag bbCore_printIndex(bbCore* core, bbScreenPoints SP, I32 index, bool isInput)
{
    bbInstruction* instruction;

    //TODO roll the following three lines into one function
    bbFlag flag = bbList_alloc(&core->doStack, (void**)&instruction);



    instruction->type = bbInstruction_printIndex;
    instruction->data.screenPoints.screenPoints.x = SP.x;
    instruction->data.screenPoints.screenPoints.y = SP.y;
    instruction->data.screenPoints.i = index;
    instruction->isInput = isInput;

    bbList_pushL(&core->doStack, instruction);

    return Success;
}


bbFlag bbCore_setGoalPoint(bbCore* core, bbMapCoords MC, bool isInput)
{

        bbInstruction* instruction;

        //TODO roll the following three lines into one function
        bbFlag flag = bbList_alloc(&core->doStack, (void**)&instruction);



        instruction->type = bbInstruction_setGoalPoint;
        instruction->data.mapCoords.i = MC.i;
        instruction->data.mapCoords.j = MC.j;
        instruction->data.mapCoords.j = MC.j;
        instruction->isInput = isInput;

        bbList_pushL(&core->doStack, instruction);

        return Success;
}


bbFlag bbCore_updateViewpoint(bbCore* core, bool isInput)
{
    bbInstruction* instruction;

    //TODO roll the following three lines into one function
    bbFlag flag = bbList_alloc(&core->doStack, (void**)&instruction);
    instruction->type = bbInstruction_updateViewpoint;
    bbList_pushL(&core->doStack, instruction);

    return Success;
}


bbFlag bbCore_incrementClock(bbCore* core, bool isInput)
{
    bbInstruction* instruction;

    //TODO roll the following three lines into one function
    bbFlag flag = bbList_alloc(&core->doStack, (void**)&instruction);
    instruction->type = bbInstruction_incrementClock;
    bbList_pushL(&core->doStack, instruction);

    return Success;
}