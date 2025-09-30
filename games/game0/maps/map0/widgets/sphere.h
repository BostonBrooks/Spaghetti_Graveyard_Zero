#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"
#include "engine/widgets/bbWidgetFunctions.h"

//typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
//                                     bbWidgets* widgets, bbScreenPoints
//                                     screen_coords, bbWidget* parent);

bbFlag Sphere_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent){
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

bbFlag SPHERE_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{


    bbWidget* widget; bbPool_Handle widgetHandle;
    bbFlag flag = bbVPool_alloc(widgets->pool, (void**) &widget);

    bbAssert(widget != NULL, "null address\n");
    bbVPool_reverseLookup(widgets->pool, widget, &widgetHandle);
    widget->tree.visible = true;
    widget->tree.childrenvisible = true;
    //  widget->ftable.MouseHandler =
    //  bbWidgetFunctions_getInt(bbWidgetFunctions0* functions,
    //    WidgetFunctionType fnType, char * key);
    widget->ftable.MouseHandler = 0;

    if (parent == NULL){
        widgets->tree->root = widgetHandle;
    } else {
        bbTreeNode_setParent(widgets->tree, widget, parent);
    }

    for (I32 i = 0; i < FRAMES_PER_WIDGET; i++) {
        widget->frames[i].drawfunction = -1;
    }
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

    int funcInt = bbWidgetFunctions_getInt(widgets->functions,
    WidgetMouseHandler, "SPHERE");

    bbDebug("funcInt = %d\n", funcInt);

    widget->ftable.MouseHandler = funcInt;

    widget->frames[0].offset.x = 0;
    widget->frames[0].offset.y = 0;

    for (I32 i = 1; i < FRAMES_PER_WIDGET; i++) {
        widget->frames[i].drawfunction = -1;
    }

    *self = widget;

    bbAssert(widget != NULL, "null address\n");

    return Success;
}

//If the mouse is over the widget, move the widget.
bbFlag SPHERE_Mouse (bbWidget* widget, void* void_mouseEvent)
{
    bbDebug("SPHERE Mouse\n");


    return Continue;
}