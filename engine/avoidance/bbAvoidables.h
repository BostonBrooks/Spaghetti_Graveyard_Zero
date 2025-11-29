#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbList.h"
#include "engine/logic/bbNestedList.h"

typedef struct
{
    bbSquareCoords coords;
    I32 radius;
} bbAvoidable;

typedef struct
{
    bbSquareCoords coords;
    bbList list;
} bbAvoidableSquare;

typedef struct
{

    bbVPool* pool;
    //Drawables outside the usual map grid
    bbList list;
    bbNestedList nestedList;

    //We cant extend bbDrawables because it ends in a flexible array member,
    //so we use a pointer to extra data
    void* extra_data;

    I32 squares_i;
    I32 squares_j;
    bbAvoidableSquare squares[];
} bbAvoidables;

bbFlag bbAvoidables_newImpl(void** self, I32 squares_i, I32
squares_j, I32 sizeOf);