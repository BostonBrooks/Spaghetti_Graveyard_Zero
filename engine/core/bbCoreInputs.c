#include "engine/core/bbCoreInputs.h"

#include "engine/core/bbInstruction.h"
#include "engine/logic/bbFlag.h"

bbFlag bbCore_printIndex(bbCore* core, bbScreenPoints SP, I32 index, bool isInput)
{
    bbInstruction* instruction;

    //TODO roll the following three lines into one function
    bbFlag flag = bbVPool_alloc(core->pool, (void**)&instruction);
    instruction->listElement.prev = core->pool->null;
    instruction->listElement.next = core->pool->null;



    instruction->type = bbInstruction_printIndex;
    instruction->data.printIndex.screenPoints.x = SP.x;
    instruction->data.printIndex.screenPoints.y = SP.y;
    instruction->data.printIndex.i = index;
    instruction->isInput = isInput;

    bbList_pushL(&core->doStack, instruction);

    return Success;
}

