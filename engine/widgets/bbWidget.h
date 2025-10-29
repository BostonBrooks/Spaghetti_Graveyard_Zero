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

typedef enum bbWidget_Type
{
	bbWidgetType_None,
	bbWidgetType_TextBox
} bbWidget_Type;


#define FRAMES_PER_WIDGET 8

typedef struct {
    I32 Constructor;
    I32 Update;
    I32 Destructor;
    I32 OnCommand;
    I32 OnTimer;
} bbWidgetFunctionTable;

typedef struct bbWidget_TextBox
{
	I32 textRows;
	I32 textColumns;
	char* string;
	sfText* text;
	sfFont* font;
}bbWidget_TextBox;

typedef union bbWidget_TypeData
{
	bbWidget_TextBox* textBox;
} bbWidget_TypeData;

typedef struct bbWidget{
    //It is important that "bbTree_Node tree;" is the first element
	bbTree_Node tree;
	bbScreenPointsRect rect;
	bbMouseTable mtable;
	bbWidgetFunctionTable ftable;
    bbFrame frames[FRAMES_PER_WIDGET];
	bbWidget_Type type;
	bbWidget_TypeData typeData;




	void* extra_data;


} bbWidget;

typedef struct bbWidgets {
	bbVPool* pool;
	bbTree* tree;
	struct bbWidgetFunctions0* functions;

    //TODO should this be here?
    //For now it's too hard to unroll this
	bbMouse* mouse;
} bbWidgets;


//typedef bbFlag bbDrawFunction(graphics,void* drawable, void* frameDescriptor, void* target);
//typedef bbFlag bWidget_DrawFunction(graphics,void* drawable, void* frameDescriptor, void* target);
typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
                                     bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent);
typedef bbFlag bbWidget_Update (bbWidget* widget, void* unused);
typedef bbFlag bbWidget_Destructor (bbWidget* widget, void* unused);
typedef bbFlag bbWidget_OnCommand (bbWidget* widget, void* data);
typedef bbFlag bbWidget_OnTimer (bbWidget* widget, void* void_timerNode);



typedef struct bbWidgetFunctions{
	bbWidget_Constructor** Constructors;  //functions to create a widget
	bbDictionary* Constructor_dict;       //create widget by label
	I32 Constructor_available;            //where to initialise new function

} bbWidgetFunctions;

bbFlag bbWidget_newEmpty(bbWidget** self, bbWidgets* widgets, bbWidget* parent);
bbFlag bbWidget_constructor(bbWidget** self, bbWidgets* widgets, bbGraphics* graphics, bbScreenPoints location, bbWidget* parent, char* key);
bbFlag bbWidget_draw(bbWidget* widget, drawFuncClosure* cl);
bbFlag bbWidget_newLayout(bbWidget** self, bbGraphics* graphics, bbWidgets* widgets, bbWidget* parent);
bbFlag bbWidgets_init(bbWidgets* widgets);

bbFlag bbWidget_newMockViewport(bbWidget** self, bbGraphics* graphics, bbWidgets* widgets, bbWidget* parent);
bbFlag bbWidget_newViewport(bbWidget** self, bbGraphics* graphics,
                            bbWidgets* widgets, bbWidget* parent,
                            void* viewport);

//bbFlag testFunc(bbTree* tree, void* node, void* cl);
bbFlag bbWidget_drawFunc(bbTree* tree, void* node, void* cl);

bbFlag bbWidgets_draw(bbWidgets* widgets, void* cl);

#endif // BBWIDGET_H