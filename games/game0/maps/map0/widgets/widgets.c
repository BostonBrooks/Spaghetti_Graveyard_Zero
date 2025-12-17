//Widgetes used: Layout, viewport, button, box

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



bbFlag bbWidgetFunctions_populate(bbWidgetFunctions* self)
{
    //typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
    //                                     bbWidgets* widgets, bbScreenPoints
    //                                     screen_coords, bbWidget* parent);
    bbWidgetFunctions_add(self, WidgetConstructor,
                          NULL_Constructor, "NULL Constructor");

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
                          SpellSelect5_Constructor, "SPELLSELECT5");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect6_Constructor, "SPELLSELECT6");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect7_Constructor, "SPELLSELECT7");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect8_Constructor, "SPELLSELECT8");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect9_Constructor, "SPELLSELECT9");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect10_Constructor, "SPELLSELECT10");

    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect11_Constructor, "SPELLSELECT11");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect12_Constructor, "SPELLSELECT12");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect13_Constructor, "SPELLSELECT13");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect14_Constructor, "SPELLSELECT14");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect15_Constructor, "SPELLSELECT15");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect16_Constructor, "SPELLSELECT16");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect17_Constructor, "SPELLSELECT17");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect18_Constructor, "SPELLSELECT18");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect19_Constructor, "SPELLSELECT19");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect20_Constructor, "SPELLSELECT20");

    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect21_Constructor, "SPELLSELECT21");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect22_Constructor, "SPELLSELECT22");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect23_Constructor, "SPELLSELECT23");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect24_Constructor, "SPELLSELECT24");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect25_Constructor, "SPELLSELECT25");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect26_Constructor, "SPELLSELECT26");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect27_Constructor, "SPELLSELECT27");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect28_Constructor, "SPELLSELECT28");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect29_Constructor, "SPELLSELECT29");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSelect30_Constructor, "SPELLSELECT30");
    bbWidgetFunctions_add(self, WidgetConstructor,
                          SpellSlot_Constructor, "SPELLSLOT");


    bbWidgetFunctions_add(self, WidgetConstructor,
                          CurrentSpell_Constructor, "CURRENTSPELL");

    //typedef bbFlag bbWidget_Update (bbWidget* widget, void* unused);
    bbWidgetFunctions_add(self, WidgetUpdate,
                          NULL_Update, "NULL Update");

    //typedef bbFlag bbWidget_Destructor (bbWidget* widget, void* unused);
    bbWidgetFunctions_add(self, WidgetDestructor,
                          NULL_Destructor, "NULL Destructor");

    //typedef bbFlag bbWidget_OnCommand (bbWidget* widget,bbWidgetCommandType type, void* data);
    bbWidgetFunctions_add(self, WidgetOnCommand,
                          NULL_OnCommand, "NULL OnCommand");

    //typedef bbFlag bbWidget_OnCommand (bbWidget* widget,bbWidgetCommandType type, void* data);
    bbWidgetFunctions_add(self, WidgetOnCommand,
                           Textbox_OnCommand, "TEXTBOX");

    //typedef bbFlag bbWidget_OnTimer (bbWidget* widget, void* void_timerNode)
    bbWidgetFunctions_add(self, WidgetOnTimer,
                          NULL_OnTimer, "NULL OnTimer");

    return Success;
}

#endif //WIDGET_FUNCTIONS