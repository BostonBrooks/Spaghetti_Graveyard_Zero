#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"
#include "engine/data/bbHome.h"

//typedef bbFlag bbMouse_LeftDown (void* mouse, void* widgets, void* widget,
// void* graphics);
bbFlag SpellSlot_LeftDown (void* mouse, void* widgets, void* widget, void*
graphics)
{

    bbWidget* Widget = (bbWidget*)widget;
    bbGraphics* Graphics = graphics;
    bbMouse* Mouse = mouse;
    bbWidgets* Widgets = widgets;

    bbWidget* CurrentSpell = Widgets->currentSpell;
    CurrentSpell->frames[0].handle = Widget->frames[0].handle;

    bbSpell_setActive_Key(Widget->key,
                          &home.private.spells,
                          home.private.server,
                          home.private.mapTime);

    return Success;
}
