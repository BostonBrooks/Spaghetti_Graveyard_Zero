
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
    if (instruction->data.printIndex.i > 0)
        bbCore_printIndex(core, SP, instruction->data.printIndex.i - 1, false);
    bbDebug("index = %d\n", instruction->data.printIndex.i);

    bbInstruction* undoInstruction;
    bbVPool_alloc(core->pool, (void**)&undoInstruction);
    undoInstruction->type = bbInstruction_unprintIndex;
    undoInstruction->data.printIndex.screenPoints.x = SP.x;
    undoInstruction->data.printIndex.screenPoints.y = SP.y;
    undoInstruction->data.printIndex.i = instruction->data.printIndex.i;
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
    bbDebug("unprint index = %d\n", instruction->data.printIndex.i);

    if (instruction->isInput)
    {
        bbInstruction* redoInstruction;
        bbVPool_lookup(core->pool, (void**)&redoInstruction, instruction->redo);
        bbList_pushL(&core->doStack, redoInstruction);
    }

    bbVPool_free(core->pool, instruction);
    return Success;
}