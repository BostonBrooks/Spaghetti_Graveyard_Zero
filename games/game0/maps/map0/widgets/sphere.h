#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"

//typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
//                                     void* widgets, bbScreenPoints
//                                     screen_coords, bbWidget* parent);

bbFlag Sphere_Constructor (bbWidget** self, void* graphics,
                           void* widgets, bbScreenPoints screen_coords, bbWidget* parent){
    bbWidget* widget;

    bbWidget_newEmpty(&widget, widgets, parent);

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = 1;
    rect.height = 1;

    widget->rect = rect;

    bbGraphics* Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPHERE",
                        &widget->frames[0].handle);

    widget->frames[0].offset.x = 0;
    widget->frames[0].offset.y = 0;

    for (I32 i = 1; i < FRAMES_PER_WIDGET; i++) {
        widget->frames[i].drawfunction = -1;
    }

    *self = widget;

    return Success;
}