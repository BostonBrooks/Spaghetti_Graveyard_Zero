#include "engine/viewport/bbUnits.h"

bbFlag bbUnit_new(bbUnit** self,bbUnits* units, bbGraphics* graphics,
                  bbMapCoords MC){

    bbVPool* pool = units->pool;
    bbSquareCoords SC = bbMapCoords_getSquareCoords(MC);
    I32 index = bbDrawables_getSquareIndex(SC.i, SC.j, units->squares_i);
    bbUnitSquare unitSquare = units->squares[index];

    bbUnit* unit;
    bbFlag flag = bbVPool_alloc(pool, (void**)&unit);

    unit->radius = 160;
    unit->drawable.coords = MC;

    bbPool_Handle drawfunctionHandle;



    bbDictionary_lookup(graphics->drawfunctions->dictionary,
                        "DRAWABLESPRITE",
                        &drawfunctionHandle);

    unit->drawable.frames[0].drawfunction = drawfunctionHandle.u64;
    unit->drawable.frames[0].handle.u64 = 143;

    for (I32 k = 1; k < FRAMES_PER_DRAWABLE; k++){
        unit->drawable.frames[k].drawfunction = -1;
    }

    bbList_sortL(&unitSquare.list, unit);
    *self = unit;
    return Success;
}

bbFlag bbUnit_newCat(bbUnit** self,bbUnits* units, bbGraphics* graphics,
                  bbMapCoords MC){

    bbVPool* pool = units->pool;
    bbSquareCoords SC = bbMapCoords_getSquareCoords(MC);
    I32 index = bbDrawables_getSquareIndex(SC.i, SC.j, units->squares_i);
    bbUnitSquare unitSquare = units->squares[index];

    bbUnit* unit;
    bbFlag flag = bbVPool_alloc(pool, (void**)&unit);
    bbFlag_print(flag);
    unit->radius = 160;
    unit->drawable.coords = MC;

    bbPool_Handle drawfunctionHandle;



    bbDictionary_lookup(graphics->drawfunctions->dictionary,
                        "DRAWABLEANIMATION",
                        &drawfunctionHandle);

    unit->drawable.frames[0].drawfunction = drawfunctionHandle.u64;
    unit->drawable.frames[0].handle.u64 = 7;
    unit->drawable.frames[0].startTime =  -(rand()%6);
    unit->drawable.frames[0].framerate = 1;

    for (I32 k = 1; k < FRAMES_PER_DRAWABLE; k++){
        unit->drawable.frames[k].drawfunction = -1;
    }

    bbList_sortL(&unitSquare.list, unit);
    *self = unit;
    return Success;
}