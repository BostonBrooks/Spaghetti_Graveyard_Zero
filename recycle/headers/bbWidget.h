/**
 * @file
 * @brief bbWidgets are things like menu buttons, text prompts, click to cast spells etc.
*/
#ifndef BBWIDGET_H
#define BBWIDGET_H
#include <stdbool.h>
#include "bbSystemIncludes.h"
#include "bbPool.h"
#include "bbTree.h"
#include "bbDictionary.h"
#include "bbGeometry.h"
#include "bbMouse.h"
#include "bbIntTypes.h"

// bbWidget is a state machine
#define s_Idle              0
#define s_WaitingForCode    1
#define s_WaitingForAnswer  2
#define s_WaitingForClick   3

#define subwidgetarraysize 8
typedef struct{
	bbNode p_Node;

    I32 m_SubwidgetArray[subwidgetarraysize];

	bbScreenCoordsI m_ScreenCoords;
	bbScreenCoordsI m_Dimensions;
	char* m_String;
	char* m_String2;
	sfText* m_Text;
    I32 m_TextRows;
    I32 m_TextColumns;
	char* m_Code;
	sfRenderTexture* m_RenderTexture;
	sfSprite* m_Sprite;


	I32 m_AnimationInt[ANIMATIONS_PER_WIDGET];
	I32 m_Angle[ANIMATIONS_PER_WIDGET];
	I32 m_Frame[ANIMATIONS_PER_WIDGET];
	I32 v_DrawFunction[ANIMATIONS_PER_WIDGET];
    I32 m_AnimationStart[ANIMATIONS_PER_WIDGET];

    I32 s_State;
	I32 v_OnCommand;
	I32 v_OnUpdate;
	I32 v_OnDelete;
    I32 v_OnMouse;
    I32 v_OnTimer;

    I32 m_CoolDownStart;
    I32 m_CoolDownEnd;
    sfRectangleShape* m_RedRect;
    sfRectangleShape* m_GreenRect;


	void* m_ExtraData;

} bbWidget;

// Numbers represent widget function types
#define f_WidgetConstructor     0
#define f_WidgetUpdate          1
#define f_WidgetDestructor      2
#define f_WidgetOnCommand       3
#define f_WidgetDrawFunction    4
#define f_WidgetMouseHandler    5
#define f_WidgetOnTimer         6


typedef I32 bbWidget_Constructor (bbWidget** reference, void* widgets, bbScreenCoordsI screen_coords, bbWidget* parent);
typedef I32 bbWidget_Update (bbWidget* widget, void* unused);
typedef I32 bbWidget_Destructor (bbWidget* widget, void* unused);
typedef I32 bbWidget_OnCommand (bbWidget* widget, void* data);
typedef I32 bbWidget_DrawFunction (bbWidget* widget, I32 i);
typedef I32 bbWidget_Mouse(void* void_mouseEvent, void* void_widget);
typedef I32 bbWidget_OnTimer (bbWidget* widget, void* void_timerNode);

typedef struct {
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
	bbWidget_DrawFunction** DrawFunction;
	bbDictionary* DrawFunction_dict;
	I32 DrawFunction_available;
    bbWidget_Mouse** MouseHandler;
    bbDictionary* MouseHandler_dict;
    I32 MouseHandler_available;
    bbWidget_Mouse** OnTimers;
    bbDictionary* OnTimers_dict;
    I32 OnTimers_available;
} bbWidgetFunctions;


typedef struct {
	bbPool* m_Pool;
    ///reference widgets by key
	bbDictionary* m_AddressDict;
    ///enter code "key" to activate widget at "address"
	bbDictionary* m_CodeDict;
    bbWidgetFunctions* m_Functions;
    ///the root widget in the hierarchy
	bbWidget* m_Layout;
    ///key events are passed to this widget
	bbWidget* m_Prompt;
    ///manages spell casting
    bbWidget* m_SpellBar;
	///viewport of game world
	bbWidget* m_Viewport;
} bbWidgets;

I32 bbWidgets_new(I32 map);
I32 bbWidgetFunctions_new(I32 map);

I32 bbWidgetFunctions_populate(I32 map);
I32 bbWidgetFunctions_add(bbWidgetFunctions* WFS, I32 bin, void* pointer, char* key );
I32 bbWidgetFunctions_getFunction(void** function, bbWidgetFunctions* WFS, I32 bin, char* key);
I32 bbWidgetFunctions_getInt(bbWidgetFunctions* WFS, I32 bin, char* key);

I32 bbWidget_new(bbWidget** self, bbWidgets* widgets , I32 type, I32 parent, bbScreenCoordsI SCI);

//typedef I32 bbTreeFunction (void* reference, void* node);
I32 bbWidget_draw(void* void_unused, void* void_widget);
I32 bbWidget_mouse(void* void_mouseEvent, void* void_widget);
I32 bbWidget_onCommand(void* command, void* void_widget);
I32 bbWidget_onUpdate(void* unused, void* void_widget);
I32 bbWidget_onTimer(void* void_timerNode, void* void_widget);

I32 bbWidget_empty_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent);


void bbDialog(const char* format, ...);
#endif //BBWIDGET_H
