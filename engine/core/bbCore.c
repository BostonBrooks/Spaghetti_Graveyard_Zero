#include "engine/core/bbCore.h"
#include "engine/core/bbInstruction.h"
#include "engine/logic/bbBloatedPool.h"

bbFlag bbCore_init(bbCore* core)
{
    bbVPool_newBloated(&core->pool, sizeof(bbInstruction), 1000, 10);
    bbList_init(&core->doStack, core->pool, NULL, offsetof(bbInstruction, listElement),NULL);
    bbList_init(&core->undoStack, core->pool, NULL, offsetof(bbInstruction, listElement),NULL);
}


bbFlag bbCore_createDot(bbCore* core, bbScreenPoints SP,bool isInput);
{
    bbInstruction* instruction;
    bbVPool_alloc(core->pool, (void**)&instruction);
    instruction->type = bbInstruction_createDot;
    instruction->data.screenPoints.x = SP.x;
    instruction->data.screenPoints.y = SP.y;
    instruction->isInput = isInput;

    bbList_pushL(&core->doStack, instruction);

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
        if (instruction->type == bbInstruction_createDot)
        {
            bbInstruction_createDot_fn(core, instruction);
        }
    }

    return Success;
}