

#ifndef MOOSE_FUNCTIONS
#define MOOSE_FUNCTIONS

#include "engine/logic/bbFlag.h"
#include "engine/user_input/bbMooseFunctions.h"
#include "games/game0/maps/map0/widgets/moose.h"
#include "games/game0/maps/map0/widgets/button.h"

bbFlag bbMooseFunctions_populate(bbMooseFunctions* self)
{

    //typedef bbFlag bbMoose_IsOver (struct bbMoose* moose, struct bbWidgets* widgets, struct bbWidget* widget);
    bbMooseFunctions_add(self, MooseIsOver, IsOver_Always, "ALWAYS");
    bbMooseFunctions_add(self, MooseIsOver, IsOver_Teleport, "TELEPORT");
    bbMooseFunctions_add(self, MooseIsOver, IsOver_Hover, "HOVER");
    bbMooseFunctions_add(self, MooseIsOver, IsOver_Viewport, "VIEWPORT");


    bbMooseFunctions_add(self, MooseIsOver, Button_IsOver, "BUTTON");
    bbMooseFunctions_add(self, MooseEnter, Button_Enter, "BUTTON");
    bbMooseFunctions_add(self, MooseLeave, Button_Leave, "BUTTON");
    bbMooseFunctions_add(self, MooseLeftDown, Button_LeftDown, "BUTTON");
    bbMooseFunctions_add(self, MooseLeftUp, Button_LeftUp, "BUTTON");

    //test:


    return Success;
}

#endif // MOOSE_FUNCTIONS