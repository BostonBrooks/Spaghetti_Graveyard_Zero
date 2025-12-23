#include "engine/geometry/bbCoordinates.h"
#include "engine/userinterface/bbWidget.h"

bbFlag ConnectButton_Constructor (bbWidget** self, void* Graphics,
                         bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{
    bbWidget* widget;
    bbFlag flag =  bbWidget_newEmpty(&widget, widgets, parent);
    bbAssert(widget != NULL, "null address\n");

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = 74 * SCREEN_PPP;
    rect.height = 22 * SCREEN_PPP;

    widget->rect = rect;

    bbGraphics* graphics = Graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->sprites->dictionary, "CONNECT_DEFAULT",
                        &widget->frames[0].handle);

    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "CONNECT_DEFAULT", handle);

    *self = widget;

    return Success;
}

