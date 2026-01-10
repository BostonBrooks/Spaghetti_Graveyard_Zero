#ifndef BBCOREINPUTS_H
#define BBCOREINPUTS_H
#include "engine/core/bbCore.h"
#include "engine/logic/bbFlag.h"

///isInput should be true unless being called from within a bbInstruction
bbFlag bbCore_createDot(bbCore* core, bbScreenPoints SP, I32 numDots, bool isInput);

#endif //BBCOREINPUTS_H
