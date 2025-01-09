#ifndef MINIMAP_H
#define MINIMAP_H

#include "engine/includes/CSFML.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbList.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbFlag.h"
#include "engine/graphics/bbComposition.h"
#include "engine/2point5D/bbViewport.h"
#include "engine/graphics/bbGraphics.h"

#define KEY_LENGTH 32

typedef struct {
    bbMapCoords coords;
    bbPool_ListElement listElement;
    char label[KEY_LENGTH];
    sfText* txt;
    I32 sprite;

} bbOverlayIcon;

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
} bbOverlay;


bbFlag bbOverlay_new(void** self, I32 squares_i, I32 squares_j);
I32 bbOverlayIcon_isCloser(void* one, void* two);

bbFlag bbOverlay_draw(bbOverlay* overlay, bbViewport* viewport,  bbGraphics* graphics);
#endif //MINIMAP_H

