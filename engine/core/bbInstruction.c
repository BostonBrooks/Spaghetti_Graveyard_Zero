
#include <limits.h>

#include "engine/logic/bbFlag.h"
#include "engine/core/bbCore.h"
#include "engine/core/bbInstruction.h"

bbFlag bbInstruction_createDot_fn(bbCore* core, bbInstruction* instruction)
{
    //create dot
    //create undo instruction
    //if input
       //set pointer in undo instruction
    //else free instruction
    bbScreenPoints SP;
    SP.x = 0; SP.y = 0;
    bbCore_createDot(core, SP, false);
    bbVPool_free(core->pool, instruction);
    bbHere();
    return Success;
}
