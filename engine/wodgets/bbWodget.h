/**
 * the first element of bbWodget gives its place in a tree data structure
 * wodgets are drawn to the screen by doing a descending search of the tree
 * clicks are detected by doing an ascending search of the tree
 *
 * wodgets themselves are drawn to the screen much like how drawables are drawn
 * to the viewport, they share the same bbSprites, bbAnimations and bbCompositions
 * wodgets have a separate clock for calculating framerates so that wodgets can
 * be animated while the game is paused
 **/
#ifndef BBWODGET_H
#define BBWODGET_H

#include "engine/graphics/bbGraphics.h"
#include "engine/logic/bbTree.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/user_input/bbMouse.h"



#define FRAMES_PER_WODGET 8

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

    bbOnMouse onMouse;
    bbFrame frames[FRAMES_PER_WODGET];

	void* extra_data;


} bbWodget;

typedef struct {
	bbVPool* pool;
	bbTree* tree;
} bbWodgets;

typedef struct {
	bbMouseEvent* event;
	struct bbWodgetFunctions* functions;

} mouseActionClosure;

//typedef bbFlag bbDrawFunction(graphics,void* drawable, void* frameDescriptor, void* target);
//typedef bbFlag bWodget_DrawFunction(graphics,void* drawable, void* frameDescriptor, void* target);
typedef bbFlag bbWodget_Constructor (bbWodget** reference, void* wodgets, bbScreenPoints screen_coords, bbWodget* parent);
typedef bbFlag bbWodget_Update (bbWodget* wodget, void* unused);
typedef bbFlag bbWodget_Destructor (bbWodget* wodget, void* unused);
typedef bbFlag bbWodget_OnCommand (bbWodget* wodget, void* data);
typedef bbFlag bbWodget_Mouse(void* void_mouseEvent, void* void_wodget);
typedef bbFlag bbWodget_OnTimer (bbWodget* wodget, void* void_timerNode);



typedef struct bbWodgetFunctions{
	bbWodget_Constructor** Constructors;  //functions to create a wodget
	bbDictionary* Constructor_dict;       //create wodget by label
	I32 Constructor_available;            //where to initialise new function

	bbWodget_Mouse** Mouse;
} bbWodgetFunctions;

bbFlag bbWodget_newEmpty(bbWodget** self, bbWodgets* wodgets, bbWodget* parent);
bbFlag bbWodget_draw(bbWodget* wodget, drawFuncClosure* cl);
bbFlag bbWodget_mouse(bbWodget* wodget, bbMouseEvent* mouseEvent, bbWodgetFunctions* functions);
bbFlag bbWodget_newLayout(bbWodget** self, bbGraphics* graphics, bbWodgets* wodgets, bbWodget* parent);
bbFlag bbWodgets_init(bbWodgets* wodgets);

bbFlag bbWodget_newMockViewport(bbWodget** self, bbGraphics* graphics, bbWodgets* wodgets, bbWodget* parent);
bbFlag bbWodget_newViewport(bbWodget** self, bbGraphics* graphics,
                            bbWodgets* wodgets, bbWodget* parent,
                            void* viewport);

//bbFlag testFunc(bbTree* tree, void* node, void* cl);
bbFlag bbWodget_drawFunc(bbTree* tree, void* node, void* cl);
bbFlag bbWodget_mouseFunc(bbTree* tree, void* node, void* cl);

bbFlag bbWodgets_draw(bbWodgets* wodgets, void* cl);
bbFlag bbWodgets_onMouse(bbWodgets* wodgets, void* cl);

#endif // BBWODGET_H