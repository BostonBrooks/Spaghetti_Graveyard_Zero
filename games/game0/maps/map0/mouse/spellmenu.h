#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"
#include "engine/widgets/bbWidgetFunctions.h"


bbFlag SpellMenu_LeftDown (void* mouse, void* widgets, void* widget, void*
graphics)
{
    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbMouse* Mouse = mouse;
    bbWidgets* Widgets = widgets;
    bbVPool* pool = Widgets->pool;
    bbPool_Handle handle;

    bbScreenPoints mousePos;
    bbScreenPoints widgetPos;
    bbScreenPoints relativePos;

    mousePos = Mouse->position;
    widgetPos.x = Widget->rect.left;
    widgetPos.y = Widget->rect.top;

    relativePos.x = mousePos.x - widgetPos.x;
    relativePos.y = mousePos.y - widgetPos.y;

    //left = 360, right = 371, top = 0, bottom = 10 in pixels

    if (relativePos.x > 360 * POINTS_PER_PIXEL && relativePos.x <= 371 * POINTS_PER_PIXEL
         && relativePos.y > 0 * POINTS_PER_PIXEL && relativePos.y < 11 *
         POINTS_PER_PIXEL){
        Widget->tree.visible = false;
        Widget->tree.childrenvisible = false;
    }

    bbDebug("Spell Select Menu Closed\n");
    return Success;
}