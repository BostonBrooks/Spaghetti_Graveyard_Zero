#ifndef BBCOREINPUTS_H
#define BBCOREINPUTS_H
#include "engine/core/bbCore.h"
#include "engine/logic/bbFlag.h"

///isInput should be true unless being called from within a bbInstruction
bbFlag bbCore_printIndex(bbCore* core, bbScreenPoints SP, I32 index, bool isInput);
bbFlag bbCore_setGoalPoint(bbCore* core, bbMapCoords MC, bool isInput);

#endif //BBCOREINPUTS_H
