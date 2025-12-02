#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

bbFlag SpellMenu_Constructor (bbWidget** self, void* graphics,
                        bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {


    bbWidget *widget;
    bbFlag flag = bbWidget_newEmpty(&widget, widgets, parent);

    bbAssert(widget != NULL, "null address\n");

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 373;
    rect.height = SCREEN_PPP * 127;

    widget->mtable.MouseIcon = 89;

    widget->rect = rect;

    bbGraphics *Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELLMENU",
                        &widget->frames[0].handle);

    int funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeftDown,
                                      "SPELLMENU");
    widget->mtable.LeftDown = funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver,
                                      "SPELLSELECT");
    widget->mtable.isOver = funcInt;

    bbWidget* widget0;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT1");

    SP.x = screen_coords.x + 11*8 + 35*8*1;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT2");

    SP.x = screen_coords.x + 11*8 + 35*8*2;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT3");

    SP.x = screen_coords.x + 11*8 + 35*8*3;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT4");

    SP.x = screen_coords.x + 11*8 + 35*8*4;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT5");

    SP.x = screen_coords.x + 11*8 + 35*8*5;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT6");

    SP.x = screen_coords.x + 11*8 + 35*8*6;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT7");

    SP.x = screen_coords.x + 11*8 + 35*8*7;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT8");

    SP.x = screen_coords.x + 11*8 + 35*8*8;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT9");

    SP.x = screen_coords.x + 11*8 + 35*8*9;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT10");


    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT11");

    SP.x = screen_coords.x + 11*8 + 35*8*1;
    SP.y = screen_coords.y + 11*8 + 35*8*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT12");

    SP.x = screen_coords.x + 11*8 + 35*8*2;
    SP.y = screen_coords.y + 11*8 + 35*8*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT13");

    SP.x = screen_coords.x + 11*8 + 35*8*3;
    SP.y = screen_coords.y + 11*8 + 35*8*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT14");

    SP.x = screen_coords.x + 11*8 + 35*8*4;
    SP.y = screen_coords.y + 11*8 + 35*8*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT15");

    SP.x = screen_coords.x + 11*8 + 35*8*5;
    SP.y = screen_coords.y + 11*8 + 35*8*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT16");

    SP.x = screen_coords.x + 11*8 + 35*8*6;
    SP.y = screen_coords.y + 11*8 + 35*8*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT17");

    SP.x = screen_coords.x + 11*8 + 35*8*7;
    SP.y = screen_coords.y + 11*8 + 35*8*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT18");

    SP.x = screen_coords.x + 11*8 + 35*8*8;
    SP.y = screen_coords.y + 11*8 + 35*8*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT19");

    SP.x = screen_coords.x + 11*8 + 35*8*9;
    SP.y = screen_coords.y + 11*8 + 35*8*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT20");


    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT21");

    SP.x = screen_coords.x + 11*8 + 35*8*1;
    SP.y = screen_coords.y + 11*8 + 35*8*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT22");

    SP.x = screen_coords.x + 11*8 + 35*8*2;
    SP.y = screen_coords.y + 11*8 + 35*8*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT23");

    SP.x = screen_coords.x + 11*8 + 35*8*3;
    SP.y = screen_coords.y + 11*8 + 35*8*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT24");

    SP.x = screen_coords.x + 11*8 + 35*8*4;
    SP.y = screen_coords.y + 11*8 + 35*8*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT25");

    SP.x = screen_coords.x + 11*8 + 35*8*5;
    SP.y = screen_coords.y + 11*8 + 35*8*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT26");

    SP.x = screen_coords.x + 11*8 + 35*8*6;
    SP.y = screen_coords.y + 11*8 + 35*8*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT27");

    SP.x = screen_coords.x + 11*8 + 35*8*7;
    SP.y = screen_coords.y + 11*8 + 35*8*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT28");

    SP.x = screen_coords.x + 11*8 + 35*8*8;
    SP.y = screen_coords.y + 11*8 + 35*8*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT29");

    SP.x = screen_coords.x + 11*8 + 35*8*9;
    SP.y = screen_coords.y + 11*8 + 35*8*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT30");

    widgets->spellMenu = widget;
    *self = widget;

}