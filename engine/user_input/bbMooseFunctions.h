//Much like bbWidgetFunctions
#ifndef BBMOOSEFUNCTIONS_H
#define BBMOOSEFUNCTIONS_H

#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbIntTypes.h"

typedef enum
{
    MooseIsOver,
    MooseEnter,
    MooseLeave,
    MooseLeftDown,
    MooseLeftUp
} MooseFunctionType;

typedef bbFlag bbMoose_IsOver (void* moose, void* widgets, void* widget);
typedef bbFlag bbMoose_Enter (void* moose, void* widgets, void* widget, void* graphics);
typedef bbFlag bbMoose_Leave (void* moose, void* widgets, void* widget, void* graphics);
typedef bbFlag bbMoose_LeftDown (void* moose, void* widgets, void* widget,
                                 void* graphics);
typedef bbFlag bbMoose_LeftUp (void* moose, void* widgets, void* widget,
                               void* graphics);

typedef struct
{
    bbMoose_IsOver** IsOver;
    bbDictionary* IsOver_dict;
    I32 IsOver_available;

    bbMoose_Enter** Enter;
    bbDictionary* Enter_dict;
    I32 Enter_available;

    bbMoose_Leave** Leave;
    bbDictionary* Leave_dict;
    I32 Leave_available;

    bbMoose_LeftDown** LeftDown;
    bbDictionary* LeftDown_dict;
    I32 LeftDown_available;

    bbMoose_LeftUp** LeftUp;
    bbDictionary* LeftUp_dict;
    I32 LeftUp_available;

}bbMooseFunctions;

bbFlag bbMooseFunctions_init(bbMooseFunctions* functions);
bbFlag bbMooseFunctions_populate(bbMooseFunctions* self);
bbFlag bbMooseFunctions_add(bbMooseFunctions* functions, MooseFunctionType fnType, void* fnPointer, char* key );
bbFlag bbMooseFunctions_getFunction(void** function, bbMooseFunctions* functions, MooseFunctionType fnType, char* key);
I32 bbMooseFunctions_getInt(bbMooseFunctions* functions, MooseFunctionType fnType, char* key);


#endif
