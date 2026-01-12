
#include "engine/graphics/bbFonts.h"
#include "engine/graphics/bbTextures.h"
#include "engine/graphics/bbSprites.h"
#include "engine/graphics/bbAnimation.h"
#include "engine/graphics/bbComposition.h"
#include "engine/graphics/bbDrawfunctions.h"

#ifndef BBGRAPHICS_H
#define BBGRAPHICS_H

//All of the elements in bbGraphicsApp have variable size, so must be dynaically allocated
typedef struct bbGraphicsApp {
	bbTextures* textures;
	bbSprites* sprites;
	bbDrawfunctions* drawfunctions;
	bbAnimations* animations;
	bbCompositions* compositions;
	bbFonts* fonts;
} bbGraphicsApp;

bbFlag bbGraphicsApp_init(bbGraphicsApp* app);
#endif // BBGRAPHICS_H