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
    bbFlag flag;// = ConnectIcon_Constructor (&ConnectIcon, graphics,widgets, screen_coords, parent);

    flag=  bbWidget_newEmpty(&widget, widgets, parent);

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


    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "LAYERBOUNDARY",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(Graphics->sprites->dictionary, "LAYERBOUNDARY",
                        &widget->frames[0].handle);

    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[1].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(Graphics->sprites->dictionary, "CONNECTMENU",
                        &widget->frames[1].handle);


    widget->ftable.Hide = bbWidgetFunctions_getInt(widgets->functions,WidgetHide ,"CONNECTHIDE");
    widget->ftable.Unhide = bbWidgetFunctions_getInt(widgets->functions,WidgetUnhide ,"CONNECTUNHIDE");

    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "CONNECTMENU", handle);


    bbPool_Handle bounds;
    bounds.i32x2.x = 187*POINTS_PER_PIXEL;
    bounds.i32x2.y = 21*POINTS_PER_PIXEL;

    bbScreenPoints SP;
    bbWidget* IP_widget;
    SP.x = 169*8; SP.y = 166*8;
    bbWidget_constructor(&IP_widget, widgets, graphics,SP, widget, "TEXTBOX");
    bbVPool_reverseLookup(widgets->pool, IP_widget, &handle);
    bbDictionary_add(widgets->dict, "IP_ADDRESS", handle);
	bbWidget_onCommand(IP_widget, widgets, bbWC_setDimensions, bounds);


    bbWidget* Port_widget;
    SP.x = 169*8; SP.y = 208*8;
    bbWidget_constructor(&Port_widget, widgets, graphics,SP, widget, "TEXTBOX");
    bbVPool_reverseLookup(widgets->pool, Port_widget, &handle);
    bbDictionary_add(widgets->dict, "IP_PORT", handle);
	bbWidget_onCommand(Port_widget, widgets, bbWC_setDimensions, bounds);

    bbWidget* connect_button;
    SP.x = 150*8; SP.y = 250*8;
    bbWidget_constructor(&connect_button, widgets, graphics,SP, widget, "CONNECTBUTTON");
    bbVPool_reverseLookup(widgets->pool, Port_widget, &handle);
    bbDictionary_add(widgets->dict, "CONNECT_BUTTON", handle);

    *self = widget;
    return Success;
}

bbFlag ConnectIcon_Constructor (bbWidget** self, void* graphics,
bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{

    bbWidget* widget;
    bbFlag flag =  bbWidget_newEmpty(&widget, widgets, parent);

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
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


    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "CONNECTICON", handle);



    *self = widget;
    return Success;
}

bbFlag Connect_Hide (bbWidget* widget, bbWidgets* widgets)
{
    bbHere()
    bbVPool* pool = widgets->pool;
    bbPool_Handle handle;
    bbDictionary_lookup(widgets->dict,"CONNECTMENU",&handle );
    bbWidget* ConnectMenu;
    bbVPool_lookup(pool, (void**)&ConnectMenu,handle);
    ConnectMenu->tree.visible = false;
    ConnectMenu->tree.childrenvisible = false;
    return Continue;
}
bbFlag Connect_Unhide (bbWidget* widget, bbWidgets* widgets)
{
    bbHere()
    bbVPool* pool = widgets->pool;
    bbPool_Handle handle;

    bbDictionary_lookup(widgets->dict,"CONNECTMENU",&handle );
    bbWidget* ConnectMenu;
    bbVPool_lookup(pool, (void**)&ConnectMenu,handle);
    ConnectMenu->tree.visible = true;
    ConnectMenu->tree.childrenvisible = true;
    return Continue;
}