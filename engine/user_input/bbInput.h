#include "engine/logic/bbFlag.h"
#include "engine/includes/csfml.h"
#include "engine/graphics/bbGraphics.h"
#include "engine/user_input/bbMouse.h"

#ifndef BBINPUT_H
#define BBINPUT_H

typedef struct {
    bbMouse* mouse;
} bbInput;

bbFlag bbInput_new(bbInput* input, sfRenderWindow* window, bbMouse* mouse);
bbFlag bbInput_poll(bbInput* input, sfRenderWindow* window);


#endif //BBINPUT_H