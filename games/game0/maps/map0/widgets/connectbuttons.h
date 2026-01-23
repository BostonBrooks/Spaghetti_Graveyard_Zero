#include "engine/data/bbHome.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/network/bbNetworkApp.h"
#include "engine/userinterface/bbWidget.h"

bbFlag testOnClick(void* self)
{
    bbHere()
    return Success;
}

bbFlag testOnUnClick(void* self)
{
    bbHere()
    return Success;
}
//look up textboxes and use their addresses, then you will have to update their sfText
bbFlag connectOnClick(void* self)
{
bbHere()

    bbWidget* widget = self;
    // TODO: bbFlag bbConnect(void* network); in bbNetworkApp.c
    // widget->isFrozen = true;
    bbPool_Handle handle;
    bbWidgets* widgets = &home.private.UI.widgets;
    bbWidget *addressWidget, *portWidget;
    bbDictionary_lookup(widgets->dict, "IP_ADDRESS",&handle);
    bbVPool_lookup(widgets->pool, (void**)&addressWidget, handle);

    bbDictionary_lookup(widgets->dict, "IP_PORT",&handle);
    bbVPool_lookup(widgets->pool, (void**)&portWidget, handle);

    char* address = addressWidget->typeData.textBox.string;
    char* port = portWidget->typeData.textBox.string;
    bbNetworkApp_connect(&home.private.network, address, port);

    sfText_setString(addressWidget->typeData.textBox.text, address);
    sfText_setString(portWidget->typeData.textBox.text, port);

    return Success;
}

bbFlag disconnectOnClick(void* self)
{
bbHere()
   /*
    bbWidget* widget = self;
    widget->isFrozen = true;
    home.private.network.quit = true;
*/
    return Success;
}


bbFlag launchServer(void* self)
{
#ifdef __linux__

    system("gnome-terminal -- bash -c \"./server.sh\"");
#else
    system("start server.cmd");
#endif
    return Success;
}

bbFlag ConnectButton_Constructor (bbWidget** self, void* Graphics,
                         bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{
    bbWidget* widget;
    bbGraphicsApp* graphics = Graphics;
    bbFlag flag =  bbWidget_newEmpty(&widget, widgets, parent);
    bbAssert(widget != NULL, "null address\n");

    bbStr_setStr(widget->key, "Connect", 64);
    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = 74 * SCREEN_PPP;
    rect.height = 22 * SCREEN_PPP;

    widget->rect = rect;

    bbPool_Handle drawfunctionHandle;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSTATE",
                    &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->compositions->dictionary, "BUTTON",
                        &widget->frames[0].handle);


    widget->frames[0].offset.x = 0;
    widget->frames[0].offset.y = 0;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETTEXT",
                    &drawfunctionHandle);
    widget->frames[1].drawfunction = drawfunctionHandle.u64;
    widget->frames[1].offset.x = 3*SCREEN_PPP;
    widget->frames[1].offset.y = 3*SCREEN_PPP;




    widget->state = bbWidgetState_Default;

    int funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver, "CONNECT");
    widget->mtable.isOver = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseEnter, "CONNECT");
    widget->mtable.Enter = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeave, "CONNECT");
    widget->mtable.Leave = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDown,"CONNECT");
    widget->mtable.LeftDown = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftUp,"CONNECT");
    widget->mtable.LeftUp = funcInt;
    widget->mtable.LeftDrag = -1;

    widget->mtable.MouseIcon = 87;
    widget->mtable.DragIcon = -1;

    widget->mtable.OnClick = connectOnClick;
    widget->mtable.OnUnClick = NULL;


    for (I32 i = 3; i < FRAMES_PER_WIDGET; i++) {
        widget->frames[i].drawfunction = -1;
    }

    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "CONNECT", handle);

    *self = widget;


    return Success;
}

