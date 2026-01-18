
#include <limits.h>

#include "engine/logic/bbFlag.h"
#include "engine/core/bbCore.h"
#include "engine/core/bbCoreInputs.h"
#include "engine/core/bbInstruction.h"

#include "engine/data/bbHome.h"

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


bbFlag bbInstruction_unsetGoalPoint_fn(bbCore* core, bbInstruction* instruction)
{

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
    oldViewpoint.i = home.private.viewportApp.viewport.viewpoint.i;
    oldViewpoint.j = home.private.viewportApp.viewport.viewpoint.j;
    oldViewpoint.k = home.private.viewportApp.viewport.viewpoint.k;

    bbMapCoords GoalPoint;
    GoalPoint.i = testGoalPoint.i;
    GoalPoint.j = testGoalPoint.j;
    GoalPoint.k = testGoalPoint.k;

    bbMapCoords difference;
    difference.i = GoalPoint.i - oldViewpoint.i;
    difference.j = GoalPoint.j - oldViewpoint.j;

    float speed = 16;
    float distance = sqrt(difference.i*difference.i
            + difference.j*difference.j);

    if (distance <= speed){
        home.private.viewportApp.viewport.viewpoint = testGoalPoint;
    } else {
        home.private.viewportApp.viewport.viewpoint.i += difference.i * speed / distance;
        home.private.viewportApp.viewport.viewpoint.j += difference.j * speed / distance;
    }

    // bbDebug("i = %d, j = %d, k = %d\n",
    //     home.private.viewportApp.viewport.viewpoint.i,
    //     home.private.viewportApp.viewport.viewpoint.j,
    //     home.private.viewportApp.viewport.viewpoint.k);
    bbUnit_setLocation((bbDrawable*)home.shared.player, home.private.viewportApp.units,
                       home.private.viewportApp.viewport.viewpoint);

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

    home.private.viewportApp.viewport.viewpoint.i = instruction->data.mapCoords.i;
    home.private.viewportApp.viewport.viewpoint.j = instruction->data.mapCoords.j;
    home.private.viewportApp.viewport.viewpoint.k = instruction->data.mapCoords.k;

    bbUnit_setLocation((bbDrawable*)home.shared.player, home.private.viewportApp.units,
                       home.private.viewportApp.viewport.viewpoint);
    if (instruction->isInput)
    {
        bbInstruction* redoInstruction;
        bbVPool_lookup(core->pool, (void**)&redoInstruction, instruction->redo);
        bbList_pushL(&core->doStack, redoInstruction);
    }

    bbVPool_free(core->pool, instruction);
    return Success;
}

///eventually this will include a wait time to achieve 60hz,
///except for the case when we want to fast-forward?
bbFlag bbInstruction_incrementClock_fn(bbCore* core, bbInstruction* instruction)
{
    U64 oldTime = home.private.mapTime;
    home.private.mapTime++;

    bbInstruction* undoInstruction;
    bbVPool_alloc(core->pool, (void**)&undoInstruction);
    undoInstruction->type = bbInstruction_unincrementClock;
    undoInstruction->data.handle.u64 = oldTime;
    undoInstruction->isInput = instruction->isInput;

    //redo instruction
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

}


bbFlag bbInstruction_unincrementClock_fn(bbCore* core, bbInstruction* instruction)
{
    home.private.mapTime = instruction->data.handle.u64;
    if (instruction->isInput)
    {
        bbInstruction* redoInstruction;
        bbVPool_lookup(core->pool, (void**)&redoInstruction, instruction->redo);
        bbList_pushL(&core->doStack, redoInstruction);
    }

    bbVPool_free(core->pool, instruction);
    return Success;
}
/* It's a bit complicated here because updateMoveables will push a bunch of instructions to the stack.
 * Each instruction will move one unit to a new location and put the reverse instruction on the undo stack
 *
 * Each instruction will store an undo instruction to the undo stack
 *
 * To reverse this, each of the move instructions on the undo stack will be undone
 * Then the undo function for updateMoveable will be placed on the undo stack
 *
 * unupdateMoveables will put updateMoveables on the redo stack and thats all
 *
 * in summary, put unupdateMoveables on the undo stack, then update Moveables
 */
