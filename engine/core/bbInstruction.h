
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
    bbInstruction_unupdateViewpoint,
    bbInstruction_incrementClock,
    bbInstruction_unincrementClock,
    bbInstruction_updateMoveables,
    bbInstruction_unupdateMoveables,
    bbInstruction_moveUnit,
    bbInstruction_unmoveUnit,
    bbInstruction_moveRotateUnit,
    bbInstruction_unmoveRotateUnit

} bbInstruction_type;

typedef struct
{
    bbMapCoords mapCoords;
    float angle;
    bbPool_Handle unitHandle;
} bbInstruction_moveUnit_data;

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
    bbInstruction_moveUnit_data moveUnit;
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

bbFlag bbInstruction_incrementClock_fn(bbCore* core, bbInstruction* instruction);
bbFlag bbInstruction_unincrementClock_fn(bbCore* core, bbInstruction* instruction);

bbFlag bbInstruction_updateMoveables_fn(bbCore* core, bbInstruction* instruction);
bbFlag bbInstruction_unupdateMoveables_fn(bbCore* core, bbInstruction* instruction);

bbFlag bbInstruction_moveUnit_fn(bbCore* core, bbInstruction* instruction);
bbFlag bbInstruction_unmoveUnit_fn(bbCore* core, bbInstruction* instruction);

bbFlag bbInstruction_moveRotateUnit_fn(bbCore* core, bbInstruction* instruction);
bbFlag bbInstruction_unmoveRotateUnit_fn(bbCore* core, bbInstruction* instruction);
#endif // BBINSTRUCTION_H