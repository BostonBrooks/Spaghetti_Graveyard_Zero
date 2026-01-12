#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

bbFlag SpellSlot_Constructor (bbWidget** self, void* Graphics,
                             bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {


    bbWidget *widget;
    bbFlag flag = bbWidget_newEmpty(&widget, widgets, parent);
    widget->type = bbWidgetType_SpellSlot;

    bbStr_setStr(widget->key, "SPELL2", 64);

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

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELLSLOT",
                        &widget->frames[0].handle);

    int funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver,
                                      "SPELLSELECT");
    widget->mtable.isOver = funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeftDown,
                                      "SPELLSLOT");
    widget->mtable.LeftDown = funcInt;

    widget->mtable.MouseIcon = 133;

    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "SPELLSLOT?", handle);

    *self = widget;
    return Success;

}