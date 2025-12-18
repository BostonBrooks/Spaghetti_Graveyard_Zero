#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbVPool.h"
#include "engine/userinterface/bbWidgetFunctions.h"
//typedef bbFlag bbMouse_LeftDown (void* mouse, void* widgets, void* widget,
// void* graphics);
bbFlag ConnectIcon_LeftDown (void* Mouse, void* Widgets, void* Widget, void*
Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphics* graphics = Graphics;
    bbMouse* mouse = Mouse;
    bbWidgets* widgets = Widgets;

    bbVPool* pool = widgets->pool;
    bbPool_Handle handle = widget->tree.children.head;

    bbWidget* ConnectMenu;
    bbVPool_lookup(pool, (void**)&ConnectMenu,handle);
    ConnectMenu->tree.visible = true;
    ConnectMenu->tree.childrenvisible = true;


    return Success;
}