#ifndef BBWIDGETFUNCTIONS_H
#define BBWIDGETFUNCTIONS_H

#include "engine/widgets/bbWidget.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbDictionary.h"

typedef enum
{
     WidgetConstructor,
     WidgetUpdate,
     WidgetDestructor,
     WidgetOnCommand,
     WidgetMouseHandler,
     WidgetOnTimer
} WidgetFunctionType;

//typedef struct bbWidget bbWidget;

typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
                                     bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent);
typedef bbFlag bbWidget_Update (bbWidget* widget, void* unused);
typedef bbFlag bbWidget_Destructor (bbWidget* widget, void* unused);
typedef bbFlag bbWidget_OnCommand (bbWidget* widget, void* data);
typedef bbFlag bbWidget_Mouse (bbWidget* widget, void* void_mouseEvent);
typedef bbFlag bbWidget_OnTimer (bbWidget* widget, void* void_timerNode);

typedef struct bbWidgetFunctions0 {
     bbWidget_Constructor** Constructors;
     bbDictionary* Constructor_dict;
     I32 Constructor_available;

     bbWidget_Update** Update;
     bbDictionary* Update_dict;
     I32 Update_available;

     bbWidget_Destructor** Destructors;
     bbDictionary* Destructor_dict;
     I32 Destructor_available;

     //includes on click and on prompt?
     bbWidget_OnCommand** OnCommands;
     bbDictionary* OnCommand_dict;
     I32 OnCommand_available;

     bbWidget_Mouse** MouseHandler;
     bbDictionary* MouseHandler_dict;
     I32 MouseHandler_available;

     bbWidget_Mouse** OnTimers;
     bbDictionary* OnTimers_dict;
     I32 OnTimers_available;
} bbWidgetFunctions0;



bbFlag bbWidgetFunctions_new(bbWidgetFunctions0** self);
bbFlag bbWidgetFunctions_populate(bbWidgetFunctions0* self);
bbFlag bbWidgetFunctions_add(bbWidgetFunctions0* functions, WidgetFunctionType fnType, void* fnPointer, char* key );
bbFlag bbWidgetFunctions_getFunction(void** function, bbWidgetFunctions0* functions, WidgetFunctionType fnType, char* key);
I32 bbWidgetFunctions_getInt(bbWidgetFunctions0* functions, WidgetFunctionType fnType, char* key);

#endif //BBWIDGETFUNCTIONS_H
