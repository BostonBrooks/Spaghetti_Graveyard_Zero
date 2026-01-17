#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

bbFlag TopLeft_Constructor (bbWidget** self, void* Graphics,
                        bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{
    bbWidget *widget;
    bbFlag flag = bbWidget_newEmpty(&widget, widgets, parent);

    bbAssert(widget != NULL, "null address\n");

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 292;
    rect.height = SCREEN_PPP * 47;

    widget->mtable.MouseIcon = 89;

    widget->rect = rect;

    bbGraphicsApp *graphics = Graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->sprites->dictionary, "TOPLEFT",
                        &widget->frames[0].handle);


    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "TOPLEFT", handle);

    *self = widget;
    return Success;
}