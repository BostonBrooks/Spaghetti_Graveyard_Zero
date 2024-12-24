/**
 * @file
 * @brief a bbDrawable is the basic object that can be drawn to the viewport
 **/

#ifndef BBDRAWABLE_H
#define BBDRAWABLE_H

#include "engine/logic/bbIntTypes.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/graphics/bbViewport.h"
#include "engine/graphics/bbComposition.h"




typedef struct {
	bbPool_ListElement square;
	bbMapCoords location;
	float rotation;
	// a bbDrawable can be either on its own, or the first element of a bbInteractable
	U8 is_interactable;
	// some composition draw functions can select a frame based on state
	U8 state;
	bbComposition composition;

} bbDrawable;

I32 bbDrawable_drawFrame(bbViewport* viewport, bbDrawable* drawable, bbFrame* frame);

#endif //BBDRAWABLE_H