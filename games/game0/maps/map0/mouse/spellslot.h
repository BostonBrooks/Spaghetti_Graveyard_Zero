#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"
#include "engine/data/bbHome.h"

//typedef bbFlag bbMouse_LeftDown (void* mouse, void* widgets, void* widget,
// void* graphics);
bbFlag SpellSlot_LeftDown (void* Mouse, void* Widgets, void* Widget, void*
Graphics)
{

    bbWidget* widget = (bbWidget*)Widget;
    bbGraphicsApp* graphics = Graphics;
    bbMouse* mouse = Mouse;
    bbWidgets* widgets = Widgets;

    bbWidget* CurrentSpell = widgets->currentSpell;
    CurrentSpell->frames[0].handle = widget->frames[0].handle;
/*
    bbSpell_setActive_Key(widget->key,
                          &home.private.UI.spells,
                          home.private.server,
                          home.private.mapTime);
*/
    return Success;
}
