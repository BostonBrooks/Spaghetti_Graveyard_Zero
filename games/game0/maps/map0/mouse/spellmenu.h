#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"


bbFlag SpellMenu_LeftDown (void* Mouse, void* Widgets, void* Widget, void*
Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    bbMouse* mouse = Mouse;
    bbWidgets* widgets = Widgets;

    bbVPool* pool = widgets->pool;
    bbPool_Handle handle;

    bbScreenPoints mousePos;
    bbScreenPoints widgetPos;
    bbScreenPoints relativePos;

    mousePos = mouse->position;
    widgetPos.x = widget->rect.left;
    widgetPos.y = widget->rect.top;

    relativePos.x = mousePos.x - widgetPos.x;
    relativePos.y = mousePos.y - widgetPos.y;

    //left = 360, right = 371, top = 0, bottom = 10 in pixels

    if (relativePos.x > 360 * POINTS_PER_PIXEL && relativePos.x <= 371 * POINTS_PER_PIXEL
         && relativePos.y > 0 * POINTS_PER_PIXEL && relativePos.y < 11 *
         POINTS_PER_PIXEL){
        widget->tree.visible = false;
        widget->tree.childrenvisible = false;
    }

    return Success;
}