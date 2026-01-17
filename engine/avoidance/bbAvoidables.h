/** Units cannot pass through avoidables */

#ifndef BBAVOIDABLES_H
#define BBAVOIDABLES_H

#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbList.h"
#include "engine/logic/bbNestedList.h"
#include "engine/viewport/bbDrawables.h"

typedef struct
{
    bbMapCoords coords;
    bbPool_ListElement listElement;
    I32 radius;
} bbAvoidable;

#define bbAvoidableSquare bbDrawableSquare

#define bbAvoidables bbDrawables

bbFlag bbAvoidables_new(void** self, I32 squares_i, I32 squares_j);

#define bbAvoidable_isCloser bbDrawable_isCloser
#define bbAvoidable_getSquareIndex bbDrawables_getSquareIndex

bbFlag bbAvoidable_new(bbAvoidable** self, bbAvoidables* avoidables,
                       bbMapCoords MC, I32 radius);

bbFlag bbAvoidables_draw(bbDrawables* drawables, drawFuncClosure* cl,
                        I32 square_i_min, I32 square_j_min,
                        I32 square_i_max, I32 square_j_max);

bbFlag bbAvoidable_drawFunc(void* node, void* cl);



#endif //BBAVOIDABLES_H