#ifndef BBCOORDINATES_H
#define BBCOORDINATES_H

#include "engine/includes/game0.h"
#include "engine/includes/CSFML.h"
#include "engine/logic/bbArith.h"
#include <math.h>

typedef struct {
    I32 i;           //i axis points down and to the right, in units of points
    I32 j;           //j axis points up and to the right, in units of points
    I32 k; //k axis points up, in units of points, negative indicates invalid
} bbMapCoords;

typedef struct {
    I32 i;           //i axis points down and to the right, in units of tiles
    I32 j;           //j axis points up and to the right, in units of tiles
    I32 k; //k axis points up, in units of points, negative indicates invalid
} bbTileCoords;

typedef struct {
    I32 i;           //i axis points down and to the right, in units of squares
    I32 j;           //j axis points up and to the right, in units of squares
    I32 k;   //k axis points up, in units of points, negative indicateS invalid
} bbSquareCoords;

/// avoid floating point math in systems that need to be deterministic
typedef struct {
    float i;           //i axis points down and to the right, in whatever units
    float j;           //j axis points up and to the right, in whatever units
    float k;           //k axis points up, whatever units
} bbFloat3D;

/// viewport coordinates may be scaled up and down, but screen points stay at
/// the same scale
typedef struct {
    I32 x; // x axis points to the right
    I32 y; // y axis points down
} bbScreenPoints;

typedef struct {

    I32 top;
    I32 left;
    I32 height;
    I32 width;

} bbIntRect;

typedef struct {

	I32 top;
	I32 left;
	I32 height;
	I32 width;

} bbScreenPointsRect;

bbTileCoords bbMapCoords_getTileCoords(bbMapCoords MC);

bbSquareCoords bbMapCoords_getSquareCoords(bbMapCoords MC);

bbSquareCoords bbTileCoords_getSquareCoords(bbTileCoords TC);

/// get a vector from A to B, as seen on the 2d isometric projection
bbScreenPoints bbMapCoords_getScreenPoints_relative (bbMapCoords A,
                                                     bbMapCoords B);

bbFloat3D bbFloat3D_normalise (bbFloat3D foo);

sfVector2f bbScreenPoints_getV2f(bbScreenPoints SP);
bbScreenPoints pixel_getScreenPoints(I32 x, I32 y);

I32 bbScreenPoints_inScreenPointsRect(bbScreenPoints SP, bbScreenPointsRect rect);

#endif // BBCOORDINATES_H