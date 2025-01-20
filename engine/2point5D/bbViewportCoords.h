/**
 * @file
 * @brief converts from map coordinates to sfVector2f coordinates
 **/

#ifndef BBVIEWPORTCOORDS_H
#define BBVIEWPORTCOORDS_H

#include "engine/2point5D/bbViewport.h"
#include "engine/includes/game0.h"

sfVector2f bbMapCoords_getV2f(bbMapCoords MC, bbViewport* VP);
sfVector2f bbMapCoords_getV2f_overlay(bbMapCoords MC, bbViewport* VP);


#endif //BBVIEWPORTCOORDS_H