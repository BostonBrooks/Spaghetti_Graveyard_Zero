//BBWIDGETFUNCTIONENUMS_H are needed for
//bbFlag bbWidget_onCommand(bbWidget* widget, bbWidgets* widgets, bbWidgetCommandType type, bbPool_Handle data);


//ifndef statement avoids circular dependancy
#ifndef BBWIDGETFUNCTIONENUMS_H
#define BBWIDGETFUNCTIONENUMS_H


typedef enum
{
     WidgetConstructor,
     WidgetConstructor2,
     WidgetUpdate,
     WidgetDestructor,
     WidgetOnCommand,
     WidgetOnTimer,
     WidgetHide,
     WidgetUnhide
} bbWidgetFunctionType;

typedef enum bbWidgetCommandType
{
    bbWC_putChar,
    bbWC_putStr,
    bbWC_setBounds,
    bbWC_setDimensions,
    bbWC_setStr,
    bbWC_clrStr
} bbWidgetCommandType;

#endif //BBWIDGETFUNCTIONENUMS_H


#ifndef BBWIDGETFUNCTIONS_H
#define BBWIDGETFUNCTIONS_H

#include "engine/userinterface/bbWidget.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbDictionary.h"


typedef struct bbWidget bbWidget;
typedef struct bbWidgets bbWidgets;

typedef bbFlag bbWidget_Constructor2 (bbWidget** self,
                                      bbWidgets* widgets,
                                      bbWidget* parent,
                                      char* name,
                                      bbScreenPoints screen_points,
                                      bbGraphicsApp* graphics
                                      );

typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
                                     bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent);
typedef bbFlag bbWidget_Update (bbWidget* widget, void* unused);
typedef bbFlag bbWidget_Destructor (bbWidget* widget, void* unused);
typedef bbFlag bbWidget_OnCommand (bbWidget* widget, bbWidgetCommandType type, bbPool_Handle data);
typedef bbFlag bbWidget_OnTimer (bbWidget* widget, void* void_timerNode);
typedef bbFlag bbWidget_Hide (bbWidget* widget, bbWidgets* widgets);
typedef bbFlag bbWidget_UnHide (bbWidget* widget, bbWidgets* widgets);

typedef struct bbWidgetFunctions {
    bbWidget_Constructor** Constructors;
    bbDictionary* Constructor_dict;
    I32 Constructor_available;

    bbWidget_Constructor2** Constructors2;
    bbDictionary* Constructor2_dict;
    I32 Constructor2_available;

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

    void** OnTimers;
    bbDictionary* OnTimers_dict;
    I32 OnTimers_available;

    void** Hide;
    bbDictionary* Hide_dict;
    I32 Hide_available;

    void** Unhide;
    bbDictionary* Unhide_dict;
    I32 Unhide_available;
} bbWidgetFunctions;



bbFlag bbWidgetFunctions_new(bbWidgetFunctions** self);
bbFlag bbWidgetFunctions_populate(bbWidgetFunctions* self);
bbFlag bbWidgetFunctions_add(bbWidgetFunctions* functions, bbWidgetFunctionType fnType, void* fnPointer, char* key );
bbFlag bbWidgetFunctions_getFunction(void** function, bbWidgetFunctions* functions, bbWidgetFunctionType fnType, char* key);
I32 bbWidgetFunctions_getInt(bbWidgetFunctions* functions, bbWidgetFunctionType fnType, char* key);


#endif //BBWIDGETFUNCTIONS_H