bbFlag CONNECTBUTTON_Constructor2 (bbWidget** self,
                            bbWidgets* widgets,
                            bbWidget* parent,
                            char* name,
                            bbScreenPoints screen_coords,
                            bbGraphicsApp* graphics
                            )
{

    bbWidget* widget;
    bbWidget_newEmpty2(&widget, widgets, parent, name);

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = 74 * SCREEN_PPP;
    rect.height = 22 * SCREEN_PPP;

    widget->rect = rect;


    bbStr_setStr(widget->key, "Connect", 64);

    bbPool_Handle drawfunctionHandle;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSTATE",
                    &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->compositions->dictionary, "BUTTON",
                        &widget->frames[0].handle);


    widget->frames[0].offset.x = 0;
    widget->frames[0].offset.y = 0;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETTEXT",
                    &drawfunctionHandle);
    widget->frames[1].drawfunction = drawfunctionHandle.u64;
    widget->frames[1].offset.x = 3*SCREEN_PPP;
    widget->frames[1].offset.y = 3*SCREEN_PPP;

    widget->state = bbWidgetState_Default;
    widget->state = bbWidgetState_Default;

    int funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver, "CONNECT");
    widget->mtable.isOver = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseEnter, "CONNECT");
    widget->mtable.Enter = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeave, "CONNECT");
    widget->mtable.Leave = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDown,"CONNECT");
    widget->mtable.LeftDown = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftUp,"CONNECT");
    widget->mtable.LeftUp = funcInt;
    widget->mtable.LeftDrag = -1;

    widget->mtable.MouseIcon = 87;
    widget->mtable.DragIcon = -1;

    widget->mtable.OnClick = connectOnClick;
    widget->mtable.OnUnClick = NULL;

    *self = widget;

    return Success;
}

bbFlag DisConnectButton_Constructor (bbWidget** self, void* Graphics,
                         bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{
    bbWidget* widget;
    bbGraphicsApp* graphics = Graphics;
    bbFlag flag =  bbWidget_newEmpty(&widget, widgets, parent);
    bbAssert(widget != NULL, "null address\n");

    bbStr_setStr(widget->key, "Connect", 64);
    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = 74 * SCREEN_PPP;
    rect.height = 22 * SCREEN_PPP;

    widget->rect = rect;

    bbPool_Handle drawfunctionHandle;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSTATE",
                    &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->compositions->dictionary, "BUTTON",
                        &widget->frames[0].handle);


    widget->frames[0].offset.x = 0;
    widget->frames[0].offset.y = 0;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETTEXT",
                    &drawfunctionHandle);
    widget->frames[1].drawfunction = drawfunctionHandle.u64;
    widget->frames[1].offset.x = 3*SCREEN_PPP;
    widget->frames[1].offset.y = 3*SCREEN_PPP;




    widget->state = bbWidgetState_Default;

    int funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver, "CONNECT");
    widget->mtable.isOver = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseEnter, "CONNECT");
    widget->mtable.Enter = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeave, "CONNECT");
    widget->mtable.Leave = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDown,"CONNECT");
    widget->mtable.LeftDown = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftUp,"CONNECT");
    widget->mtable.LeftUp = funcInt;
    widget->mtable.LeftDrag = -1;

    widget->mtable.MouseIcon = 87;
    widget->mtable.DragIcon = -1;

    widget->mtable.OnClick = disconnectOnClick;
    widget->mtable.OnUnClick = NULL;


    for (I32 i = 3; i < FRAMES_PER_WIDGET; i++) {
        widget->frames[i].drawfunction = -1;
    }

    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "DISCONNECT", handle);

    widget->isFrozen = true;

    bbStr_setStr(widget->key, "Disconnect", 64);

    *self = widget;

    return Success;

}

bbFlag DISCONNECTBUTTON_Constructor2 (bbWidget** self,
                            bbWidgets* widgets,
                            bbWidget* parent,
                            char* name,
                            bbScreenPoints screen_coords,
                            bbGraphicsApp* graphics
                            )
{
    bbWidget* widget;
    bbWidget_newEmpty2(&widget, widgets, parent, name);

    bbStr_setStr(widget->key, "Disconnect", 64);
    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = 74 * SCREEN_PPP;
    rect.height = 22 * SCREEN_PPP;

    widget->rect = rect;

    bbPool_Handle drawfunctionHandle;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSTATE",
                    &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->compositions->dictionary, "BUTTON",
                        &widget->frames[0].handle);


    widget->frames[0].offset.x = 0;
    widget->frames[0].offset.y = 0;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETTEXT",
                    &drawfunctionHandle);
    widget->frames[1].drawfunction = drawfunctionHandle.u64;
    widget->frames[1].offset.x = 3*SCREEN_PPP;
    widget->frames[1].offset.y = 3*SCREEN_PPP;




    widget->state = bbWidgetState_Default;

    int funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver, "CONNECT");
    widget->mtable.isOver = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseEnter, "CONNECT");
    widget->mtable.Enter = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeave, "CONNECT");
    widget->mtable.Leave = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDown,"CONNECT");
    widget->mtable.LeftDown = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftUp,"CONNECT");
    widget->mtable.LeftUp = funcInt;
    widget->mtable.LeftDrag = -1;

    widget->mtable.MouseIcon = 87;
    widget->mtable.DragIcon = -1;

    widget->mtable.OnClick = disconnectOnClick;
    widget->mtable.OnUnClick = NULL;

    widget->isFrozen = true;


    *self = widget;

    return Success;
}

