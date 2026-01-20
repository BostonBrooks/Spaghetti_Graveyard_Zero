#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

bbFlag SPELLMENU_Constructor2 (bbWidget** self,
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


    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 373;
    rect.height = SCREEN_PPP * 197;

    widget->mtable.MouseIcon = 89;

    widget->rect = rect;

    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(graphics->drawfunctions->dictionary, "LAYERBOUNDARY",
                        &drawfunctionHandle);

    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->sprites->dictionary, "LAYERBOUNDARY",
                        &widget->frames[0].handle);

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                    &drawfunctionHandle);
    widget->frames[1].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELLMENU",
                        &widget->frames[1].handle);

    int funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeftDown,
                                      "SPELLMENU");
    widget->mtable.LeftDown = funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver,
                                      "ALWAYS");
    widget->mtable.isOver = funcInt;


    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "SPELLMENU", handle);

    bbWidget* widget0;
    bbScreenPoints SP;




    bbWidget_constructor2(&widget0,
             widgets,
             "SPELLSELECT1",
             "SPELLMENU",
             "SPELLSELECT1",
             screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*0,
             screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0);

    bbWidget_constructor2(&widget0,
         widgets,
         "SPELLSELECT2",
         "SPELLMENU",
         "SPELLSELECT2",
         screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*1,
         screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0);

    bbWidget_constructor2(&widget0,
         widgets,
         "SPELLSELECT3",
         "SPELLMENU",
         "SPELLSELECT3",
         screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*2,
         screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0);

    bbWidget_constructor2(&widget0,
         widgets,
         "SPELLSELECT4",
         "SPELLMENU",
         "SPELLSELECT4",
         screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*3,
         screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0);


    widgets->spellMenu = widget;
    *self = widget;

}
bbFlag SpellMenu_Constructor (bbWidget** self, void* Graphics,
                        bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {


    bbWidget *widget;
    bbFlag flag = bbWidget_newEmpty(&widget, widgets, parent);

    bbAssert(widget != NULL, "null address\n");

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 373;
    rect.height = SCREEN_PPP * 197;

    widget->mtable.MouseIcon = 89;

    widget->rect = rect;

    bbGraphicsApp *graphics = Graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(graphics->drawfunctions->dictionary, "LAYERBOUNDARY",
                        &drawfunctionHandle);

    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->sprites->dictionary, "LAYERBOUNDARY",
                        &widget->frames[0].handle);

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                    &drawfunctionHandle);
    widget->frames[1].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELLMENU",
                        &widget->frames[1].handle);

    int funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeftDown,
                                      "SPELLMENU");
    widget->mtable.LeftDown = funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver,
                                      "ALWAYS");
    widget->mtable.isOver = funcInt;


    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "SPELLMENU", handle);

    bbWidget* widget0;
    bbScreenPoints SP;




    bbWidget_constructor2(&widget0,
             widgets,
             "SPELLSELECT1",
             "SPELLMENU",
             "SPELLSELECT1",
             screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*0,
             screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0);

    bbWidget_constructor2(&widget0,
         widgets,
         "SPELLSELECT2",
         "SPELLMENU",
         "SPELLSELECT2",
         screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*1,
         screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0);

    bbWidget_constructor2(&widget0,
         widgets,
         "SPELLSELECT3",
         "SPELLMENU",
         "SPELLSELECT3",
         screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*2,
         screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0);

    bbWidget_constructor2(&widget0,
         widgets,
         "SPELLSELECT4",
         "SPELLMENU",
         "SPELLSELECT4",
         screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*3,
         screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0);

/*
    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*1;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT2");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*2;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT3");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*3;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT4");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*4;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT5");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*5;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT6");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*6;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT7");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*7;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT8");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*SCREEN_PPP;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT9");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*9;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*0;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT10");


    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*0;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT11");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*1;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT12");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*2;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT13");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*3;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT14");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*4;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT15");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*5;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT16");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*6;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT17");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*7;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT18");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*SCREEN_PPP;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT19");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*9;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*1;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT20");


    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*0;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT21");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*1;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT22");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*2;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT23");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*3;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT24");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*4;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT25");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*5;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT26");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*6;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT27");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*7;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT28");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*SCREEN_PPP;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT29");

    SP.x = screen_coords.x + 11*SCREEN_PPP + 35*SCREEN_PPP*9;
    SP.y = screen_coords.y + 80*SCREEN_PPP + 35*SCREEN_PPP*2;
    bbWidget_constructor(&widget0, widgets, graphics,
                         SP, widget, "SPELLSELECT30");
*/


    widgets->spellMenu = widget;
    *self = widget;

}