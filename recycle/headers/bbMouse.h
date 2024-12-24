/**
 * @file bbMouse
 * This file passes mouse state on to widgets
 * Another file will later handle key events
 * Both of these are of type sfEvent
*/

#ifndef BBMOUSE
#define BBMOUSE

#include <stdbool.h>
#include "bbSystemIncludes.h"
#include "bbGeometry.h"
#include "bbIntTypes.h"

#define f_MouseMove 0
#define f_MouseLeft 1
#define f_MouseRight 2


typedef struct {
    bbScreenCoordsI m_ScreenCoords;
    I32 m_type;
} bbMouseEvent;






/// If the event is a mouse click
I32 EventMouse(bbMouseEvent* mouse, int map);

#endif //BBMOUSE
