#include "engine/core/bbCore.h"
#include "engine/core/bbInstruction.h"
#include "engine/data/bbHome.h"
#include "engine/logic/bbBloatedPool.h"

bbFlag bbCore_init(bbCore* core)
{
    //TODO eventually the pool will fill
    bbVPool_newBloated(&core->pool, sizeof(bbInstruction), 1000, 1000);
    bbList_init(&core->doStack, core->pool, NULL, offsetof(bbInstruction, listElement),NULL);
    bbList_init(&core->undoStack, core->pool, NULL, offsetof(bbInstruction, listElement),NULL);
    bbMoveables_init(&core->moveables);
    return Success;
}

bbFlag bbCore_react(bbCore* core)
{
    bbFlag flag;
    bbInstruction* instruction;

    while (1)
    {
        flag = bbList_popL(&core->doStack, (void**)&instruction);
        if (flag != Success) return Success;
        //TODO use switch()
        if (instruction->type == bbInstruction_printIndex)
        {
            bbInstruction_printIndex_fn(core, instruction);
        }
        if (instruction->type == bbInstruction_updateViewpoint)
        {
            bbInstruction_updateViewpoint_fn(core, instruction);
        }

        if (instruction->type == bbInstruction_setGoalPoint)
        {
            bbInstruction_setGoalPoint_fn(core, instruction);
        }

        if (instruction->type == bbInstruction_incrementClock)
        {
            bbInstruction_incrementClock_fn(core, instruction);
        }

        if (instruction->type == bbInstruction_updateMoveables)
        {
            bbInstruction_updateMoveables_fn(core, instruction);
        }

        if (instruction->type == bbInstruction_unupdateMoveables)
        {
            bbInstruction_unupdateMoveables_fn(core, instruction);
        }


        if (instruction->type == bbInstruction_moveUnit)
        {
            bbInstruction_moveUnit_fn(core, instruction);
        }

        if (instruction->type == bbInstruction_moveRotateUnit)
        {
            bbInstruction_moveRotateUnit_fn(core, instruction);
        }
        if (instruction->type == bbInstruction_ViewpointToPlayer)
        {
            bbInstruction_ViewpointToPlayer_fn(core, instruction);
        }

    }

    return Success;
}


bbFlag bbCore_rewind(bbCore* core)
{
    bbFlag flag;
    bbInstruction* instruction;

    while (1)
    {
        flag = bbList_popL(&core->undoStack, (void**)&instruction);
        if (flag != Success) return Success;
        //TODO use switch()

        //bbInstructionType_print(instruction->type);

        if (instruction->type == bbInstruction_unprintIndex)
        {
            bbInstruction_unprintIndex_fn(core, instruction);
        }
        if (instruction->type == bbInstruction_unupdateViewpoint)
        {
            bbInstruction_unupdateViewpoint_fn(core, instruction);
        }
        if (instruction->type == bbInstruction_unsetGoalPoint)
        {
            bbInstruction_unsetGoalPoint_fn(core, instruction);
        }

        if (instruction->type == bbInstruction_unincrementClock)
        {
            bbInstruction_unincrementClock_fn(core, instruction);
        }

        if (instruction->type == bbInstruction_unmoveUnit)
        {
            bbInstruction_unmoveUnit_fn(core, instruction);
        }

        if (instruction->type == bbInstruction_unmoveRotateUnit)
        {
            bbInstruction_unmoveRotateUnit_fn(core, instruction);
        }
    }

    return Success;
}

bbFlag bbCore_clearFuture(bbCore* core)
{
    bbFlag flag;
    bbInstruction* instruction;


    while (1)
    {
        flag = bbList_popL(&core->doStack, (void**)&instruction);
        if (flag != Success) break;
        bbVPool_free(core->pool, instruction);
    }
}



bbFlag bbCore_rewindUntil(bbCore* core, bbCallback* callback)
{
    bbFlag flag;
    bbInstruction* instruction;

    while (1)
    {
        bbPool_Handle coreHandle;
        coreHandle.ptr = (void*)core;
        flag = bbCallback_execute(callback, coreHandle);
        if (flag == Break) return Success;

        flag = bbList_popL(&core->undoStack, (void**)&instruction);
        if (flag != Success) return Success;
        //TODO use switch()

        //bbInstructionType_print(instruction->type);

        if (instruction->type == bbInstruction_unprintIndex)
        {
            bbInstruction_unprintIndex_fn(core, instruction);
        }
        if (instruction->type == bbInstruction_unupdateViewpoint)
        {
            bbInstruction_unupdateViewpoint_fn(core, instruction);
        }
        if (instruction->type == bbInstruction_unsetGoalPoint)
        {
            bbInstruction_unsetGoalPoint_fn(core, instruction);
        }

        if (instruction->type == bbInstruction_unincrementClock)
        {
            bbInstruction_unincrementClock_fn(core, instruction);
        }
        if (instruction->type == bbInstruction_unmoveUnit)
        {
            bbInstruction_unmoveUnit_fn(core, instruction);
        }
        if (instruction->type == bbInstruction_unmoveRotateUnit)
        {
            bbInstruction_unmoveRotateUnit_fn(core, instruction);
        }
    }

    return Success;
}

//typedef bbFlag bbCallbackFunction(void* callback, bbPool_Handle handle);
bbFlag isTimeEqual(void* callback, bbPool_Handle handle){
    bbCore* core = handle.ptr;
    bbCallback* Callback = callback;
    U64 targetTime = Callback->args.u64;

    if (targetTime == home.private.mapTime) return Break;
    return Continue;
}

bbFlag bbCore_rewindUntilTime(bbCore* core, U64 time)
{
    bbCallback callback;
    callback.args.u64 = time;
    callback.function = isTimeEqual;

    return  bbCore_rewindUntil(core, &callback);
}