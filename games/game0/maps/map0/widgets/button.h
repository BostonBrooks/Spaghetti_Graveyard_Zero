//button is a basic UI element

#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

//typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
//                                     bbWidgets* widgets, bbScreenPoints
//                                     screen_coords, bbWidget* parent);



bbFlag Button_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{


    bbWidget* widget; bbPool_Handle widgetHandle;
    bbFlag flag = bbVPool_alloc(widgets->pool, (void**) &widget);

    bbAssert(widget != NULL, "null address\n");
    bbVPool_reverseLookup(widgets->pool, widget, &widgetHandle);
    widget->tree.visible = true;
    widget->tree.childrenvisible = true;

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
    rect.width = SCREEN_PPP * 75;
    rect.height = SCREEN_PPP * 25;

    widget->rect = rect;

    bbGraphicsApp* Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(Graphics->sprites->dictionary, "BUTTON_DEFAULT",
                        &widget->frames[0].handle);

    int funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver, "BUTTON");
    widget->mtable.isOver = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseEnter, "BUTTON");
    widget->mtable.Enter = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeave, "BUTTON");
    widget->mtable.Leave = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDown,"BUTTON");
    widget->mtable.LeftDown = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftUp,"BUTTON");
    widget->mtable.LeftUp = funcInt;
    widget->mtable.LeftDrag = -1;

    widget->mtable.MouseIcon = 87;
    widget->mtable.DragIcon = -1;

    widget->frames[0].offset.x = 0;
    widget->frames[0].offset.y = 0;

    for (I32 i = 1; i < FRAMES_PER_WIDGET; i++) {
        widget->frames[i].drawfunction = -1;
    }

    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "BUTTON", handle);

    *self = widget;


    return Success;
}
