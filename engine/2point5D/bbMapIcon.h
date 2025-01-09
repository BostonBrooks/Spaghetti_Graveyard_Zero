#ifndef MINIMAP_H
#define MINIMAP_H

#include "engine/includes/CSFML.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbList.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbFlag.h"
#include "engine/graphics/bbComposition.h"

#define KEY_LENGTH 32

typedef struct {
    bbMapCoords coords;
    bbPool_ListElement listElement;
    char label[KEY_LENGTH];
    sfText* txt;
    I32 sprite;

} bbMapIcon;

typedef struct {
    bbSquareCoords coords;
    bbVPool* pool;
    bbList list;
} bbMapIconSquare;

typedef struct {
    I32 squares_i;
    I32 squares_j;
	sfFont* font;
    bbMapIconSquare squares[];
} bbMapIcons;


bbFlag bbMapIcons_new(void** self, I32 squares_i, I32 squares_j);
I32 bbMapIcon_compare(void* one, void* two);

#endif //MINIMAP_H

