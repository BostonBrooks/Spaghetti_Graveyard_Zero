

#ifndef MOOSE_FUNCTIONS
#define MOOSE_FUNCTIONS

#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbMouseFunctions.h"
#include "games/game0/maps/map0/mouse/mouse.h"
#include "games/game0/maps/map0/mouse/button.h"
#include "games/game0/maps/map0/mouse/box.h"
#include "games/game0/maps/map0/mouse/card.h"
#include "games/game0/maps/map0/mouse/spellselect.h"
#include "games/game0/maps/map0/mouse/spellslot.h"
#include "games/game0/maps/map0/mouse/spellmenu.h"
#include "games/game0/maps/map0/mouse/spellbar.h"
#include "games/game0/maps/map0/mouse/textbox.h"
#include "games/game0/maps/map0/mouse/connecticon.h"
#include "games/game0/maps/map0/mouse/currentspell.h"
#include "games/game0/maps/map0/mouse/connectbutton.h"

bbFlag bbMouseFunctions_populate(bbMouseFunctions* self)
{

    //typedef bbFlag bbMouse_IsOver (struct bbMouse* mouse, struct bbWidgets* widgets, struct bbWidget* widget);
    bbMouseFunctions_add(self, MouseIsOver, IsOver_Always, "ALWAYS");
    bbMouseFunctions_add(self, MouseIsOver, IsOver_Teleport, "TELEPORT");
    bbMouseFunctions_add(self, MouseIsOver, IsOver_Hover, "HOVER");
    bbMouseFunctions_add(self, MouseIsOver, IsOver_Viewport, "VIEWPORT");
    bbMouseFunctions_add(self, MouseLeftDown, Viewport_LeftDown, "VIEWPORT");


    bbMouseFunctions_add(self, MouseIsOver, Button_IsOver, "BUTTON");
    bbMouseFunctions_add(self, MouseEnter, Button_Enter, "BUTTON");
    bbMouseFunctions_add(self, MouseLeave, Button_Leave, "BUTTON");
    bbMouseFunctions_add(self, MouseLeftDown, Button_LeftDown, "BUTTON");
    bbMouseFunctions_add(self, MouseLeftUp, Button_LeftUp, "BUTTON");

    bbMouseFunctions_add(self, MouseIsOver, ConnectButton_IsOver, "CONNECT");
    bbMouseFunctions_add(self, MouseEnter, ConnectButton_Enter, "CONNECT");
    bbMouseFunctions_add(self, MouseLeave, ConnectButton_Leave, "CONNECT");
    bbMouseFunctions_add(self, MouseLeftDown, ConnectButton_LeftDown, "CONNECT");
    bbMouseFunctions_add(self, MouseLeftUp, ConnectButton_LeftUp, "CONNECT");


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
    bbMouseFunctions_add(self, MouseEnter, SpellSelect_Enter, "SPELLSELECT");
    bbMouseFunctions_add(self, MouseLeave, SpellSelect_Leave, "SPELLSELECT");
    bbMouseFunctions_add(self, MouseLeftDown, SpellSelect_LeftDown, "SPELLSELECT");
    bbMouseFunctions_add(self, MouseLeftUp, SpellSelect_LeftUp, "SPELLSELECT");
    bbMouseFunctions_add(self, MouseLeftDrag, SpellSelect_LeftDrag, "SPELLSELECT");


    bbMouseFunctions_add(self, MouseLeftDown,  SpellSlot_LeftDown, "SPELLSLOT");
    bbMouseFunctions_add(self, MouseLeftDown,  SpellMenu_LeftDown, "SPELLMENU");
    bbMouseFunctions_add(self, MouseLeftDown,  SpellBar_LeftDown, "SPELLBAR");


    bbMouseFunctions_add(self, MouseIsOver,  Textbox_IsOver, "TEXTBOX");
    bbMouseFunctions_add(self, MouseLeftDown,  Textbox_LeftDown, "TEXTBOX");


    bbMouseFunctions_add(self, MouseLeftDown,  ConnectIcon_LeftDown, "CONNECTICON");
    bbMouseFunctions_add(self, MouseLeftDown,  CurrentSpell_LeftDown, "CURRENTSPELL");

    return Success;
}

#endif // MOOSE_FUNCTIONS