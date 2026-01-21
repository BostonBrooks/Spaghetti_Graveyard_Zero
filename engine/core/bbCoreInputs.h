#ifndef BBCOREINPUTS_H
#define BBCOREINPUTS_H
#include "engine/core/bbCore.h"
#include "engine/logic/bbFlag.h"

///isInput should be true unless being called from within a bbInstruction
bbFlag bbCore_printIndex(bbCore* core, bbScreenPoints SP, I32 index, bool isInput);
bbFlag bbCore_setGoalPoint(bbCore* core, bbMapCoords MC, bool isInput);
bbFlag bbCore_updateViewpoint(bbCore* core, bool isInput);
bbFlag bbCore_updateViewpointToPlayer(bbCore* core, bool isInput);
bbFlag bbCore_incrementClock(bbCore* core, bool isInput);
bbFlag bbCore_updateMoveables(bbCore* core, bool isInput);
bbFlag bbCore_moveUnit(bbCore* core, bbMapCoords mapCoords, bbPool_Handle handle,bool isInput);

bbFlag bbCore_moveRotateUnit(bbCore* core, bbMapCoords mapCoords, float angle, bbPool_Handle handle,bool isInput);
#endif //BBCOREINPUTS_H