bbFlag bbInstruction_updateMoveables_fn(bbCore* core, bbInstruction* instruction)
{
    bbInstruction* undoInstruction;
    bbVPool_alloc(core->pool, (void**)&undoInstruction);
    undoInstruction->type = bbInstruction_unupdateMoveables;
    undoInstruction->isInput = instruction->isInput;


    bbMoveables_getInput(&home.shared.core->moveables);
    bbMoveables_update(&home.shared.core->moveables);
    bbMoveables_putOutput_Core(&home.shared.core->moveables);

    return Success;
}


bbFlag bbInstruction_unupdateMoveables_fn(bbCore* core, bbInstruction* instruction)
{
    return Success;
}


bbFlag bbInstruction_moveUnit_fn(bbCore* core, bbInstruction* instruction)
{
    bbUnit* unit;
    bbPool_Handle handle = instruction->data.moveUnit.unitHandle;
    bbMapCoords mapCoords = instruction->data.moveUnit.mapCoords;
    bbVPool* unitPool = home.private.viewportApp.units->pool;
    bbVPool_lookup(unitPool, (void**)&unit, handle);

    bbInstruction* undoInstruction;
    bbVPool_alloc(core->pool, (void**)&undoInstruction);
    undoInstruction->type = bbInstruction_unmoveUnit;
    undoInstruction->data.moveUnit.unitHandle = handle;
    undoInstruction->data.moveUnit.mapCoords = unit->drawable.coords;
    undoInstruction->isInput = instruction->isInput;

    bbUnit_setLocation((bbDrawable*)unit, home.private.viewportApp.units, mapCoords);


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


bbFlag bbInstruction_unmoveUnit_fn(bbCore* core, bbInstruction* instruction)
{
    bbUnit* unit;
    bbPool_Handle handle = instruction->data.moveUnit.unitHandle;
    bbMapCoords mapCoords = instruction->data.moveUnit.mapCoords;
    bbVPool* unitPool = home.private.viewportApp.units->pool;
    bbVPool_lookup(unitPool, (void**)&unit, handle);

    bbUnit_setLocation((bbDrawable*)unit, home.private.viewportApp.units, mapCoords);

    if (instruction->isInput)
    {
        bbInstruction* redoInstruction;
        bbVPool_lookup(core->pool, (void**)&redoInstruction, instruction->redo);
        bbList_pushL(&core->doStack, redoInstruction);
    }

    bbVPool_free(core->pool, instruction);
    return Success;
}

bbFlag bbInstruction_moveRotateUnit_fn(bbCore* core, bbInstruction* instruction)
{
    bbUnit* unit;
    bbPool_Handle handle = instruction->data.moveUnit.unitHandle;
    bbMapCoords mapCoords = instruction->data.moveUnit.mapCoords;
    float angle = instruction->data.moveUnit.angle;
    bbVPool* unitPool = home.private.viewportApp.units->pool;
    bbVPool_lookup(unitPool, (void**)&unit, handle);

    bbInstruction* undoInstruction;
    bbVPool_alloc(core->pool, (void**)&undoInstruction);
    undoInstruction->type = bbInstruction_unmoveRotateUnit;
    undoInstruction->data.moveUnit.unitHandle = handle;
    undoInstruction->data.moveUnit.mapCoords = unit->drawable.coords;
    undoInstruction->data.moveUnit.angle = unit->drawable.rotation;
    undoInstruction->isInput = instruction->isInput;

    bbUnit_setLocation((bbDrawable*)unit, home.private.viewportApp.units, mapCoords);
    unit->drawable.rotation = angle;


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

bbFlag bbInstruction_unmoveRotateUnit_fn(bbCore* core, bbInstruction* instruction)
{
    bbUnit* unit;
    bbPool_Handle handle = instruction->data.moveUnit.unitHandle;
    bbMapCoords mapCoords = instruction->data.moveUnit.mapCoords;
    float angle = instruction->data.moveUnit.angle;
    bbVPool* unitPool = home.private.viewportApp.units->pool;
    bbVPool_lookup(unitPool, (void**)&unit, handle);

    bbUnit_setLocation((bbDrawable*)unit, home.private.viewportApp.units, mapCoords);
    unit->drawable.rotation = angle;

    if (instruction->isInput)
    {
        bbInstruction* redoInstruction;
        bbVPool_lookup(core->pool, (void**)&redoInstruction, instruction->redo);
        bbList_pushL(&core->doStack, redoInstruction);
    }

    bbVPool_free(core->pool, instruction);
    return Success;
}