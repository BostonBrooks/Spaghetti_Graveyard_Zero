//sphere is a test bbWidget. when the mouse passes over the object, the
// object teleports to a new location.

#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"
#include "engine/widgets/bbWidgetFunctions.h"

//typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
//                                     bbWidgets* widgets, bbScreenPoints
//                                     screen_coords, bbWidget* parent);


bbFlag SPHERE_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{
    bbWidget* widget;
    bbFlag flag =  bbWidget_newEmpty(&widget, widgets, parent);
    bbAssert(widget != NULL, "null address\n");


    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 52;
    rect.height = SCREEN_PPP * 52;

    widget->rect = rect;

    bbGraphics* Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPHERE",
                        &widget->frames[0].handle);

    int funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver, "TELEPORT");
    widget->mtable.isOver = funcInt;

    widget->frames[0].offset.x = 0;
    widget->frames[0].offset.y = 0;


    *self = widget;


    return Success;
}

