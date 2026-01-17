#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

//typedef bbFlag bbMouse_IsOver (void* mouse, void* widgets, void* widget);
bbFlag Button_IsOver (bbMouse* mouse, bbWidgets* widgets, bbWidget* widget)
{
    bbScreenPointsRect rect = widget->rect;
    bbScreenPoints point = mouse->position;

    if (bbScreenPoints_inScreenPointsRect(point, rect)){
        bbVPool* pool = widgets->pool;
        bbPool_Handle handle;
        bbVPool_reverseLookup(pool,widget,&handle);

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

bbFlag Button_Enter (void* mouse, void* widgets, void* Widget, void* Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    bbDictionary_lookup(graphics->sprites->dictionary,
                        "BUTTON_HOVER", &widget->frames[0].handle);

    widget->mtable.hover = true;
    return Success;
}

//typedef bbFlag bbMouse_Leave (void* mouse, void* widgets, void* widget, void* graphics);
bbFlag Button_Leave (void* mouse, void* widgets, void* Widget, void* Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    bbDictionary_lookup(graphics->sprites->dictionary,
                        "BUTTON_DEFAULT", &widget->frames[0].handle);

    widget->mtable.hover = false;
    return Success;
}

//typedef bbFlag bbMouse_LeftDown (void* mouse, void* widgets, void* widget,
// void* graphics);
bbFlag Button_LeftDown (void* Mouse, void* Widgets, void* Widget, void*
Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    bbMouse* mouse = Mouse;
    bbWidgets* widgets = Widgets;

    bbVPool* pool = widgets->pool;
    bbPool_Handle handle;
    bbDictionary_lookup(graphics->sprites->dictionary,
                        "BUTTON_CLICK", &widget->frames[0].handle);

    bbVPool_reverseLookup(pool, widget, &handle);
    widget->mtable.hover = true;
    mouse->selected = handle;
    return Success;
}

//typedef bbFlag bbMouse_LeftUp (void* mouse, void* widgets, void* widget, void*
// graphics);
bbFlag Button_LeftUp (void* Mouse, void* Widgets, void* Widget, void* Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    bbMouse* mouse = Mouse;
    bbWidgets* widgets = Widgets;

    mouse->selected = widgets->pool->null;

    if (widget->mtable.hover) {

        bbDictionary_lookup(graphics->sprites->dictionary,
                            "BUTTON_HOVER", &widget->frames[0].handle);

    } else {
        bbDictionary_lookup(graphics->sprites->dictionary,
                            "BUTTON_DEFAULT", &widget->frames[0].handle);
    }

    widget->mtable.hover = false;
    return Success;
}
