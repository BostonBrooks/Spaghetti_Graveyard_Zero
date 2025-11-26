/** a drawable is (a base class for) any object drawn to the viewport */

#ifndef BBDRAWABLES_H
#define BBDRAWABLES_H

#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbFlag.h"
#include "engine/graphics/bbComposition.h"
#include "engine/logic/bbList.h"
#include "engine/graphics/bbGraphics.h"

#define FRAMES_PER_DRAWABLE

typedef struct
{
    bbMapCoords coords;
    bbPool_ListElement listElement;
    bbFrame frames[FRAMES_PER_DRAWABLE];
} bbDrawable;

typedef struct
{
    bbSquareCoords coords;
    bbList list;
} bbDrawableSquare;

typedef struct
{

    bbVPool* pool;
    //Drawables outside the usual map grid
    bbList lost;

    I32 squares_i;
    I32 squares_j;
    bbDrawableSquare squares[];
} bbDrawables;

bbFlag bbDrawables_new(void** self, bbGraphics* graphics, I32 squares_i, I32
squares_j);
I32 bbDrawable_isCloser(void* one, void* two);

/** bbDrawables_draw maps bbDrawables_drawFunc tp each bbDrawable */
bbFlag bbDrawables_draw(bbDrawables* overlays, drawFuncClosure* cl);
/** bbDrawables_drawFunc calls bbDrawable_draw */
bbFlag bbDrawables_drawFunc(void* node, void* cl);
/** bbbDrawable_draw draws a drawable to the screen*/
bbFlag bbDrawable_draw(bbDrawable* drawable, drawFuncClosure* cl);
#endif //BBDRAWABLES_H

