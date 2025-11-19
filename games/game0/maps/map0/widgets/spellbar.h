#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"
#include "engine/widgets/bbWidgetFunctions.h"

bbFlag Spellbar_Constructor (bbWidget** self, void* graphics,
                        bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {


    bbWidget *widget;
    bbFlag flag = bbWidget_newEmpty(&widget, widgets, parent);

    bbAssert(widget != NULL, "null address\n");

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 52;
    rect.height = SCREEN_PPP * 52;

    widget->rect = rect;

    bbGraphics *Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELLBAR",
                        &widget->frames[0].handle);


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