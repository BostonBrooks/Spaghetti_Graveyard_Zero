
#include <limits.h>

#include "engine/logic/bbFlag.h"
#include "engine/core/bbCore.h"
#include "engine/core/bbCoreInputs.h"
#include "engine/core/bbInstruction.h"

bbFlag bbInstruction_printIndex_fn(bbCore* core, bbInstruction* instruction)
{
    //create dot
    //create undo instruction
    //if input
       //set pointer in undo instruction
    //else free instruction
    bbScreenPoints SP;
    SP.x = 0; SP.y = 0;
    if (instruction->data.screenPoints.i > 0)
        bbCore_printIndex(core, SP, instruction->data.screenPoints.i - 1, false);
    bbDebug("index = %d\n", instruction->data.screenPoints.i);

    bbInstruction* undoInstruction;
    bbVPool_alloc(core->pool, (void**)&undoInstruction);
    undoInstruction->type = bbInstruction_unprintIndex;
    undoInstruction->data.screenPoints.screenPoints.x = SP.x;
    undoInstruction->data.screenPoints.screenPoints.y = SP.y;
    undoInstruction->data.screenPoints.i = instruction->data.screenPoints.i;
    undoInstruction->isInput = instruction->isInput;



    if (!instruction->isInput)
    {
        bbVPool_free(core->pool, instruction);
        undoInstruction->redo = core->pool->null;
    } else
    {
        bbPool_Handle handle;
        bbVPool_reverseLookup(core->pool, instruction, &handle);
        undoInstruction->redo = handle;

        instruction->listElement.prev = core->pool->null;
        instruction->listElement.next = core->pool->null;
    }


    bbList_pushL(&core->undoStack, undoInstruction);
    return Success;
}


bbFlag bbInstruction_unprintIndex_fn(bbCore* core, bbInstruction* instruction)
{
    bbDebug("unprint index = %d\n", instruction->data.screenPoints.i);

    if (instruction->isInput)
    {
        bbInstruction* redoInstruction;
        bbVPool_lookup(core->pool, (void**)&redoInstruction, instruction->redo);
        bbList_pushL(&core->doStack, redoInstruction);
    }

    bbVPool_free(core->pool, instruction);
    return Success;
}
extern bbMapCoords testGoalPoint;

bbFlag bbInstruction_setGoalPoint_fn(bbCore* core, bbInstruction* instruction)
{
    bbMapCoords oldGoalPoint;
    oldGoalPoint.i = testGoalPoint.i;
    oldGoalPoint.j = testGoalPoint.j;
    oldGoalPoint.k = testGoalPoint.k;

    testGoalPoint.i = instruction->data.mapCoords.i;
    testGoalPoint.j = instruction->data.mapCoords.j;
    testGoalPoint.k = instruction->data.mapCoords.k;

    bbInstruction* undoInstruction;
    bbVPool_alloc(core->pool, (void**)&undoInstruction);
    undoInstruction->type = bbInstruction_unsetGoalPoint;
    undoInstruction->data.mapCoords.i = oldGoalPoint.i;
    undoInstruction->data.mapCoords.j = oldGoalPoint.j;
    undoInstruction->data.mapCoords.k = oldGoalPoint.k;
    undoInstruction->isInput = instruction->isInput;

    if (!instruction->isInput)
    {
        bbVPool_free(core->pool, instruction);
        undoInstruction->redo = core->pool->null;
    } else
    {
        bbPool_Handle handle;
        bbVPool_reverseLookup(core->pool, instruction, &handle);
        undoInstruction->redo = handle;

        instruction->listElement.prev = core->pool->null;
        instruction->listElement.next = core->pool->null;
    }


    bbList_pushL(&core->undoStack, undoInstruction);

    return Success;

}