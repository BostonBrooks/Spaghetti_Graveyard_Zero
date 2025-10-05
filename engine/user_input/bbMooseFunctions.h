//Much like bbWidgetFunctions
#ifndef BBMOOSEFUNCTIONS_H
#define BBMOOSEFUNCTIONS_H

#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbIntTypes.h"

typedef enum
{
    MooseIsOver,
    MooseEnter
} MooseFunctionType;

typedef bbFlag bbMoose_IsOver (struct bbMoose* moose, struct bbWidgets* widgets, struct bbWidget* widget);

typedef struct
{
    bbMoose_IsOver** IsOver;
    bbDictionary* IsOver_dict;
    I32 IsOver_available;

}bbMooseFunctions;

bbFlag bbMooseFunctions_init(bbMooseFunctions* functions);
bbFlag bbMooseFunctions_populate(bbMooseFunctions* self);
bbFlag bbMooseFunctions_add(bbMooseFunctions* functions, MooseFunctionType fnType, void* fnPointer, char* key );
bbFlag bbMooseFunctions_getFunction(void** function, bbMooseFunctions* functions, MooseFunctionType fnType, char* key);
I32 bbMooseFunctions_getInt(bbMooseFunctions* functions, MooseFunctionType fnType, char* key);


#endif
