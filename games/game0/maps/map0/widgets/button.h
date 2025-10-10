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
    //  widget->ftable.MouseHandler =
    //  bbWidgetFunctions_getInt(bbWidgetFunctions0* functions,
    //    WidgetFunctionType fnType, char * key);
    widget->ftable.MouseHandler = 0;

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

    int funcInt = bbWidgetFunctions_getInt(widgets->functions,
    WidgetMouseHandler, "SPHERE");

    bbDebug("funcInt = %d\n", funcInt);

    widget->ftable.MouseHandler = funcInt;

    funcInt = bbMooseFunctions_getInt(&widgets->moose->functions,MooseIsOver, "BUTTON");
    widget->mtable.isOver = funcInt;
    funcInt = bbMooseFunctions_getInt(&widgets->moose->functions,MooseEnter, "BUTTON");
    widget->mtable.Enter = funcInt;
    funcInt = bbMooseFunctions_getInt(&widgets->moose->functions,MooseLeave, "BUTTON");
    widget->mtable.Leave = funcInt;
    funcInt = bbMooseFunctions_getInt(&widgets->moose->functions,
                                      MooseLeftDown,"BUTTON");
    widget->mtable.LeftDown = funcInt;
    funcInt = bbMooseFunctions_getInt(&widgets->moose->functions,
                                      MooseLeftUp,"BUTTON");
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
//typedef bbFlag bbMoose_IsOver (void* moose, void* widgets, void* widget);
bbFlag Button_IsOver (bbMoose* moose, bbWidgets* widgets, bbWidget* widget)
{
    bbScreenPointsRect rect = widget->rect;
    bbScreenPoints point = moose->position;

    if (bbScreenPoints_inScreenPointsRect(point, rect)){
        bbVPool* pool = widgets->pool;
        bbPool_Handle handle;
        bbVPool_reverseLookup(pool,widget,&handle);

        if (!bbVPool_handleIsEqual(pool,handle,moose->isOver))
        {

            bbHere();
            moose->wasOver = moose->isOver;
            moose->isOver = handle;
        }
        return Break;
    }
    return Continue;
}


//typedef bbFlag bbMoose_Enter (void* moose, void* widgets, void* widget, void* graphics);

bbFlag Button_Enter (void* moose, void* widgets, void* widget, void* graphics)
{
    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbDictionary_lookup(Graphics->sprites->dictionary,
        "BUTTON_HOVER", &Widget->frames[0].handle);

    Widget->mtable.hover = true;
    bbDebug("Mouse enters button\n");
    return Success;
}

//typedef bbFlag bbMoose_Leave (void* moose, void* widgets, void* widget, void* graphics);
bbFlag Button_Leave (void* moose, void* widgets, void* widget, void* graphics)
{
    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbDictionary_lookup(Graphics->sprites->dictionary,
        "BUTTON_DEFAULT", &Widget->frames[0].handle);

    Widget->mtable.hover = false;
    bbDebug("Mouse leaves button\n");
    return Success;
}

//typedef bbFlag bbMoose_LeftDown (void* moose, void* widgets, void* widget,
// void* graphics);
bbFlag Button_LeftDown (void* moose, void* widgets, void* widget, void*
graphics)
{
    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbMoose* Moose = moose;
    bbWidgets* Widgets = widgets;
    bbVPool* pool = Widgets->pool;
    bbPool_Handle handle;
    bbDictionary_lookup(Graphics->sprites->dictionary,
                        "BUTTON_CLICK", &Widget->frames[0].handle);

    bbVPool_reverseLookup(pool, widget, &handle);
    Widget->mtable.hover = true;
    Moose->selected = handle;
    bbDebug("Mouse enters button\n");
    return Success;
}

//typedef bbFlag bbMoose_LeftUp (void* moose, void* widgets, void* widget, void*
// graphics);
bbFlag Button_LeftUp (void* moose, void* widgets, void* widget, void* graphics)
{
    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbWidgets* Widgets = widgets;

    bbMoose* Moose = moose;
    Moose->selected = Widgets->pool->null;

    if (Widget->mtable.hover) {

        bbDictionary_lookup(Graphics->sprites->dictionary,
                            "BUTTON_HOVER", &Widget->frames[0].handle);

    } else {
        bbDictionary_lookup(Graphics->sprites->dictionary,
                            "BUTTON_DEFAULT", &Widget->frames[0].handle);
    }

    Widget->mtable.hover = false;
    bbDebug("Mouse leaves button\n");
    return Success;
}

#endif //MOOSE_FUNCTIONS