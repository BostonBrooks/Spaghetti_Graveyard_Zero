#include "engine/core/bbCore.h"
#include "engine/core/bbInstruction.h"
#include "engine/logic/bbBloatedPool.h"

bbFlag bbCore_init(bbCore* core)
{
    bbVPool_newBloated(&core->pool, sizeof(bbInstruction), 1000, 10);
    bbList_init(&core->doStack, core->pool, NULL, offsetof(bbInstruction, listElement),NULL);
    bbList_init(&core->undoStack, core->pool, NULL, offsetof(bbInstruction, listElement),NULL);
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
        if (instruction->type == bbInstruction_unprintIndex)
        {
            bbInstruction_unprintIndex_fn(core, instruction);
        }
    }

    return Success;
}