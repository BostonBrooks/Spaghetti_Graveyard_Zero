/**
 * @file
 * @brief a composition is a collection of frames to be drawn to the screen
 * a frame contains data needed to draw a sprite, animation, or another frame
 *
 * compositions.csv has the following fields:
 * Label: used to lookup composition in dictionary
 * Virtual Address: where to store composition
 * up to FRAMES_PER_COMPOSITION of: {
 *     type: SPRITE/ANIMATION/COMPOSITION //which dictionary to look up identifier
 *     identifier: used to look up SPRITE/ANIMATION/COMPOSITION
 *     framerate:
 *     drawfunction:
 **/
#ifndef BBCOMPOSITION_H
#define BBCOMPOSITION_H


#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbDictionary.h"
#include "engine/graphics/bbSprites.h"
#include "engine/graphics/bbAnimation.h"
#define FRAMES_PER_COMPOSITION 8

// a bbFrame contains the data used to draw a sprite, animation or composition
typedef struct {
	I32 drawfunction;
	I32 identifier;
	U32 starttime;
	//multiply by the framerate of the animation
	float framerate;
} bbFrame;

typedef struct {
	bbFrame frame[FRAMES_PER_COMPOSITION];
} bbComposition;

typedef struct {
	I32 num_composition;
	//pointer to array of equal sized compositions
	bbComposition* compositions;
	bbDictionary* dictionary;
} bbCompositions;

I32 bbComposition_new(bbComposition** self, bbSprites* sprites, bbAnimations* animations, char* folderPath,
					 I32 numAnimations);

I32 bbCompositions_delete(bbCompositions* compositions);

I32 bbCompositions_lookupInt(bbCompositions* compositions, char* key);

#endif //BBCOMPOSITION_H