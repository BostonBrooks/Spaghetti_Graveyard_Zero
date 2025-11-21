#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"
#include "engine/widgets/bbWidgetFunctions.h"


bbFlag SpellBar_LeftDown (void* mouse, void* widgets, void* widget, void*
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

    //left = 293, right = 303, top = 0, bottom = 10 in pixels

    if (relativePos.x > 293 * POINTS_PER_PIXEL && relativePos.x <= 303 * POINTS_PER_PIXEL
        && relativePos.y > 0 * POINTS_PER_PIXEL && relativePos.y < 11 *
                                                                   POINTS_PER_PIXEL){

        bbWidget* SpellMenu = Widgets->spellMenu;

        SpellMenu->tree.visible = true;
        SpellMenu->tree.childrenvisible = true;

        bbDebug("clicked spells bar top right\n");
    }


    return Success;
}