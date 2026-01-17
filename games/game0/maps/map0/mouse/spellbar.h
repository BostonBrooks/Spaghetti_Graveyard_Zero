#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"


bbFlag SpellBar_LeftDown (void* Mouse, void* Widgets, void* Widget, void*
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

    //left = 293, right = 303, top = 0, bottom = 10 in pixels

    if (relativePos.x > 293 * POINTS_PER_PIXEL && relativePos.x <= 303 * POINTS_PER_PIXEL
        && relativePos.y > 0 * POINTS_PER_PIXEL && relativePos.y < 11 *
                                                                   POINTS_PER_PIXEL){

        bbWidget* SpellMenu = widgets->spellMenu;

        SpellMenu->tree.visible = true;
        SpellMenu->tree.childrenvisible = true;

    }


    return Success;
}