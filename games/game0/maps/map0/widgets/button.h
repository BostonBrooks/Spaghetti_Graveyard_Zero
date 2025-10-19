//button is a basic UI element

#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"
#include "engine/widgets/bbWidgetFunctions.h"

//typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
//                                     bbWidgets* widgets, bbScreenPoints
//                                     screen_coords, bbWidget* parent);

#ifdef WIDGET_FUNCTIONS

bbFlag Button_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{


    bbWidget* widget; bbPool_Handle widgetHandle;
    bbFlag flag = bbVPool_alloc(widgets->pool, (void**) &widget);

    bbAssert(widget != NULL, "null address\n");
    bbVPool_reverseLookup(widgets->pool, widget, &widgetHandle);
    widget->tree.visible = true;
    widget->tree.childrenvisible = true;

    if (parent == NULL){
        widgets->tree->root = widgetHandle;
    } else {
        bbTreeNode_setParent(widgets->tree, widget, parent);
    }

    for (I32 i = 0; i < FRAMES_PER_WIDGET; i++) {
        widget->frames[i].drawfunction = -1;
    }
    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 75;
    rect.height = SCREEN_PPP * 25;

    widget->rect = rect;

    bbGraphics* Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(Graphics->sprites->dictionary, "BUTTON_DEFAULT",
                        &widget->frames[0].handle);

    int funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver, "BUTTON");
    widget->mtable.isOver = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseEnter, "BUTTON");
    widget->mtable.Enter = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeave, "BUTTON");
    widget->mtable.Leave = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDown,"BUTTON");
    widget->mtable.LeftDown = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftUp,"BUTTON");
    widget->mtable.LeftUp = funcInt;

    widget->mtable.MouseIcon = 87;
    widget->mtable.DragIcon = 97;

    widget->frames[0].offset.x = 0;
    widget->frames[0].offset.y = 0;

    for (I32 i = 1; i < FRAMES_PER_WIDGET; i++) {
        widget->frames[i].drawfunction = -1;
    }

    *self = widget;

    bbAssert(widget != NULL, "null address\n");

    return Success;
}
#endif //WIDGET_FUNCTIONS

#ifdef MOOSE_FUNCTIONS
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

            bbHere();
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
    bbDebug("Mouse enters button\n");
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
    bbDebug("Mouse leaves button\n");
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
    bbDebug("Mouse left button down on viewpoint\n");
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
    bbDebug("Mouse left button up on viewport\n");
    return Success;
}

#endif //MOOSE_FUNCTIONS