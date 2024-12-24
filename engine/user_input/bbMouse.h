#include "engine/logic/bbFlag.h"
#include "engine/geometry/bbCoordinates.h"

#ifndef BBMOUSE_H
#define BBMOUSE_H


typedef struct {
    bbScreenPoints position;
    sfSprite* cursor;
} bbMouse;

bbFlag bbMouse_new(bbMouse* mouse, sfRenderWindow* window, bbGraphics* graphics);

bbFlag bbMouse_update(bbMouse* mouse, sfEvent* event);
bbFlag bbMouse_draw(bbMouse* mouse, sfRenderWindow* window);

#endif //BBMOUSE_H