

#ifndef MOOSE_FUNCTIONS
#define MOOSE_FUNCTIONS

#include "engine/logic/bbFlag.h"
#include "engine/user_input/bbMouseFunctions.h"
#include "games/game0/maps/map0/mouse/mouse.h"
#include "games/game0/maps/map0/mouse/button.h"

bbFlag bbMouseFunctions_populate(bbMouseFunctions* self)
{

    //typedef bbFlag bbMouse_IsOver (struct bbMouse* mouse, struct bbWidgets* widgets, struct bbWidget* widget);
    bbMouseFunctions_add(self, MouseIsOver, IsOver_Always, "ALWAYS");
    bbMouseFunctions_add(self, MouseIsOver, IsOver_Teleport, "TELEPORT");
    bbMouseFunctions_add(self, MouseIsOver, IsOver_Hover, "HOVER");
    bbMouseFunctions_add(self, MouseIsOver, IsOver_Viewport, "VIEWPORT");


    bbMouseFunctions_add(self, MouseIsOver, Button_IsOver, "BUTTON");
    bbMouseFunctions_add(self, MouseEnter, Button_Enter, "BUTTON");
    bbMouseFunctions_add(self, MouseLeave, Button_Leave, "BUTTON");
    bbMouseFunctions_add(self, MouseLeftDown, Button_LeftDown, "BUTTON");
    bbMouseFunctions_add(self, MouseLeftUp, Button_LeftUp, "BUTTON");

    //test:


    return Success;
}

#endif // MOOSE_FUNCTIONS