bbFlag GoOfflineButton_Constructor (bbWidget** self, void* Graphics,
                         bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{
    bbWidget* widget;
    bbGraphicsApp* graphics = Graphics;
    bbFlag flag =  bbWidget_newEmpty(&widget, widgets, parent);
    bbAssert(widget != NULL, "null address\n");

    bbStr_setStr(widget->key, "Connect", 64);
    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = 74 * SCREEN_PPP;
    rect.height = 22 * SCREEN_PPP;

    widget->rect = rect;

    bbPool_Handle drawfunctionHandle;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSTATE",
                    &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->compositions->dictionary, "BUTTON",
                        &widget->frames[0].handle);


    widget->frames[0].offset.x = 0;
    widget->frames[0].offset.y = 0;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETTEXT",
                    &drawfunctionHandle);
    widget->frames[1].drawfunction = drawfunctionHandle.u64;
    widget->frames[1].offset.x = 3*SCREEN_PPP;
    widget->frames[1].offset.y = 3*SCREEN_PPP;




    widget->state = bbWidgetState_Default;

    int funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver, "CONNECT");
    widget->mtable.isOver = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseEnter, "CONNECT");
    widget->mtable.Enter = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeave, "CONNECT");
    widget->mtable.Leave = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDown,"CONNECT");
    widget->mtable.LeftDown = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftUp,"CONNECT");
    widget->mtable.LeftUp = funcInt;
    widget->mtable.LeftDrag = -1;

    widget->mtable.MouseIcon = 87;
    widget->mtable.DragIcon = -1;

    widget->mtable.OnClick = NULL;
    widget->mtable.OnUnClick = launchServer;


    for (I32 i = 3; i < FRAMES_PER_WIDGET; i++) {
        widget->frames[i].drawfunction = -1;
    }

    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "NEWSERVER", handle);


    bbStr_setStr(widget->key, "New Server", 64);





    *self = widget;
    return Success;

}

bbFlag NEWSERVER_Constructor2 (bbWidget** self,
                            bbWidgets* widgets,
                            bbWidget* parent,
                            char* name,
                            bbScreenPoints screen_coords,
                            bbGraphicsApp* graphics
                            )
{
    bbWidget* widget;
    bbWidget_newEmpty2(&widget, widgets, parent, name);

    bbStr_setStr(widget->key, "New Server", 64);

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = 74 * SCREEN_PPP;
    rect.height = 22 * SCREEN_PPP;

    widget->rect = rect;

    bbPool_Handle drawfunctionHandle;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSTATE",
                    &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->compositions->dictionary, "BUTTON",
                        &widget->frames[0].handle);


    widget->frames[0].offset.x = 0;
    widget->frames[0].offset.y = 0;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETTEXT",
                    &drawfunctionHandle);
    widget->frames[1].drawfunction = drawfunctionHandle.u64;
    widget->frames[1].offset.x = 3*SCREEN_PPP;
    widget->frames[1].offset.y = 3*SCREEN_PPP;




    widget->state = bbWidgetState_Default;

    int funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver, "CONNECT");
    widget->mtable.isOver = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseEnter, "CONNECT");
    widget->mtable.Enter = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeave, "CONNECT");
    widget->mtable.Leave = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDown,"CONNECT");
    widget->mtable.LeftDown = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftUp,"CONNECT");
    widget->mtable.LeftUp = funcInt;
    widget->mtable.LeftDrag = -1;

    widget->mtable.MouseIcon = 87;
    widget->mtable.DragIcon = -1;

    widget->mtable.OnClick = NULL;
    widget->mtable.OnUnClick = launchServer;

    *self = widget;
    return Success;
}