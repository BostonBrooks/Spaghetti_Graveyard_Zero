#include "engine/core/bbCoreInputs.h"

#include "engine/core/bbInstruction.h"
#include "engine/logic/bbFlag.h"

bbFlag bbCore_createDot(bbCore* core, bbScreenPoints SP, I32 numDots, bool isInput)
{
    bbInstruction* instruction;
    bbVPool_alloc(core->pool, (void**)&instruction);
    instruction->type = bbInstruction_createDot;
    instruction->data.createDot.screenPoints.x = SP.x;
    instruction->data.createDot.screenPoints.y = SP.y;
    instruction->data.createDot.i = numDots;
    instruction->isInput = isInput;

    bbList_pushL(&core->doStack, instruction);

    return Success;
}
