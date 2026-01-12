

#ifndef BBINPUT_H
#define BBINPUT_H

#include "engine/logic/bbFlag.h"
#include "engine/includes/CSFML.h"
#include "engine/graphics/bbGraphicsApp.h"
#include "engine/userinterface/bbMouse.h"
#include "engine/userinterface/bbWidget.h"

typedef struct {
    bbMouse* mouse;
    bbWidgets* widgets;


    char keymap_lowercase[sfKeyCount];
    char keymap_uppercase[sfKeyCount];
} bbInput;

bbFlag bbInput_new(bbInput* input, sfRenderWindow* window, bbMouse* mouse, bbWidgets* widgets);
bbFlag bbInput_poll(bbInput* input, sfRenderWindow* window);


#endif //BBINPUT_H

