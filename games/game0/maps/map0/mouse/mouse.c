

#ifndef MOOSE_FUNCTIONS
#define MOOSE_FUNCTIONS

#include "engine/logic/bbFlag.h"
#include "engine/user_input/bbMouseFunctions.h"
#include "games/game0/maps/map0/mouse/mouse.h"
#include "games/game0/maps/map0/mouse/button.h"
#include "games/game0/maps/map0/mouse/box.h"
#include "games/game0/maps/map0/mouse/card.h"
#include "games/game0/maps/map0/mouse/spellselect.h"

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


    bbMouseFunctions_add(self, MouseIsOver, Box_IsOver, "BOX");
    bbMouseFunctions_add(self, MouseEnter, Box_Enter, "BOX");
    bbMouseFunctions_add(self, MouseLeave, Box_Leave, "BOX");
    bbMouseFunctions_add(self, MouseLeftDown, Box_LeftDown, "BOX");
    bbMouseFunctions_add(self, MouseLeftUp, Box_LeftUp, "BOX");
    bbMouseFunctions_add(self, MouseLeftDrag, Box_LeftDrag, "BOX");

    bbMouseFunctions_add(self, MouseIsOver, Card_IsOver, "CARD");
    bbMouseFunctions_add(self, MouseEnter, Card_Enter, "CARD");
    bbMouseFunctions_add(self, MouseLeave, Card_Leave, "CARD");
    bbMouseFunctions_add(self, MouseLeftDown, Card_LeftDown, "CARD");
    bbMouseFunctions_add(self, MouseLeftUp, Card_LeftUp, "CARD");
    bbMouseFunctions_add(self, MouseLeftDrag, Card_LeftDrag, "CARD");

    bbMouseFunctions_add(self, MouseIsOver, SpellSelect_IsOver, "SPELLSELECT");
//    bbMouseFunctions_add(self, MouseEnter, SpellSelect_Enter, "SPELLSELECT");
//    bbMouseFunctions_add(self, MouseLeave, SpellSelect_Leave, "SPELLSELECT");
//    bbMouseFunctions_add(self, MouseLeftDown, SpellSelect_LeftDown, "SPELLSELECT");
//    bbMouseFunctions_add(self, MouseLeftUp, SpellSelect_LeftUp, "SPELLSELECT");
//    bbMouseFunctions_add(self, MouseLeftDrag, SpellSelect_LeftDrag, "SPELLSELECT");



    return Success;
}

#endif // MOOSE_FUNCTIONS