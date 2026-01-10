
#include <limits.h>

#include "engine/logic/bbFlag.h"
#include "engine/core/bbCore.h"
#include "engine/core/bbCoreInputs.h"
#include "engine/core/bbInstruction.h"

#include "engine/data/bbHome.h"

bbFlag bbInstruction_printIndex_fn(bbCore* core, bbInstruction* instruction)
{
    bbHere()
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
    bbHere()
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
    bbHere()
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


bbFlag bbInstruction_unsetGoalPoint_fn(bbCore* core, bbInstruction* instruction)
{
    bbHere()
    testGoalPoint.i = instruction->data.mapCoords.i;
    testGoalPoint.j = instruction->data.mapCoords.j;
    testGoalPoint.k = instruction->data.mapCoords.k;

    if (instruction->isInput)
    {
        bbInstruction* redoInstruction;
        bbVPool_lookup(core->pool, (void**)&redoInstruction, instruction->redo);
        bbList_pushL(&core->doStack, redoInstruction);
    }

    bbVPool_free(core->pool, instruction);
    return Success;
}



bbFlag bbInstruction_updateViewpoint_fn(bbCore* core, bbInstruction* instruction)
{

    bbMapCoords oldViewpoint;
    oldViewpoint.i = home.private.viewport->viewpoint.i;
    oldViewpoint.j = home.private.viewport->viewpoint.j;
    oldViewpoint.k = home.private.viewport->viewpoint.k;

    bbMapCoords GoalPoint;
    GoalPoint.i = testGoalPoint.i;
    GoalPoint.j = testGoalPoint.j;
    GoalPoint.k = testGoalPoint.k;

    bbMapCoords difference;
    difference.i = GoalPoint.i - oldViewpoint.i;
    difference.j = GoalPoint.j - oldViewpoint.j;

    float speed = 8;
    float distance = sqrt(difference.i*difference.i
            + difference.j*difference.j);

    if (distance <= speed){
        home.private.viewport->viewpoint = testGoalPoint;
    } else {
        home.private.viewport->viewpoint.i += difference.i * speed / distance;
        home.private.viewport->viewpoint.j += difference.j * speed / distance;
    }

    bbUnit_setLocation((bbDrawable*)home.shared.player, home.shared.units,
                       home.private.viewport->viewpoint);

    //TODO post undoInstruction
    bbInstruction* undoInstruction;
    bbVPool_alloc(core->pool, (void**)&undoInstruction);
    undoInstruction->type = bbInstruction_unupdateViewpoint;
    undoInstruction->data.mapCoords.i = oldViewpoint.i;
    undoInstruction->data.mapCoords.j = oldViewpoint.j;
    undoInstruction->data.mapCoords.k = oldViewpoint.k;
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

bbFlag bbInstruction_unupdateViewpoint_fn(bbCore* core, bbInstruction* instruction)
{
    bbHere()

    home.private.viewport->viewpoint.i = instruction->data.mapCoords.i;
    home.private.viewport->viewpoint.j = instruction->data.mapCoords.j;
    home.private.viewport->viewpoint.k = instruction->data.mapCoords.k;

    bbUnit_setLocation((bbDrawable*)home.shared.player, home.shared.units,
                       home.private.viewport->viewpoint);
    if (instruction->isInput)
    {
        bbInstruction* redoInstruction;
        bbVPool_lookup(core->pool, (void**)&redoInstruction, instruction->redo);
        bbList_pushL(&core->doStack, redoInstruction);
    }

    bbVPool_free(core->pool, instruction);
    return Success;
}