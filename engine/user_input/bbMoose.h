//bbMoose is the new and improved mouse object that is a part of bbWidgets and interacts with the bbWidgets
//bbMoose* moose is a member of bbInput and bbWidgets
#ifndef BBMOOSE_H
#define BBMOOSE_H

#include "engine/graphics/bbGraphics.h"
#include "engine/logic/bbTree.h"
#include "engine/geometry/bbCoordinates.h"
//#include "engine/widgets/bbWidget.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbVPool.h"
#include "engine/user_input/bbMooseFunctions.h"

//data stored in bbWidget, informs the object how to interact with the mouse

typedef struct
{
    I32 isOver;
    I32 Enter;
    I32 Leave;
    I32 LeftDown;
    I32 RightDown;
    I32 LeftUp;
    I32 RightUp;
    I32 Drag;
    I32 Drop;
    I32 MouseIcon;
    I32 DragIcon;
} bbMooseTable;






typedef struct bbMoose
{
    bbScreenPoints position;
    bbScreenPoints previousPosition;
    unsigned int leftDown : 1;
    unsigned int rightDown : 1;
    unsigned int leftChanged : 1;
    unsigned int rightChanged : 1;
    //what if mouse button is down but nothing is selected?
    // PS we have bbVPool.null
    // and I32 bbVPool_handleIsEqual(bbVPool* pool, bbPool_Handle A, bbPool_Handle B);

    //wasOver == null indicates isover has not change
    bbPool_Handle wasOver;
    bbPool_Handle isOver;
    bbPool_Handle selected;
    I32 defaultMouseIcon;

    bbMooseFunctions functions;
} bbMoose;

//cl contains pointers to whatever systems are needed
typedef struct
{
    int unused;
} bbMoose_isOver_cl;

//Needs to know the pool used for widgets...
bbFlag bbMoose_Init(bbMoose* moose, void* widgets, bbGraphics* graphics);

//Figure out what widget the mouse is over
bbFlag bbMoose_isOver(bbMoose* moose, void* widgets);

bbFlag bbMoose_Event(bbMoose* moose, sfEvent* event);
//Interact with widgets, may have to look up sprite int in dictionary
bbFlag bbMoose_Update(bbMoose* moose, void* widgets, bbGraphics* graphics);

//Draw mouse to screen, depending on what widget is selected and what is under the mouse
bbFlag bbMoose_Draw(bbMoose* moose, struct bbWidgets* widgets, bbGraphics* graphics);

//Function to be called recursively
bbFlag bbMoose_isOverFunc(bbTree* tree, void* node, void* cl);
#endif // BBMOOSE_H


/*
 * bbFlag bbInput_poll(bbInput* input, sfRenderWindow* window, bbMouse* mouse, bbMoose* moose);
 *     updates bbMoose bbFlag bbMoose_Event(bbMoose* moose, sfEvent* event)
 *
 * bbFlag bbMoose_Update(bbMoose* moose, struct bbWidgets* widgets, bbGraphics* graphics);
 *     calls bbFlag bbMoose_isOver(bbMoose* moose, struct bbWidgets* widgets);
 *
 * bbFlag bbMoose_isOver(bbMoose* moose, struct bbWidgets* widgets);
 *     calls bbTree_ascendingMapVisible with bbMoose_isOverFunc and cl
 *
 * bbFlag bbMoose_isOverFunc(bbTree* tree, void* node, void* cl)
 *     looks up function given by node.functions.isOver
 *
 * cl contains pointers to whatever systems are needed
 *
 * function given by node.functions.isOver
 *     is type bbFlag bbMoose_IsOver(bbMoose* moose, bbWidgets* widgets, bbWidget* widget);
 *     updates bbMoose.isOver and bbMoose.wasOver and returns Break
 *     OR returns Continue
 *
 * bbMoose_Update
 *     calls appropriate functions from bbWidget.mtable
 *     clears bbMoose.leftChanged and bbMoose.rightChanged
 *
 * bbMoose_Draw
 *     looks up isOver.MouseIcon and selected.DragIcon and draws them to the screen
 */