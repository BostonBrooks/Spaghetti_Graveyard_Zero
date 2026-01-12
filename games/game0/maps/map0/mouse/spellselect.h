#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

//typedef bbFlag bbMouse_IsOver (void* mouse, void* widgets, void* widget);
bbFlag SpellSelect_IsOver (bbMouse* mouse, bbWidgets* widgets, bbWidget* widget)
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

            mouse->wasOver = mouse->isOver;
            mouse->isOver = handle;
        }
        return Break;
    }
    return Continue;
}

//typedef bbFlag bbMouse_Enter (void* mouse, void* widgets, void* widget, void* graphics);

bbFlag SpellSelect_Enter (void* mouse, void* widgets, void* Widget, void*
Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    //bbDictionary_lookup(Graphics->sprites->dictionary,
    //                    "ASPADES", &Widget->frames[0].handle);

    widget->mtable.hover = true;
    return Success;
}

//typedef bbFlag bbMouse_Leave (void* mouse, void* widgets, void* widget, void* graphics);
bbFlag SpellSelect_Leave (void* mouse, void* widgets, void* Widget, void*
Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    //bbDictionary_lookup(Graphics->sprites->dictionary,
    //                    "ASPADES", &Widget->frames[0].handle);

    widget->mtable.hover = false;
    return Success;
}

//typedef bbFlag bbMouse_LeftDown (void* mouse, void* widgets, void* widget,
// void* graphics);
bbFlag SpellSelect_LeftDown (void* Mouse, void* Widgets, void* Widget, void*
Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    bbMouse* mouse = Mouse;
    bbWidgets* widgets = Widgets;

    bbVPool* pool = widgets->pool;
    bbPool_Handle handle;
    //bbDictionary_lookup(Graphics->sprites->dictionary,
    //                    "ASPADES", &Widget->frames[0].handle);

    bbVPool_reverseLookup(pool, widget, &handle);
    widget->mtable.hover = true;
    mouse->selected = handle;

    bbScreenPoints dragOrigin;
    dragOrigin.x = mouse->position.x - widget->rect.left;
    dragOrigin.y = mouse->position.y - widget->rect.top;
    mouse->dragOrigin = dragOrigin;

    return Success;
}

//typedef bbFlag bbMouse_LeftUp (void* mouse, void* widgets, void* widget, void*
// graphics);
bbFlag SpellSelect_LeftUp (void* Mouse, void* Widgets, void* Widget, void*
Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    bbMouse* mouse = Mouse;
    bbWidgets* widgets = Widgets;

    bbWidget* target;
    bbVPool_lookup(widgets->pool, (void**)&target, mouse->isOver);
    if (target->type==bbWidgetType_SpellSlot) {
        target->frames[0].handle = widget->frames[0].handle;
        bbStr_setStr(target->key, widget->key, 64);
    }
    mouse->selected = widgets->pool->null;

    if (widget->mtable.hover) {

        //bbDictionary_lookup(Graphics->sprites->dictionary,
        //                    "ASPADES", &Widget->frames[0].handle);

    } else {
        //bbDictionary_lookup(Graphics->sprites->dictionary,
        //                    "ASPADES", &Widget->frames[0].handle);
    }

    //experimental code:


    bbScreenPoints dragged_SP;
    dragged_SP.x = mouse->position.x - mouse->dragOrigin.x;
    dragged_SP.y = mouse->position.y - mouse->dragOrigin.y;
    //Widget->rect.left = dragged_SP.x;
    //Widget->rect.top = dragged_SP.y;


    widget->mtable.hover = false;
    return Success;
}


//typedef bbFlag bbMouse_LeftDrag (void* mouse, void* widgets, void* widget,
//                                 void* graphics);

bbFlag SpellSelect_LeftDrag (void* mouse, void* widgets, void* widget, void*
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
    return Success;
}