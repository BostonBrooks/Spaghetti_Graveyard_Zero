#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

//typedef bbFlag bbMouse_IsOver (void* mouse, void* widgets, void* widget);
bbFlag ConnectButton_IsOver (bbMouse* mouse, bbWidgets* widgets, bbWidget* widget)
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

bbFlag ConnectButton_Enter (void* mouse, void* widgets, void* Widget, void* Graphics)
{

    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;


    widget->mtable.hover = true;
    widget->state = bbWidgetState_Hover;
    return Success;
}

//typedef bbFlag bbMouse_Leave (void* mouse, void* widgets, void* widget, void* graphics);
bbFlag ConnectButton_Leave (void* mouse, void* widgets, void* Widget, void* Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;


    widget->mtable.hover = false;
    widget->state = bbWidgetState_Default;
    return Success;
}

//typedef bbFlag bbMouse_LeftDown (void* mouse, void* widgets, void* widget,
// void* graphics);
bbFlag ConnectButton_LeftDown (void* Mouse, void* Widgets, void* Widget, void*
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
    mouse->selected = handle;
    widget->state = bbWidgetState_Click;

    if (widget->mtable.OnClick!=NULL && widget->isFrozen == false)
    {
        widget->mtable.OnClick(widget);
    }
    return Success;
}

//typedef bbFlag bbMouse_LeftUp (void* mouse, void* widgets, void* widget, void*
// graphics);
bbFlag ConnectButton_LeftUp (void* Mouse, void* Widgets, void* Widget, void* Graphics)
{
    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    bbMouse* mouse = Mouse;
    bbWidgets* widgets = Widgets;


    mouse->selected = widgets->pool->null;

    if (widget->mtable.hover) {

        widget->state = bbWidgetState_Hover;

        if (widget->mtable.OnUnClick!=NULL && widget->isFrozen == false)
        {
            widget->mtable.OnUnClick(widget);
        }
    } else {

        widget->state = bbWidgetState_Default;
    }

    widget->mtable.hover = false;
    return Success;
}
