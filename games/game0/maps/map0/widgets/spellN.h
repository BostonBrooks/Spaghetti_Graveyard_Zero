#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"
#include "engine/widgets/bbWidgetFunctions.h"

bbFlag SpellSelect1_Constructor (bbWidget** self, void* graphics,
                             bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL1",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL1",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect2_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL2",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL2",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect3_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL3",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL3",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect4_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL4",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL4",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect5_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL5",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL5",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect6_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL6",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL6",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect7_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL7",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL7",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect8_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL8",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL8",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect9_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL9",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL9",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect10_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL10",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL10",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect11_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL11",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL11",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect12_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL12",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL12",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect13_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL13",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL13",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect14_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL14",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL14",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect15_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL15",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL15",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect16_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL16",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL16",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect17_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL17",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL17",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect18_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL18",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL18",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect19_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL19",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL19",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect20_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL20",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL20",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect21_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL21",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL21",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect22_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL22",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL22",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect23_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL23",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL23",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect24_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL24",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL24",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect25_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL25",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL25",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect26_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL26",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL26",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect27_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL27",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL27",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect28_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL28",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL28",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect29_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL29",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL29",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}

bbFlag SpellSelect30_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent) {

    bbGraphics *Graphics = graphics;
    bbWidget* widget;
    bbScreenPoints SP;

    SP.x = screen_coords.x + 11*8 + 35*8*0;
    SP.y = screen_coords.y + 11*8 + 35*8*0;
    bbWidget_constructor(&widget, widgets, graphics,
                         SP, parent, "SPELLSELECT");

    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL30",
                        &widget->frames[0].handle);


    bbPool_Handle dragHandle;
    bbDictionary_lookup(Graphics->sprites->dictionary, "SPELL30",
                        &dragHandle);

    widget->mtable.DragIcon = dragHandle.u64;

    *self = widget;
    return Success;

}