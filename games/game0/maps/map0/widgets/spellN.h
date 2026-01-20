#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"

bbFlag SPELLSELECT1_Constructor2 (bbWidget** self,
                            bbWidgets* widgets,
                            bbWidget* parent,
                            char* name,
                            bbScreenPoints screen_coords,
                            bbGraphicsApp* graphics
                            )
{
    bbHere()
        bbWidget* widget;
    bbScreenPoints SP;


    SP.x = screen_coords.x;
    SP.y = screen_coords.y;

    bbWidget_constructor2(&widget,
                         widgets,
                         "SPELLSELECT",
                         //This probably shouldn's be hard-coded
                         "SPELLMENU",
                         "SPELLSELECT1",
                          screen_coords.x,
                          screen_coords.y);

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL1",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL1",
                        &dragHandle);

    bbStr_setStr(widget->key, "SPELL1", 64);

    widget->mtable.DragIcon = dragHandle.u64;


    *self = widget;
    return Success;
}

bbFlag SPELLSELECT2_Constructor2 (bbWidget** self,
                            bbWidgets* widgets,
                            bbWidget* parent,
                            char* name,
                            bbScreenPoints screen_coords,
                            bbGraphicsApp* graphics
                            )
{
    bbHere()
        bbWidget* widget;
    bbScreenPoints SP;

    bbWidget_constructor2(&widget,
                         widgets,
                         "SPELLSELECT",
                         "SPELLMENU",
                         "SPELLSELECT2",
                          screen_coords.x,
                          screen_coords.y);

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL2",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL2",
                        &dragHandle);

    bbStr_setStr(widget->key, "SPELL2", 64);

    widget->mtable.DragIcon = dragHandle.u64;


    *self = widget;
    return Success;
}

bbFlag SPELLSELECT3_Constructor2 (bbWidget** self,
                            bbWidgets* widgets,
                            bbWidget* parent,
                            char* name,
                            bbScreenPoints screen_coords,
                            bbGraphicsApp* graphics
                            )
{
    bbHere()
        bbWidget* widget;
    bbScreenPoints SP;

    bbWidget_constructor2(&widget,
                         widgets,
                         "SPELLSELECT",
                         "SPELLMENU",
                         "SPELLSELECT3",
                          screen_coords.x,
                          screen_coords.y);

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL3",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL3",
                        &dragHandle);

    bbStr_setStr(widget->key, "SPELL3", 64);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;
}

bbFlag SPELLSELECT4_Constructor2 (bbWidget** self,
                            bbWidgets* widgets,
                            bbWidget* parent,
                            char* name,
                            bbScreenPoints screen_coords,
                            bbGraphicsApp* graphics
                            )
{
    bbHere()
        bbWidget* widget;
    bbScreenPoints SP;

    bbWidget_constructor2(&widget,
                         widgets,
                         "SPELLSELECT",
                         "SPELLMENU",
                         "SPELLSELECT4",
                          screen_coords.x,
                          screen_coords.y);

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL4",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL4",
                        &dragHandle);

    bbStr_setStr(widget->key, "SPELL4", 64);

    widget->mtable.DragIcon = dragHandle.u64;


    *self = widget;
    return Success;
}

bbFlag SpellSelect1_Constructor (bbWidget** self, void* Graphics,
                             bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphicsApp *graphics = Graphics;
    bbWidget* widget;
    bbScreenPoints SP;


    SP.x = screen_coords.x;
    SP.y = screen_coords.y;
    bbWidget_constructor(&widget, widgets, Graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL1",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL1",
                        &dragHandle);

    bbStr_setStr(widget->key, "SPELL1", 64);

    widget->mtable.DragIcon = dragHandle.u64;


    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "SPELLSELECT1", handle);

    *self = widget;
    return Success;

}

bbFlag SpellSelect2_Constructor (bbWidget** self, void* Graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphicsApp *graphics = Graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x;
    SP.y = screen_coords.y;
    bbWidget_constructor(&widget, widgets, Graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL2",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL2",
                        &dragHandle);
    bbStr_setStr(widget->key, "SPELL2", 64);

    widget->mtable.DragIcon = dragHandle.u64;

    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "SPELLSELECT2", handle);
    *self = widget;
    return Success;

}

bbFlag SpellSelect3_Constructor (bbWidget** self, void* Graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphicsApp *graphics = Graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x;
    SP.y = screen_coords.y;
    bbWidget_constructor(&widget, widgets, Graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL3",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL3",
                        &dragHandle);

    bbStr_setStr(widget->key, "SPELL3", 64);

    widget->mtable.DragIcon = dragHandle.u64;


    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "SPELLSELECT3", handle);

    *self = widget;
    return Success;

}

bbFlag SpellSelect4_Constructor (bbWidget** self, void* Graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphicsApp *graphics = Graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x;
    SP.y = screen_coords.y;
    bbWidget_constructor(&widget, widgets, Graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL4",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(graphics->sprites->dictionary, "SPELL4",
                        &dragHandle);

    bbStr_setStr(widget->key, "SPELL4", 64);

    widget->mtable.DragIcon = dragHandle.u64;

    bbPool_Handle handle;
    bbVPool_reverseLookup(widgets->pool, widget, &handle);
    bbDictionary_add(widgets->dict, "SPELLSELECT4", handle);

    *self = widget;
    return Success;

}
