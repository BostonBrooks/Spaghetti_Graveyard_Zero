#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

bbFlag AnimationTest_Constructor (bbWidget** self, void* graphics,bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{
    bbWidget* widget;
    bbFlag flag =  bbWidget_newEmpty(&widget, widgets, parent);


    bbScreenPointsRect rect;

    rect.left = 30*POINTS_PER_PIXEL;
    rect.top =  100*POINTS_PER_PIXEL;
    rect.width = 0;
    rect.height = 0;

    widget->rect = rect;

    bbGraphicsApp* Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
   // bbDictionary_lookup(Graphics->drawfunctions->dictionary, "WIDGETSPRITE",
     //                   &drawfunctionHandle);
    //widget->frames[0].drawfunction = drawfunctionHandle.u64;
    //widget->frames[0].framerate = 1;
    //widget->frames[0].handle.u64 = 154;


    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "WIDGETANIMATIONNETTIME",
                        &drawfunctionHandle);
    widget->frames[1].drawfunction = drawfunctionHandle.u64;
    widget->frames[1].framerate = 1;
    bbDictionary_lookup(Graphics->animations->dictionary, "CLOCK",
                        &widget->frames[1].handle);

    *self = widget;
    return Success;
}