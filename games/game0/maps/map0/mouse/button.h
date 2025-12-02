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

bbFlag Button_Enter (void* mouse, void* widgets, void* widget, void* graphics)
{
    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbDictionary_lookup(Graphics->sprites->dictionary,
                        "BUTTON_HOVER", &Widget->frames[0].handle);

    Widget->mtable.hover = true;
    return Success;
}

//typedef bbFlag bbMouse_Leave (void* mouse, void* widgets, void* widget, void* graphics);
bbFlag Button_Leave (void* mouse, void* widgets, void* widget, void* graphics)
{
    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbDictionary_lookup(Graphics->sprites->dictionary,
                        "BUTTON_DEFAULT", &Widget->frames[0].handle);

    Widget->mtable.hover = false;
    return Success;
}

//typedef bbFlag bbMouse_LeftDown (void* mouse, void* widgets, void* widget,
// void* graphics);
bbFlag Button_LeftDown (void* mouse, void* widgets, void* widget, void*
graphics)
{
    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbMouse* Mouse = mouse;
    bbWidgets* Widgets = widgets;
    bbVPool* pool = Widgets->pool;
    bbPool_Handle handle;
    bbDictionary_lookup(Graphics->sprites->dictionary,
                        "BUTTON_CLICK", &Widget->frames[0].handle);

    bbVPool_reverseLookup(pool, widget, &handle);
    Widget->mtable.hover = true;
    Mouse->selected = handle;
    return Success;
}

//typedef bbFlag bbMouse_LeftUp (void* mouse, void* widgets, void* widget, void*
// graphics);
bbFlag Button_LeftUp (void* mouse, void* widgets, void* widget, void* graphics)
{
    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbWidgets* Widgets = widgets;

    bbMouse* Mouse = mouse;
    Mouse->selected = Widgets->pool->null;

    if (Widget->mtable.hover) {

        bbDictionary_lookup(Graphics->sprites->dictionary,
                            "BUTTON_HOVER", &Widget->frames[0].handle);

    } else {
        bbDictionary_lookup(Graphics->sprites->dictionary,
                            "BUTTON_DEFAULT", &Widget->frames[0].handle);
    }

    Widget->mtable.hover = false;
    return Success;
}
