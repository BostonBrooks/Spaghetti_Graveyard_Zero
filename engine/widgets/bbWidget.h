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



#define FRAMES_PER_WIDGET 8

typedef struct {
	bbTree_Node tree;
	bbScreenPointsRect rect;
	char label[KEY_LENGTH];
	char code[KEY_LENGTH]; //enter code to select spell
	char* display_str;
	sfText* display_text;
	I32 text_rows;
	I32 text_columns;
	I32 state;

	void* extra_data;

	bbFrame frames[FRAMES_PER_WIDGET];

} bbWidget;

typedef struct {
	bbVPool* pool;
	bbTree* tree;
} bbWidgets;

//typedef bbFlag bbDrawFunction(graphics,void* drawable, void* frameDescriptor, void* target);
//typedef bbFlag bWidget_DrawFunction(graphics,void* drawable, void* frameDescriptor, void* target);
typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* widgets, bbScreenPoints screen_coords, bbWidget* parent);
typedef bbFlag bbWidget_Update (bbWidget* widget, void* unused);
typedef bbFlag bbWidget_Destructor (bbWidget* widget, void* unused);
typedef bbFlag bbWidget_OnCommand (bbWidget* widget, void* data);
typedef bbFlag bbWidget_Mouse(void* void_mouseEvent, void* void_widget);
typedef bbFlag bbWidget_OnTimer (bbWidget* widget, void* void_timerNode);



typedef struct {
	bbWidget_Constructor** Constructors;  //functions to create a widget
	bbDictionary* Constructor_dict;       //create widget by label
	I32 Constructor_available;            //where to initialise new function

} bbWidgetFunctions;

bbFlag bbWidget_newEmpty(bbWidget** self, bbWidgets* widgets, bbWidget* parent);
bbFlag bbWidget_draw(bbGraphics* graphics, bbWidget* widget, void* target, I32 mapTime);
bbFlag bbWidget_layoutNew(bbWidget** self, bbGraphics* graphics, bbWidgets* widgets, bbWidget* parent);
bbFlag bbWidgets_init(bbWidgets* widgets);

bbFlag bbWidget_viewportNew(bbWidget** self, bbGraphics* graphics, bbWidgets* widgets, bbWidget* parent);

typedef struct {
	bbGraphics* graphics;
	void* target;
	I32 GUI_time;
	I32 mapTime;
} targets;
bbFlag drawFunc(bbTree* tree, void* node, void* cl);

#endif // BBWIDGET_H