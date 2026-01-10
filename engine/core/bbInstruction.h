
#ifndef BBINSTRUCTION_H
#define BBINSTRUCTION_H

#include "engine/core/bbCore.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbPoolHandle.h"

typedef enum
{
    bbInstruction_createDot,
    bbInstruction_deleteDot
} bbInstruction_type;

typedef struct
{

    bbScreenPoints screenPoints;
    I32 i;
} bbInstruction_createDot_data;

typedef union
{
    bbInstruction_createDot_data createDot;
    bbPool_Handle handle;
} bbInstruction_data;

typedef struct
{
    bbInstruction_type type;
    bbInstruction_data data;
    bbPool_ListElement* listElement;
    bbPool_Handle redo;
    bool isInput;
} bbInstruction;

bbFlag bbInstruction_createDot_fn(bbCore* core, bbInstruction* instruction);



#endif // BBINSTRUCTION_H