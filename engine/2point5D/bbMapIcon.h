#ifndef MINIMAP_H
#define MINIMAP_H

#include "engine/includes/CSFML.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbList.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbFlag.h"

#define KEY_LENGTH 32

typedef struct {
    char label[KEY_LENGTH];
    bbMapCoords coords;
    sfText* txt;
    I32 sprite;
    bbPool_ListElement listElement;

} bbMapIcon;

typedef struct {
    I32 squares_i;
    I32 squares_j;
    bbVPool* pool;
    bbList list[];
} bbMapIcons;


bbFlag bbMapIcons_new(void** self, I32 squares_i, I32 squares_j);

#endif //MINIMAP_H

