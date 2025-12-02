#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

bbFlag Spellbar_Constructor (bbWidget** self, void* Graphics,
                        bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {


    bbWidget *widget;
    bbFlag flag = bbWidget_newEmpty(&widget, widgets, parent);

    bbAssert(widget != NULL, "null address\n");

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 303;
    rect.height = SCREEN_PPP * 47;

    widget->mtable.MouseIcon = 89;

    widget->rect = rect;

    bbGraphics *graphics = Graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELLBAR",
                        &widget->frames[0].handle);


    int funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeftDown,
                                      "SPELLBAR");
    widget->mtable.LeftDown = funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver,
                                      "SPELLSELECT");
    widget->mtable.isOver = funcInt;

    bbScreenPoints SP0;
    bbWidget* widget0;
    bbWidget* widget1;


    SP0.x = screen_coords.x + 11*8 + 0*35*8; SP0.y = screen_coords.y + 11*8;
    bbWidget_constructor(&widget1, widgets, Graphics,
                         SP0, widget,"SPELLSLOT");

    SP0.x = screen_coords.x + 11*8 + 1*35*8; SP0.y = screen_coords.y + 11*8;
    bbWidget_constructor(&widget1, widgets, Graphics,
                         SP0, widget,"SPELLSLOT");

    SP0.x = screen_coords.x + 11*8 + 2*35*8; SP0.y = screen_coords.y + 11*8;
    bbWidget_constructor(&widget1, widgets, Graphics,
                         SP0, widget,"SPELLSLOT");

    SP0.x = screen_coords.x + 11*8 + 3*35*8; SP0.y = screen_coords.y + 11*8;
    bbWidget_constructor(&widget1, widgets, Graphics,
                         SP0, widget,"SPELLSLOT");

    SP0.x = screen_coords.x + 11*8 + 4*35*8; SP0.y = screen_coords.y + 11*8;
    bbWidget_constructor(&widget1, widgets, Graphics,
                         SP0, widget,"SPELLSLOT");

    SP0.x = screen_coords.x + 11*8 + 5*35*8; SP0.y = screen_coords.y + 11*8;
    bbWidget_constructor(&widget1, widgets, Graphics,
                         SP0, widget,"SPELLSLOT");

    SP0.x = screen_coords.x + 11*8 + 6*35*8; SP0.y = screen_coords.y + 11*8;
    bbWidget_constructor(&widget1, widgets, Graphics,
                         SP0, widget,"SPELLSLOT");

    SP0.x = screen_coords.x + 11*8 + 7*35*8; SP0.y = screen_coords.y + 11*8;
    bbWidget_constructor(&widget1, widgets, Graphics,
                         SP0, widget,"SPELLSLOT");






    *self = widget;

}