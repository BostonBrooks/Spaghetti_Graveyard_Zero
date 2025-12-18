//type ip and port to connect to server

#include "engine/includes/CSFML.h"
#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"
#include "engine/logic/bbString.h"

//typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
//                                     bbWidgets* widgets, bbScreenPoints
//                                     screen_coords, bbWidget* parent);

bbFlag ConnectIcon_Constructor (bbWidget** self, void* graphics,
bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent);

bbFlag ConnectMenu_Constructor (bbWidget** self, void* graphics,
bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{

    bbWidget *widget, *ConnectIcon;
    bbFlag flag = ConnectIcon_Constructor (&ConnectIcon, graphics,widgets, screen_coords, parent);

    flag=  bbWidget_newEmpty(&widget, widgets, ConnectIcon);

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = 373 * POINTS_PER_PIXEL;
    rect.height = 197 * POINTS_PER_PIXEL;
    widget->rect = rect;

    widget->mtable.MouseIcon = 86;
    int funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver,
                                  "ALWAYS");
    widget->mtable.isOver = funcInt;


    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeftDown,
                                      "SPELLMENU");
    widget->mtable.LeftDown = funcInt;

    bbGraphics* Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(Graphics->sprites->dictionary, "CONNECTMENU",
                        &widget->frames[0].handle);





    *self = widget;
    return Success;
}

bbFlag ConnectIcon_Constructor (bbWidget** self, void* graphics,
bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{

    bbWidget* widget;
    bbFlag flag =  bbWidget_newEmpty(&widget, widgets, parent);

    bbScreenPointsRect rect;

    rect.left = 46 * POINTS_PER_PIXEL;
    rect.top = 11 * POINTS_PER_PIXEL;
    rect.width = 36 * POINTS_PER_PIXEL;
    rect.height = 36 * POINTS_PER_PIXEL;
    widget->rect = rect;


    widget->mtable.MouseIcon = 86;
    int funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver,
                                  "HOVER");
    widget->mtable.isOver = funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeftDown,
                                  "CONNECTICON");
    widget->mtable.LeftDown = funcInt;

    bbGraphics* Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(Graphics->sprites->dictionary, "CONNECT_ICON",
                        &widget->frames[0].handle);

    *self = widget;

    return Success;
}