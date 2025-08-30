#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidgetFunctions.h"

bbFlag bbWidgetFunctions_populate(bbWidgetFunctions0** self)
{
    //typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* widgets, bbScreenPoints screen_coords, bbWidget* parent);
    bbWidgetFunctions_add(self, WidgetConstructor, NULL, "aConstructor");

    //typedef bbFlag bbWidget_Update (bbWidget* widget, void* unused);
    bbWidgetFunctions_add(self, WidgetUpdate, NULL, "anUpdator");

    //typedef bbFlag bbWidget_Destructor (bbWidget* widget, void* unused);
    bbWidgetFunctions_add(self, WidgetDestructor, NULL, "aDestructor");

    //typedef bbFlag bbWidget_OnCommand (bbWidget* widget, void* data);
    bbWidgetFunctions_add(self, WidgetOnCommand, NULL, "OnCommand");

    //typedef bbFlag bbWidget_Mouse (void* void_mouseEvent, void* void_widget);
    bbWidgetFunctions_add(self, WidgetMouseHandler, NULL, "aMouseHandler");

    //typedef bbFlag bbWidget_OnTimer (bbWidget* widget, void* void_timerNode)
    bbWidgetFunctions_add(self, WidgetOnTimer, NULL, "anOTimer");

}