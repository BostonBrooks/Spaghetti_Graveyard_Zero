#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"
#include "engine/widgets/bbWidgetFunctions.h"

bbFlag Spellbar_Constructor (bbWidget** self, void* graphics,
                        bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {


    bbWidget *widget;
    bbFlag flag = bbWidget_newEmpty(&widget, widgets, parent);

    bbAssert(widget != NULL, "null address\n");

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 52;
    rect.height = SCREEN_PPP * 52;

    widget->rect = rect;

    bbGraphics *Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL1",
                        &widget->frames[0].handle);


    *self = widget;

}