
#ifndef BBINSTRUCTION_H
#define BBINSTRUCTION_H

#include "engine/core/bbCore.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbPoolHandle.h"

typedef enum
{
    bbInstruction_printIndex,
    bbInstruction_unprintIndex,
    bbInstruction_setGoalPoint,
    bbInstruction_unsetGoalPoint,
    bbInstruction_updateViewpoint,
    bbInstruction_unupdateViewpoint

} bbInstruction_type;

typedef struct
{

    bbScreenPoints screenPoints;
    I32 i;
} bbInstruction_printIndex_data;

typedef union
{
    bbInstruction_printIndex_data screenPoints;
    bbMapCoords mapCoords;
    bbPool_Handle handle;
} bbInstruction_data;

typedef struct
{
    bbInstruction_type type;
    bbInstruction_data data;
    bbPool_ListElement listElement;
    bbPool_Handle redo;
    bool isInput;
} bbInstruction;

bbFlag bbInstruction_printIndex_fn(bbCore* core, bbInstruction* instruction);
bbFlag bbInstruction_unprintIndex_fn(bbCore* core, bbInstruction* instruction);


bbFlag bbInstruction_setGoalPoint_fn(bbCore* core, bbInstruction* instruction);
bbFlag bbInstruction_unsetGoalPoint_fn(bbCore* core, bbInstruction* instruction);

bbFlag bbInstruction_updateViewpoint_fn(bbCore* core, bbInstruction* instruction);
bbFlag bbInstruction_unupdateViewpoint_fn(bbCore* core, bbInstruction* instruction);
#endif // BBINSTRUCTION_H