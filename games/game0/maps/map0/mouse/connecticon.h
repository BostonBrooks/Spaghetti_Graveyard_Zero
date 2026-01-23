#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbVPool.h"
#include "engine/userinterface/bbWidgetFunctions.h"
#include "engine/data/bbHome.h"
//typedef bbFlag bbMouse_LeftDown (void* mouse, void* widgets, void* widget,
// void* graphics);
bbFlag ConnectIcon_LeftDown (void* Mouse, void* Widgets, void* Widget, void*
Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    bbMouse* mouse = Mouse;
    bbWidgets* widgets = Widgets;

    bbVPool* pool = widgets->pool;
    bbPool_Handle handle;

    bbDictionary_lookup(widgets->dict,"CONNECTMENU",&handle );
    bbWidget* connectMenu;
    bbVPool_lookup(pool, (void**)&connectMenu,handle);
    bool visible = connectMenu->tree.visible;

    if (visible) bbWidget_hide(connectMenu, &home.private.UI.widgets);
    else bbWidget_unhide(connectMenu, &home.private.UI.widgets);


    return Success;
}