/**
 * @file
 * @brief when a mouse moves, we search through widgets with the onMouse
 * function. If the mouse is found to have moved over a new widget,
 * onMouse calls bbMouse_leave, which calls onMouseLeft and then onMouse
 * calls onMouseEntered
 *
*/

#ifndef BBMOUSE_H
#define BBMOUSE_H

#include "engine/logic/bbFlag.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/widgets/bbWidget.h"



typedef struct {
    bbScreenPoints position;
    sfSprite* cursor;
    bbPool_Handle current_widget;
} bbMouse;

typedef struct {
    I32 state;
    I32 onMouse;
    I32 onMouseEntered;
    I32 onMouseLeft;

} bbOnMouse;

bbFlag bbMouse_new(bbMouse* mouse, sfRenderWindow* window, bbGraphics* graphics);

bbFlag bbMouse_update(bbMouse* mouse, sfEvent* event);
bbFlag bbMouse_draw(bbMouse* mouse, sfRenderWindow* window);

bbFlag bbMouse_leave(bbMouse* mouse);
typedef bbFlag bbMouseHandler(bbMouse* mouse, void* drawable, sfEvent* event);



#endif //BBMOUSE_H


