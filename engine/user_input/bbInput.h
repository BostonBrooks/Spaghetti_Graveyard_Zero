

#ifndef BBINPUT_H
#define BBINPUT_H

#include "engine/logic/bbFlag.h"
#include "engine/includes/CSFML.h"
#include "engine/graphics/bbGraphics.h"
#include "engine/user_input/bbMouse.h"
#include "engine/user_input/bbMoose.h"

typedef struct {
    bbMouse* mouse;
    bbMoose* moose;
} bbInput;

bbFlag bbInput_new(bbInput* input, sfRenderWindow* window, bbMouse* mouse, bbMoose* moose);
bbFlag bbInput_poll(bbInput* input, sfRenderWindow* window);


#endif //BBINPUT_H

