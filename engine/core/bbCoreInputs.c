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
        instruction->data.mapCoords.k = MC.k;
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
    instruction->isInput = isInput;
    bbList_pushL(&core->doStack, instruction);

    return Success;
}

bbFlag bbCore_updateViewpointToPlayer(bbCore* core, bool isInput)
{
    bbInstruction* instruction;

    //TODO roll the following three lines into one function
    bbFlag flag = bbList_alloc(&core->doStack, (void**)&instruction);
    instruction->type = bbInstruction_ViewpointToPlayer;
    instruction->isInput = isInput;
    bbList_pushL(&core->doStack, instruction);

    return Success;
}

bbFlag bbCore_incrementClock(bbCore* core, bool isInput)
{
    bbInstruction* instruction;

    //TODO roll the following three lines into one function
    bbFlag flag = bbList_alloc(&core->doStack, (void**)&instruction);
    instruction->type = bbInstruction_incrementClock;
    instruction->isInput = isInput;
    bbList_pushL(&core->doStack, instruction);

    return Success;
}


bbFlag bbCore_updateMoveables(bbCore* core, bool isInput)
{
    bbInstruction* instruction;
    //TODO roll the following three lines into one function
    bbFlag flag = bbList_alloc(&core->doStack, (void**)&instruction);
    instruction->type = bbInstruction_updateMoveables;
    instruction->isInput = isInput;
    bbList_pushL(&core->doStack, instruction);
    return Success;
}


bbFlag bbCore_moveUnit(bbCore* core, bbMapCoords mapCoords, bbPool_Handle handle, bool isInput)
{
    bbInstruction* instruction;
    //TODO roll the following three lines into one function
    bbFlag flag = bbList_alloc(&core->doStack, (void**)&instruction);
    instruction->type = bbInstruction_moveUnit;
    instruction->data.moveUnit.mapCoords = mapCoords;
    instruction->data.moveUnit.unitHandle = handle;
    instruction->isInput = isInput;
    bbList_pushL(&core->doStack, instruction);
    return Success;
}

bbFlag bbCore_moveRotateUnit(bbCore* core, bbMapCoords mapCoords, float angle, bbPool_Handle handle, bool isInput)
{
    bbInstruction* instruction;
    //TODO roll the following three lines into one function
    bbFlag flag = bbList_alloc(&core->doStack, (void**)&instruction);
    instruction->type = bbInstruction_moveRotateUnit;
    instruction->data.moveUnit.mapCoords = mapCoords;
    instruction->data.moveUnit.unitHandle = handle;
    instruction->data.moveUnit.angle = angle;
    instruction->isInput = isInput;
    bbList_pushL(&core->doStack, instruction);
    return Success;
}