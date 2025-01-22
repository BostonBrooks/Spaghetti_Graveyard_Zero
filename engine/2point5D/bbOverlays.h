/**
 * An overlay is an icon to be drawn to the minimap
 **/


#ifndef BBOVERLAYS_H
#define BBOVERLAYS_H

#include "engine/includes/CSFML.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbList.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbFlag.h"
#include "engine/graphics/bbComposition.h"
#include "engine/2point5D/bbViewport.h"
#include "engine/graphics/bbGraphics.h"
#include "engine/graphics/bbDrawfunctions.h"


#define KEY_LENGTH 32
#define FRAMES_PER_OVERLAY 8

typedef struct {
    bbMapCoords coords;
    bbPool_ListElement listElement;
    char label[KEY_LENGTH];
    sfText* txt;
    I32 sprite;

    bbFrame frames[FRAMES_PER_OVERLAY];
} bbOverlay;

typedef struct {
    bbSquareCoords coords;
    bbVPool* pool;
    bbList list;
} bbOverlaySquare;

typedef struct {
    I32 squares_i;
    I32 squares_j;
	sfFont* font;
    bbOverlaySquare squares[];
} bbOverlays;


bbFlag bbOverlays_new(void** self, bbGraphics* graphics, I32 squares_i, I32
squares_j);
I32 bbOverlay_isCloser(void* one, void* two);

bbFlag bbOverlay_drawTest(bbOverlays* overlays, bbViewport* viewport,
                          bbGraphics* graphics);

/// maps drawfunc to list of lists
bbFlag bbOverlays_draw(bbOverlays* overlays, drawFuncClosure* cl);
/// calls bbOverlay_draw()

///typedef bbFlag bListList_mapFunction(void* node, void* cl);
bbFlag bbOverlay_drawFunc(void* node, void* cl);
/// draws individual overlay
bbFlag bbOverlay_draw(bbOverlay* overlay, drawFuncClosure* cl);



#endif //BBOVERLAYS_H

