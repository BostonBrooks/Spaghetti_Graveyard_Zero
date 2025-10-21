//Widgetes used: Layout, viewport, button, box

#ifndef WIDGET_FUNCTIONS
#define WIDGET_FUNCTIONS

#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidgetFunctions.h"

#include "games/game0/maps/map0/widgets/nullfunctions.h"
#include "games/game0/maps/map0/widgets/sphere.h"
#include "games/game0/maps/map0/widgets/button.h"
#include "games/game0/maps/map0/widgets/box.h"
#include "games/game0/maps/map0/widgets/card.h"


bbFlag bbWidgetFunctions_populate(bbWidgetFunctions0* self)
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
                          Card_Constructor, "CARD");

    //typedef bbFlag bbWidget_Update (bbWidget* widget, void* unused);
    bbWidgetFunctions_add(self, WidgetUpdate,
                          NULL_Update, "NULL Update");

    //typedef bbFlag bbWidget_Destructor (bbWidget* widget, void* unused);
    bbWidgetFunctions_add(self, WidgetDestructor,
                          NULL_Destructor, "NULL Destructor");

    //typedef bbFlag bbWidget_OnCommand (bbWidget* widget, void* data);
    bbWidgetFunctions_add(self, WidgetOnCommand,
                          NULL_OnCommand, "NULL OnCommand");

    //typedef bbFlag bbWidget_OnTimer (bbWidget* widget, void* void_timerNode)
    bbWidgetFunctions_add(self, WidgetOnTimer,
                          NULL_OnTimer, "NULL OnTimer");

    return Success;
}

#endif //WIDGET_FUNCTIONS