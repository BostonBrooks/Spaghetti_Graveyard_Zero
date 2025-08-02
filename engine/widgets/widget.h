/**
* @file
 * @brief bbWidgets are things like menu buttons, text prompts, click to cast spells etc.
*/
#ifndef BBWIDGET_H
#define BBWIDGET_H

#include "engine/graphics/bbGraphics.h"
#include "engine/logic/bbTree.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/user_input/bbMouse.h"
#include "engine/logic/bbLeanPool.h"

#define bbWidgetPool bbLeanPool
#define bbWidgetPool_new bbLeanPool_new
#define bbWidgetPool_delete bbLeanPool_delete
#define bbWidgetPool_resize bbLeanPool_resize
#define bbWidgetPool_clear bbLeanPool_clear
#define bbWidgetPool_alloc bbLeanPool_alloc
#define bbWidgetPool_free bbLeanPool_free
#define bbWidgetPool_lookup bbLeanPool_lookup
#define bbWidgetPool_reverseLookup bbLeanPool_reverseLookup
#define bbWidgetPool_handleIsEqual bbLeanPool_handleIsEqual








// bbWidget is a state machine
#define s_Idle              0
#define s_WaitingForCode    1
#define s_WaitingForAnswer  2
#define s_WaitingForClick   3


#define FRAMES_PER_WIDGET 8

typedef struct
{
    bbTree_Node tree;
    bbScreenPointsRect rect;
    char label[KEY_LENGTH];
    char code[KEY_LENGTH]; //enter code to select spell
    char* display_str;
    sfText* display_text;
    I32 text_rows;
    I32 text_columns;
    I32 state;

    I32 onMouse;
    bbFrame frames[FRAMES_PER_WIDGET];

    void* extra_data;
} bbWidget;

// Numbers represent widget function types
#define f_WidgetConstructor     0
#define f_WidgetUpdate          1
#define f_WidgetDestructor      2
#define f_WidgetOnCommand       3
#define f_WidgetDrawFunction    4
#define f_WidgetMouseHandler    5
#define f_WidgetOnTimer         6

//types of member functions for class bbWidget
typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* widgets, bbScreenPoints screen_coords, bbWidget* parent);
typedef bbFlag bbWidget_Update (bbWidget* widget, void* unused);
typedef bbFlag bbWidget_Destructor (bbWidget* widget, void* unused);
typedef bbFlag bbWidget_OnCommand (bbWidget* widget, void* data);
typedef bbFlag bbWidget_DrawFunction (bbWidget* widget, I32 i);
typedef bbFlag bbWidget_Mouse(void* void_mouseEvent, void* void_widget);
typedef bbFlag bbWidget_OnTimer (bbWidget* widget, void* void_timerNode);

// container for functions belonging to bbWidgets
typedef struct
{
    bbWidget_Constructor** constructors;
    bbDictionary* constructor_dict;
    I32 num_constructors;

    bbWidget_Update** updates;
    bbDictionary* update_dict;
    I32 num_updates;

    bbWidget_Destructor** destructors;
    bbDictionary* destructor_dict;
    I32 num_destructors;

    bbWidget_OnCommand** onCommands;
    bbDictionary* onCommand_dict;
    I32 num_onCommands;

    bbWidget_DrawFunction** drawFunction;
    bbDictionary* drawFunction_dict;
    I32 num_drawFunctions;

    bbWidget_Mouse** mouseHandler;
    bbDictionary* mouseHandler_dict;
    I32 num_mouseHandlers;

    bbWidget_OnTimer** onTimers;
    bbDictionary* onTimers_dict;
    I32 num_onTimers;


} bbWidgetFunctions;

//widget subsystem
typedef struct
{
    //contains widgets
    bbWidgetPool* widgets;
    //names of widgets
    bbDictionary* addresses;
    //enter code to select widget
    bbDictionary* codes;
    bbWidgetFunctions* functions;
    //root widget
    bbWidget* layout;
    //accepts key presses
    bbWidget* prompt;
    //viewport into game world
    bbWidget* viewport;
} bbWidgets;

//defined in /games/game0/maps/map0/widgets
bbFlag bbWidgetFunctions_new(bbWidgetFunctions** self);
bbFlag bbWidgetFunctions_add(bbWidgetFunctions* functions, I32 fnType, void* fnPtr, char* key);
bbFlag bbWidgetFunctions_getFunction(void** function, bbWidgetFunctions* functions, I32 fnType, char* key);

// find value to be stored in "I32 onMouse;" in bbWidget
bbFlag bbWidgetFunctions_getInt(bbWidgetFunctions* functions, I32 fnType, char* key);

/*
 * bbWidget_new
 * bbWidget_draw
 * bbWidget_mouse
 * bbWidget_onCommand
 * bbWidget_onUpdate
 * bbWidget_onTimer
 * bbWidget_newEmpty
 *
 * ...
 *
 */