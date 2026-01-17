//bbMouse is the new and improved mouse object that is a part of bbWidgets and interacts with the bbWidgets
//bbMouse* mouse is a member of bbInput and bbWidgets
#ifndef BBMOOSE_H
#define BBMOOSE_H

#include "engine/graphics/bbGraphicsApp.h"
#include "engine/logic/bbTree.h"
#include "engine/geometry/bbCoordinates.h"
//#include "engine/widgets/bbWidget.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbVPool.h"
#include "engine/userinterface/bbMouseFunctions.h"

//data stored in bbWidget, informs the object how to interact with the mouse using virtual functions found in vtables

typedef struct
{
    //virtual functions
    I32 isOver;
    I32 Enter;
    I32 Leave;
    I32 LeftDown;
    I32 RightDown;
    I32 LeftUp;
    I32 RightUp;
    I32 LeftDrag;
    I32 RightDrag;
    I32 Drop;
    I32 MouseIcon;
    I32 DragIcon;
    bbMouse_onClick* OnClick;
    bbMouse_onClick* OnUnClick;
    //todo OnClick EG connect to a network

    //book keeping data
    unsigned int hover : 1;
    unsigned int selected : 1;
} bbMouseTable;





typedef struct bbMouse
{
    bbScreenPoints position;
    bbScreenPoints previousPosition;
    bbScreenPoints dragOrigin;
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

    bbMouseFunctions functions;
} bbMouse;

//cl contains pointers to whatever systems are needed
typedef struct
{
    void* widgets;
} bbMouse_isOver_cl;



//Needs to know the pool used for widgets...
bbFlag bbMouse_Init(bbMouse* mouse, void* widgets, bbGraphicsApp* graphics);

//Figure out what widget the mouse is over
bbFlag bbMouse_isOver(bbMouse* mouse, void* widgets);

bbFlag bbMouse_Event(bbMouse* mouse, sfEvent* event);
//Interact with widgets, may have to look up sprite int in dictionary
bbFlag bbMouse_Update(bbMouse* mouse, void* widgets, bbGraphicsApp* graphics);

//Draw mouse to screen, depending on what widget is selected and what is under the mouse
bbFlag bbMouse_Draw(bbMouse* mouse, void* widgets, bbGraphicsApp* graphics, sfRenderWindow* window);

bbFlag bbMouse_EnterWidget(void* mouse, void* widgets, void* widget, void*
graphics);

bbFlag bbMouse_LeaveWidget(void* mouse, void* widgets, void* widget, void*
graphics);

bbFlag bbMouse_LeftDownWidget(void* mouse, void* widgets, void* widget,
                                void* graphics);
bbFlag bbMouse_LeftUpWidget(void* mouse, void* widgets, void* widget,
                                  void* graphics);


bbFlag bbMouse_LeftDragWidget(void* mouse, void* widgets, void* widget,
                            void* graphics);

//Function to be called recursively
bbFlag bbMouse_isOverFunc(bbTree* tree, void* node, void* cl);
#endif // BBMOOSE_H


/*
 * bbFlag bbInput_poll(bbInput* input, sfRenderWindow* window, bbMouse* mouse, bbMouse* mouse);
 *     updates bbMouse bbFlag bbMouse_Event(bbMouse* mouse, sfEvent* event)
 *
 * bbFlag bbMouse_Update(bbMouse* mouse, struct bbWidgets* widgets, bbGraphicsApp* graphics);
 *     calls bbFlag bbMouse_isOver(bbMouse* mouse, struct bbWidgets* widgets);
 *
 * bbFlag bbMouse_isOver(bbMouse* mouse, struct bbWidgets* widgets);
 *     calls bbTree_ascendingMapVisible with bbMouse_isOverFunc and cl
 *
 * bbFlag bbMouse_isOverFunc(bbTree* tree, void* node, void* cl)
 *     looks up function given by node.functions.isOver
 *
 * cl contains pointers to whatever systems are needed
 *
 * function given by node.functions.isOver
 *     is type bbFlag bbMouse_IsOver(bbMouse* mouse, bbWidgets* widgets, bbWidget* widget);
 *     updates bbMouse.isOver and bbMouse.wasOver and returns Break
 *     OR returns Continue
 *
 * bbMouse_Update
 *     calls appropriate functions from bbWidget.mtable
 *     clears bbMouse.leftChanged and bbMouse.rightChanged
 *
 * bbMouse_Draw
 *     looks up isOver.MouseIcon and selected.DragIcon and draws them to the screen
 */