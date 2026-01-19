

#ifndef WIDGET_FUNCTIONS
#define WIDGET_FUNCTIONS

#include "engine/includes/CSFML.h"
#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidgetFunctions.h"

#include "games/game0/maps/map0/widgets/nullfunctions.h"
#include "games/game0/maps/map0/widgets/sphere.h"
#include "games/game0/maps/map0/widgets/button.h"
#include "games/game0/maps/map0/widgets/box.h"
#include "games/game0/maps/map0/widgets/card.h"
#include "games/game0/maps/map0/widgets/textbox.h"
#include "games/game0/maps/map0/widgets/spellbar.h"
#include "games/game0/maps/map0/widgets/spellmenu.h"
#include "games/game0/maps/map0/widgets/spellselect.h"
#include "games/game0/maps/map0/widgets/spellN.h"
#include "games/game0/maps/map0/widgets/spellslot.h"
#include "games/game0/maps/map0/widgets/currentspell.h"
#include "games/game0/maps/map0/widgets/connect.h"
#include "games/game0/maps/map0/widgets/topleft.h"
#include "games/game0/maps/map0/widgets/connectbuttons.h"
#include "games/game0/maps/map0/widgets/animationtest.h"



bbFlag bbWidgetFunctions_populate(bbWidgetFunctions* self)
{
    bbWidgetFunctions_add(self, WidgetConstructor2,
    NULL_Constructor2, "NULL");

    bbWidgetFunctions_add(self, WidgetConstructor2,
    SPHERE_Constructor2, "SPHERE");

    bbWidgetFunctions_add(self, WidgetConstructor2,
                          CARD_Constructor2, "CARD");

    bbWidgetFunctions_add(self, WidgetConstructor2,
    BOX_Constructor2, "BOX");

    bbWidgetFunctions_add(self, WidgetConstructor2,
    BUTTON_Constructor2, "BUTTON");

    bbWidgetFunctions_add(self, WidgetConstructor2,
    TOPLEFT_Constructor2, "TOPLEFT");

    bbWidgetFunctions_add(self, WidgetConstructor2,
    CURRENTSPELL_Constructor2, "CURRENTSPELL");

    bbWidgetFunctions_add(self, WidgetConstructor2,
    CONNECTICON_Constructor2, "CONNECTICON");

    bbWidgetFunctions_add(self, WidgetConstructor2,
    TEXTBOX_Constructor2, "TEXTBOX");

    bbWidgetFunctions_add(self, WidgetConstructor2,
                          CONNECTMENU_Constructor2, "CONNECTMENU");

    //typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
    //                                     bbWidgets* widgets, bbScreenPoints
    //                                     screen_coords, bbWidget* parent);
    bbWidgetFunctions_add(self, WidgetConstructor,
                          NULL_Constructor, "NULLCONSTRUCTOR");

    bbWidgetFunctions_add(self, WidgetConstructor,
    SPHERE_Constructor, "SPHERE");

    bbWidgetFunctions_add(self, WidgetConstructor,
                          Button_Constructor, "BUTTON");

    bbWidgetFunctions_add(self, WidgetConstructor,
                          Box_Constructor, "BOX");


    bbWidgetFunctions_add(self, WidgetConstructor,
                          Textbox_Constructor, "TEXTBOX");


    bbWidgetFunctions_add(self, WidgetConstructor,
                          Card_Constructor, "CARD");

    bbWidgetFunctions_add(self, WidgetConstructor,
    Spellbar_Constructor, "SPELLBAR");

    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellMenu_Constructor, "SPELLMENU");

    bbWidgetFunctions_add(self, WidgetConstructor,
                          ConnectMenu_Constructor, "CONNECTMENU");


    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect_Constructor, "SPELLSELECT");

    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect1_Constructor, "SPELLSELECT1");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect2_Constructor, "SPELLSELECT2");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect3_Constructor, "SPELLSELECT3");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect4_Constructor, "SPELLSELECT4");

    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSlot_Constructor, "SPELLSLOT");


    bbWidgetFunctions_add(self, WidgetConstructor,
                          CurrentSpell_Constructor, "CURRENTSPELL");

    bbWidgetFunctions_add(self, WidgetConstructor,
                          TopLeft_Constructor, "TOPLEFT");


    bbWidgetFunctions_add(self, WidgetConstructor,
                          ConnectIcon_Constructor, "CONNECTICON");

    bbWidgetFunctions_add(self, WidgetConstructor,
    ConnectButton_Constructor, "CONNECTBUTTON");

    bbWidgetFunctions_add(self, WidgetConstructor,
    DisConnectButton_Constructor, "DISCONNECTBUTTON");

    bbWidgetFunctions_add(self, WidgetConstructor,
    GoOfflineButton_Constructor, "NEWSERVER");

    bbWidgetFunctions_add(self, WidgetConstructor,
                      AnimationTest_Constructor, "ANIMATIONTEST");




    //typedef bbFlag bbWidget_Update (bbWidget* widget, void* unused);
    bbWidgetFunctions_add(self, WidgetUpdate,
                          NULL_Update, "NULLUPDATE");

    //typedef bbFlag bbWidget_Destructor (bbWidget* widget, void* unused);
    bbWidgetFunctions_add(self, WidgetDestructor,
                          NULL_Destructor, "NULLDESTRUCTOR");

    //typedef bbFlag bbWidget_OnCommand (bbWidget* widget,bbWidgetCommandType type, void* data);
    bbWidgetFunctions_add(self, WidgetOnCommand,
                          NULL_OnCommand, "NULLONCOMMAND");

    //typedef bbFlag bbWidget_OnCommand (bbWidget* widget,bbWidgetCommandType type, void* data);
    bbWidgetFunctions_add(self, WidgetOnCommand,
    Textbox_OnCommand, "TEXTBOX");

    //typedef bbFlag bbWidget_OnTimer (bbWidget* widget, void* void_timerNode)
    bbWidgetFunctions_add(self, WidgetOnTimer,
    NULL_OnTimer, "NULLONTIMER");

    //typedef bbFlag bbWidget_Hide (bbWidget* widget, bbWidgets* widgets);
    bbWidgetFunctions_add(self, WidgetHide,
    NULL_Hide, "NULLHIDE");


    //typedef bbFlag bbWidget_UnHide (bbWidget* widget, bbWidgets* widgets);
    bbWidgetFunctions_add(self, WidgetUnhide,
                          NULL_Unhide, "NULLUNHIDE");



    //typedef bbFlag bbWidget_Hide (bbWidget* widget, bbWidgets* widgets);
    bbWidgetFunctions_add(self, WidgetHide,
    Connect_Hide, "CONNECTHIDE");


    //typedef bbFlag bbWidget_UnHide (bbWidget* widget, bbWidgets* widgets);
    bbWidgetFunctions_add(self, WidgetUnhide,
                          Connect_Unhide, "CONNECTUNHIDE");

    return Success;
}

#endif //WIDGET_FUNCTIONS