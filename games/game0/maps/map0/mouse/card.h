#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"
#include "engine/widgets/bbWidgetFunctions.h"

//typedef bbFlag bbMouse_IsOver (void* mouse, void* widgets, void* widget);
bbFlag Card_IsOver (bbMouse* mouse, bbWidgets* widgets, bbWidget* widget)
{
    bbScreenPointsRect rect = widget->rect;
    bbScreenPoints point = mouse->position;

    if (bbScreenPoints_inScreenPointsRect(point, rect)){
        bbVPool* pool = widgets->pool;
        bbPool_Handle handle;
        bbVPool_reverseLookup(pool,widget,&handle);

        if(bbVPool_handleIsEqual(pool,handle,mouse->selected)) return Continue;

        if (!bbVPool_handleIsEqual(pool,handle,mouse->isOver))
        {

            bbHere();
            mouse->wasOver = mouse->isOver;
            mouse->isOver = handle;
        }
        return Break;
    }
    return Continue;
}


//typedef bbFlag bbMouse_Enter (void* mouse, void* widgets, void* widget, void* graphics);

bbFlag Card_Enter (void* mouse, void* widgets, void* widget, void* graphics)
{
    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbDictionary_lookup(Graphics->sprites->dictionary,
                        "ASPADES", &Widget->frames[0].handle);

    Widget->mtable.hover = true;
    bbDebug("Mouse enters card\n");
    return Success;
}

//typedef bbFlag bbMouse_Leave (void* mouse, void* widgets, void* widget, void* graphics);
bbFlag Card_Leave (void* mouse, void* widgets, void* widget, void* graphics)
{
    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbDictionary_lookup(Graphics->sprites->dictionary,
                        "ASPADES", &Widget->frames[0].handle);

    Widget->mtable.hover = false;
    bbDebug("Mouse leaves card\n");
    return Success;
}

//typedef bbFlag bbMouse_LeftDown (void* mouse, void* widgets, void* widget,
// void* graphics);
bbFlag Card_LeftDown (void* mouse, void* widgets, void* widget, void*
graphics)
{
    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbMouse* Mouse = mouse;
    bbWidgets* Widgets = widgets;
    bbVPool* pool = Widgets->pool;
    bbPool_Handle handle;
    bbDictionary_lookup(Graphics->sprites->dictionary,
                        "ASPADES", &Widget->frames[0].handle);

    bbVPool_reverseLookup(pool, widget, &handle);
    Widget->mtable.hover = true;
    Mouse->selected = handle;

    bbScreenPoints dragOrigin;
    dragOrigin.x = Mouse->position.x - Widget->rect.left;
    dragOrigin.y = Mouse->position.y - Widget->rect.top;
    Mouse->dragOrigin = dragOrigin;

    bbDebug("Mouse left button down on carde\n");
    return Success;
}

//typedef bbFlag bbMouse_LeftUp (void* mouse, void* widgets, void* widget, void*
// graphics);
bbFlag Card_LeftUp (void* mouse, void* widgets, void* widget, void* graphics)
{
    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbWidgets* Widgets = widgets;

    bbMouse* Mouse = mouse;
    Mouse->selected = Widgets->pool->null;

    if (Widget->mtable.hover) {

        bbDictionary_lookup(Graphics->sprites->dictionary,
                            "ASPADES", &Widget->frames[0].handle);

    } else {
        bbDictionary_lookup(Graphics->sprites->dictionary,
                            "ASPADES", &Widget->frames[0].handle);
    }

    Widget->mtable.hover = false;
    bbDebug("Mouse left button up on card\n");
    return Success;
}


//typedef bbFlag bbMouse_LeftDrag (void* mouse, void* widgets, void* widget,
//                                 void* graphics);

bbFlag Card_LeftDrag (void* mouse, void* widgets, void* widget, void*
graphics) {

    /*
    bbMouse* Mouse = mouse;
    bbWidget* Widget = (bbWidget*)widget;
    bbScreenPoints newPos;
    newPos.x = Mouse->position.x - Mouse->dragOrigin.x;
    newPos.y = Mouse->position.y - Mouse->dragOrigin.y;

    Widget->rect.left = newPos.x;
    Widget->rect.top = newPos.y;
*/

    bbDebug("Mouse left button drag on card\n");
    return Success;
}