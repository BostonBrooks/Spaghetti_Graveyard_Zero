#include "engine/user_input/bbMouse.h"

#ifndef BBMOUSEHANDLERS_H
#define BBMOUSEHANDLERS_H



#endif //BBMOUSEHANDLERS_H

typedef struct {
    I32 num;
    bbDictionary* dictionary;
    bbMouseHandler* functions[];
} bbMouseHandlers;

bbFlag bbMouseHandlers_new(bbMouseHandlers** mouseHandlers);