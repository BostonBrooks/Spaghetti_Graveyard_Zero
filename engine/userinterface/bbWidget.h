/**
 * the first element of bbWidget gives its place in a tree data structure
 * widgets are drawn to the screen by doing a descending search of the tree
 * clicks are detected by doing an ascending search of the tree
 *
 * widgets themselves are drawn to the screen much like how drawables are drawn
 * to the viewport, they share the same bbSprites, bbAnimations and bbCompositions
 * widgets have a separate clock for calculating framerates so that widgets can
 * be animated while the game is paused
 **/
#ifndef BBWIDGET_H
#define BBWIDGET_H

#include "engine/graphics/bbGraphicsApp.h"
#include "engine/logic/bbTree.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/userinterface/bbMouse.h"
#include "engine/userinterface/bbWidgetFunctions.h"

typedef enum bbWidget_Type
{
	bbWidgetType_None,
	bbWidgetType_TextBox,
    bbWidgetType_SpellSelector,
    bbWidgetType_SpellSlot,
    bbWidgetType_CurrentSpell
} bbWidget_Type;

typedef enum bbWidget_state
{
	bbWidgetState_Default,
	bbWidgetState_Hover,
	bbWidgetState_Click,

	//TODO should this be a state or a separate bool?
	bbWidgetState_Frozen,
} bbWidget_state;


#define FRAMES_PER_WIDGET 8

typedef struct {
    I32 Constructor;
    I32 Update;
    I32 Destructor;
    I32 OnCommand;
    I32 OnTimer;
    I32 Hide;
    I32 Unhide;
} bbWidgetFunctionTable;

typedef struct bbWidget_TextBox
{
	I32 rows;
	I32 columns;
	char* string;
	sfText* text;
	sfFont* font;
}bbWidget_TextBox;

typedef union bbWidget_TypeData
{
	bbWidget_TextBox textBox;
} bbWidget_TypeData;

typedef struct bbWidget{
    //It is important that "bbTree_Node tree;" is the first element
	bbTree_Node tree;
	bbScreenPointsRect rect;
	bbMouseTable mtable;
	bbWidgetFunctionTable ftable;
    bbFrame frames[FRAMES_PER_WIDGET];
	bbWidget_Type type;
	bbWidget_state state;
	bool isFrozen;
	bbWidget_TypeData typeData;
    char key[64];




	void* extra_data;


} bbWidget;

typedef struct bbWidgets {
	bbVPool* pool;
	bbTree* tree;
	struct bbWidgetFunctions* functions;
	bbMouse* mouse;
    bbDictionary* dict;
	bbWidget* dialog;
	bbWidget* prompt;
	bbWidget* command;
    bbWidget* currentSpell;
    bbWidget* spellMenu;
	bbWidget* textbox;

} bbWidgets;


bbFlag bbWidget_newEmpty(bbWidget** self, bbWidgets* widgets, bbWidget* parent);

bbFlag bbWidget_newEmpty2(bbWidget** self, bbWidgets* widgets, bbWidget* parent, char* name);


//TODO key is for locating constructor, add a second key for adding the widget to the dictionary
bbFlag bbWidget_constructor(bbWidget** self, bbWidgets* widgets, bbGraphicsApp* graphics, bbScreenPoints location, bbWidget* parent, char* key);

bbFlag bbWidget_constructor2(bbWidget** self,
							 bbWidgets* widgets,
							 char* type,
							 char* parent,
							 char* name,
							 I32 position_x,
							 I32 position_y);

bbFlag bbWidget_onCommand(bbWidget* widget, bbWidgets* widgets, bbWidgetCommandType type, bbPool_Handle data);
bbFlag bbWidget_draw(bbWidget* widget, drawFuncClosure* cl);
bbFlag bbWidget_newLayout(bbWidget** self, bbGraphicsApp* graphics, bbWidgets* widgets, bbWidget* parent);
bbFlag bbWidgets_init(bbWidgets* widgets);
bbFlag bbWidget_hide(bbWidget* widget, bbWidgets* widgets);
bbFlag bbWidget_unhide(bbWidget* widget, bbWidgets* widgets);
//bbFlag bbWidget_newMockViewport(bbWidget** self, bbGraphicsApp* graphics, bbWidgets* widgets, bbWidget* parent);
bbFlag bbWidget_newViewport(bbWidget** self, bbGraphicsApp* graphics,
                            bbWidgets* widgets, bbWidget* parent,
                            void* viewport);

//bbFlag testFunc(bbTree* tree, void* node, void* cl);
bbFlag bbWidget_drawFunc(bbTree* tree, void* node, void* cl);
bbFlag bbWidgets_draw(bbWidgets* widgets, void* cl);

#endif // BBWIDGET_H