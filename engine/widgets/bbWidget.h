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

#include "engine/graphics/bbGraphics.h"
#include "engine/logic/bbTree.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/user_input/bbMouse.h"



#define FRAMES_PER_WIDGET 8

typedef struct {
    I32 Constructor;
    I32 Update;
    I32 Destructor;
    I32 OnCommand;
    I32 MouseHandler;
    I32 OnTimer;
} bbWidgetFunctionTable;

typedef struct {
    //It is important that "bbTree_Node tree;" is the first element
	bbTree_Node tree;
	bbScreenPointsRect rect;
	char label[KEY_LENGTH];
	char code[KEY_LENGTH]; //enter code to select spell
	char* display_str;
	sfText* display_text;
	I32 text_rows;
	I32 text_columns;
	I32 state;


    bbWidgetFunctionTable ftable;

    bbOnMouse onMouse;
    bbFrame frames[FRAMES_PER_WIDGET];

	void* extra_data;


} bbWidget;

typedef struct {
	bbVPool* pool;
	bbTree* tree;
	struct bbWidgetFunctions0* functions;
} bbWidgets;

typedef struct {
	bbMouseEvent* event;
	struct bbWidgetFunctions* functions;

	struct bbWidgetFunctions0* functions0;
	bbMouse* mouse;
} mouseActionClosure;

//typedef bbFlag bbDrawFunction(graphics,void* drawable, void* frameDescriptor, void* target);
//typedef bbFlag bWidget_DrawFunction(graphics,void* drawable, void* frameDescriptor, void* target);
typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
                                     bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent);
typedef bbFlag bbWidget_Update (bbWidget* widget, void* unused);
typedef bbFlag bbWidget_Destructor (bbWidget* widget, void* unused);
typedef bbFlag bbWidget_OnCommand (bbWidget* widget, void* data);
typedef bbFlag bbWidget_Mouse(bbWidget* widget, void* cl);
typedef bbFlag bbWidget_OnTimer (bbWidget* widget, void* void_timerNode);



typedef struct bbWidgetFunctions{
	bbWidget_Constructor** Constructors;  //functions to create a widget
	bbDictionary* Constructor_dict;       //create widget by label
	I32 Constructor_available;            //where to initialise new function

	bbWidget_Mouse** Mouse;
} bbWidgetFunctions;

bbFlag bbWidget_newEmpty(bbWidget** self, bbWidgets* widgets, bbWidget* parent);
bbFlag bbWidget_constructor(bbWidget** self, bbWidgets* widgets, bbGraphics* graphics, bbScreenPoints location, bbWidget* parent, char* key);
bbFlag bbWidget_draw(bbWidget* widget, drawFuncClosure* cl);
bbFlag bbWidget_mouse(bbWidget* widget, struct bbWidgetFunctions0* functions, void* cl);
bbFlag bbWidget_newLayout(bbWidget** self, bbGraphics* graphics, bbWidgets* widgets, bbWidget* parent);
bbFlag bbWidgets_init(bbWidgets* widgets);

bbFlag bbWidget_newMockViewport(bbWidget** self, bbGraphics* graphics, bbWidgets* widgets, bbWidget* parent);
bbFlag bbWidget_newViewport(bbWidget** self, bbGraphics* graphics,
                            bbWidgets* widgets, bbWidget* parent,
                            void* viewport);

//bbFlag testFunc(bbTree* tree, void* node, void* cl);
bbFlag bbWidget_drawFunc(bbTree* tree, void* node, void* cl);
bbFlag bbWidget_mouseFunc(bbTree* tree, void* node, void* cl);

bbFlag bbWidgets_draw(bbWidgets* widgets, void* cl);
bbFlag bbWidgets_onMouse(bbWidgets* widgets, void* cl);

#endif // BBWIDGET_H