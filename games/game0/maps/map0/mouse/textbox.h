#include "engine/data/bbHome.h"

bbFlag Textbox_IsOver (bbMouse* mouse, bbWidgets* widgets, bbWidget* widget)
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

bbFlag Textbox_LeftDown (void* Mouse, void* Widgets, void* Widget, void*
Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    bbMouse* mouse = Mouse;
    bbWidgets* widgets = Widgets;

    bbVPool* pool = widgets->pool;
    bbPool_Handle handle;

    bbVPool_reverseLookup(pool, widget, &handle);
    widget->mtable.hover = true;
    home.private.widgets.textbox = widget;
    return Success;
}
