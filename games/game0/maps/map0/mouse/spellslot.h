#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"
#include "engine/widgets/bbWidgetFunctions.h"

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

    bbDebug("Mouse left button down on spells slot\n");
    return Success;
}
