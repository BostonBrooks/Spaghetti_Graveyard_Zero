#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

bbFlag SPELLSELECT_Constructor2 (bbWidget** self,
                            bbWidgets* widgets,
                            bbWidget* parent,
                            char* name,
                            bbScreenPoints screen_coords,
                            bbGraphicsApp* graphics
                            )
{
    bbHere()
        bbWidget* widget;
    bbWidget_newEmpty2(&widget, widgets, parent, name);
    bbAssert(widget != NULL, "null address\n");

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 36;
    rect.height = SCREEN_PPP * 36;

    widget->rect = rect;

    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL1",
                        &widget->frames[0].handle);

    int funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver,
                                      "SPELLSELECT");

    widget->mtable.isOver = funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseEnter,
                                      "SPELLSELECT");
    widget->mtable.Enter = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeave,
                                      "SPELLSELECT");
    widget->mtable.Leave = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDown,"SPELLSELECT");
    widget->mtable.LeftDown = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftUp,"SPELLSELECT");
    widget->mtable.LeftUp = funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDrag,"SPELLSELECT");
    widget->mtable.LeftDrag = funcInt;


    widget->mtable.MouseIcon = 133;
    *self = widget;
    return Success;

}

bbFlag SpellSelect_Constructor (bbWidget** self, void* Graphics,
                             bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {


    bbWidget *widget;
    bbFlag flag = bbWidget_newEmpty(&widget, widgets, parent);
    widget->type = bbWidgetType_SpellSelector;

    bbAssert(widget != NULL, "null address\n");

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 36;
    rect.height = SCREEN_PPP * 36;

    widget->rect = rect;

    bbGraphicsApp *graphics = Graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL1",
                        &widget->frames[0].handle);

    int funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver,
                                      "SPELLSELECT");

    widget->mtable.isOver = funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseEnter,
                                      "SPELLSELECT");
    widget->mtable.Enter = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeave,
                                      "SPELLSELECT");
    widget->mtable.Leave = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDown,"SPELLSELECT");
    widget->mtable.LeftDown = funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftUp,"SPELLSELECT");
    widget->mtable.LeftUp = funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                      MouseLeftDrag,"SPELLSELECT");
    widget->mtable.LeftDrag = funcInt;


    widget->mtable.MouseIcon = 133;

    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "SPELLSELECT?", handle);
    *self = widget;
    return Success;

}