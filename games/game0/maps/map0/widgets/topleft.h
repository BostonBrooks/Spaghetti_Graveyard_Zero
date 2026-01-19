#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

bbFlag TopLeft_Constructor (bbWidget** self, void* Graphics,
                        bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{
    bbWidget *widget;
    bbFlag flag = bbWidget_newEmpty(&widget, widgets, parent);

    bbAssert(widget != NULL, "null address\n");

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 292;
    rect.height = SCREEN_PPP * 47;

    widget->mtable.MouseIcon = 89;


    bbGraphicsApp *graphics = Graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->sprites->dictionary, "TOPLEFT",
                        &widget->frames[0].handle);


    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "TOPLEFT", handle);

    *self = widget;
    return Success;
}


bbFlag TOPLEFT_Constructor2 (bbWidget** self,
                            bbWidgets* widgets,
                            bbWidget* parent,
                            char* name,
                            bbScreenPoints screen_coords,
                            bbGraphicsApp* graphics
                            )
{
    bbWidget* widget;
    bbWidget_newEmpty2(&widget, widgets, parent, name);

    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = SCREEN_PPP * 292;
    rect.height = SCREEN_PPP * 47;

    widget->rect = rect;
    widget->mtable.MouseIcon = 89;

    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSPRITE",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    bbDictionary_lookup(graphics->sprites->dictionary, "TOPLEFT",
                        &widget->frames[0].handle);



    bbWidget_constructor2(&widget,
                     widgets,
                     "CURRENTSPELL",
                     name,
                     "CURRENTSPELL2",
                     11*SCREEN_PPP,
                     11*SCREEN_PPP);

    bbWidget_constructor2(&widget,
                     widgets,
                     "CONNECTICON",
                     name,
                     "CONNECTICON2",
                     46*SCREEN_PPP,
                     11*SCREEN_PPP);

    *self = widget;
    return Success;
}