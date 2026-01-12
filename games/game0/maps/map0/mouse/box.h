#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

//typedef bbFlag bbMouse_IsOver (void* mouse, void* widgets, void* widget);
bbFlag Box_IsOver (bbMouse* mouse, bbWidgets* widgets, bbWidget* widget)
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

bbFlag Box_Enter (void* mouse, void* widgets, void* Widget, void* graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* Graphics = graphics;
    bbDictionary_lookup(Graphics->sprites->dictionary,
                        "BOX", &widget->frames[0].handle);

    widget->mtable.hover = true;
    bbDebug("Mouse enters box\n");
    return Success;
}

//typedef bbFlag bbMouse_Leave (void* mouse, void* widgets, void* widget, void* graphics);
bbFlag Box_Leave (void* mouse, void* widgets, void* Widget, void* graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* Graphics = graphics;
    bbDictionary_lookup(Graphics->sprites->dictionary,
                        "BOX", &widget->frames[0].handle);

    widget->mtable.hover = false;
    bbDebug("Mouse leaves box\n");
    return Success;
}

//typedef bbFlag bbMouse_LeftDown (void* mouse, void* widgets, void* widget,
// void* graphics);
bbFlag Box_LeftDown (void* Mouse, void* Widgets, void* Widget, void*
Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    bbMouse* mouse = Mouse;
    bbWidgets* widgets = Widgets;
    bbVPool* pool = widgets->pool;
    bbPool_Handle handle;
    bbDictionary_lookup(graphics->sprites->dictionary,
                        "BOX", &widget->frames[0].handle);

    bbVPool_reverseLookup(pool, widget, &handle);
    widget->mtable.hover = true;
    mouse->selected = handle;

    bbScreenPoints dragOrigin;
    dragOrigin.x = mouse->position.x - widget->rect.left;
    dragOrigin.y = mouse->position.y - widget->rect.top;
    mouse->dragOrigin = dragOrigin;

    bbDebug("Mouse left button down on box\n");
    return Success;
}

//typedef bbFlag bbMouse_LeftUp (void* mouse, void* widgets, void* widget, void*
// graphics);
bbFlag Box_LeftUp (void* Mouse, void* Widgets, void* Widget, void* Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    bbWidgets* widgets = Widgets;
    bbMouse* mouse = Mouse;

    mouse->selected = widgets->pool->null;

    if (widget->mtable.hover) {

        bbDictionary_lookup(graphics->sprites->dictionary,
                            "BOX", &widget->frames[0].handle);

    } else {
        bbDictionary_lookup(graphics->sprites->dictionary,
                            "BOX", &widget->frames[0].handle);
    }

    widget->mtable.hover = false;
    bbDebug("Mouse left button up on box\n");
    return Success;
}


//typedef bbFlag bbMouse_LeftDrag (void* mouse, void* widgets, void* widget,
//                                 void* graphics);

bbFlag Box_LeftDrag (void* Mouse, void* widgets, void* Widget, void* graphics) {

    bbMouse* mouse = Mouse;
    bbWidget* widget = (bbWidget*)Widget;
    bbScreenPoints newPos;
    newPos.x = mouse->position.x - mouse->dragOrigin.x;
    newPos.y = mouse->position.y - mouse->dragOrigin.y;

    widget->rect.left = newPos.x;
    widget->rect.top = newPos.y;


    bbDebug("Mouse left button drag on box\n");
    return Success;
}