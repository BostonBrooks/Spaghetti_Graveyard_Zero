/*
*bbFlag bbWidgetFunctions_populate(bbWidgetFunctions0* self)
{
//typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
//                                     bbWidgets* widgets, bbScreenPoints
//                                     screen_coords, bbWidget* parent);
bbWidgetFunctions_add(self, WidgetConstructor,
NULL_Constructor, "NULL Constructor");

bbWidgetFunctions_add(self, WidgetConstructor,
Sphere_Constructor, "Sphere");

bbWidgetFunctions_add(self, WidgetConstructor,
SPHERE_Constructor, "SPHERE");

//typedef bbFlag bbWidget_Update (bbWidget* widget, void* unused);
bbWidgetFunctions_add(self, WidgetUpdate,
NULL_Update, "NULL Update");

//typedef bbFlag bbWidget_Destructor (bbWidget* widget, void* unused);
bbWidgetFunctions_add(self, WidgetDestructor,
NULL_Destructor, "NULL Destructor");

//typedef bbFlag bbWidget_OnCommand (bbWidget* widget, void* data);
bbWidgetFunctions_add(self, WidgetOnCommand,
NULL_OnCommand, "NULL OnCommand");

//typedef bbFlag bbWidget_Mouse (bbWidget* widget, void* void_mouseEvent);
bbWidgetFunctions_add(self, WidgetMouseHandler,
NULL_Mouse, "NULL Mouse");

//typedef bbFlag bbWidget_Mouse (bbWidget* widget, void* void_mouseEvent);
bbWidgetFunctions_add(self, WidgetMouseHandler,
SPHERE_Mouse, "SPHERE");

//typedef bbFlag bbWidget_OnTimer (bbWidget* widget, void* void_timerNode)
bbWidgetFunctions_add(self, WidgetOnTimer,
NULL_OnTimer, "NULL OnTimer");

return Success;
}
*/

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