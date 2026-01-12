//Box can be clicked and dragged

#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

//typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
//                                     bbWidgets* widgets, bbScreenPoints
//                                     screen_coords, bbWidget* parent);



bbFlag Card_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{


    bbWidget* widget;
    bbFlag flag =  bbWidget_newEmpty(&widget, widgets, parent);
    bbAssert(widget != NULL, "null address\n");

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 69;
    rect.height = SCREEN_PPP * 103;

    widget->rect = rect;

    bbGraphicsApp* Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(Graphics->sprites->dictionary, "ASPADES",
                        &widget->frames[0].handle);

    int funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver,
                                      "CARD");
    widget->mtable.isOver = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseEnter,
                                      "CARD");
    widget->mtable.Enter = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeave,
                                      "CARD");
    widget->mtable.Leave = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDown,"CARD");
    widget->mtable.LeftDown = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftUp,"CARD");
    widget->mtable.LeftUp = funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDrag,"CARD");
    widget->mtable.LeftDrag = funcInt;

    widget->mtable.MouseIcon = 87;
    widget->mtable.DragIcon = 99;

    widget->frames[0].offset.x = 0;
    widget->frames[0].offset.y = 0;


    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "CARD", handle);

    *self = widget;

    return Success;
}
