/**
 * @file
 * @brief sfTexture is define in SFML as raw pixel data
 * bbTextures is a container for sfTextures
 * sprites are used to draw images to render targets such as:
 * the screen, where sprites are scaled by widgetscale
 * the viewport, where sprites are scaled by drawavlescale
 * the ground, where sprites are scaled by groundscale
 * NONE, sprites that are not scaled
 *
 * data is contained in games/game0/maps/map0/graphics/textures.csv
 *
 * Lable: used to look up sprite in dictionary
 * Virtual Address: location of sprite in array
 * sfTexture: where to find pixel data for the sprite
 * Left, Top, Width, Height: bounding box for sprite
 * Origin_x, Origin_y: sprites are drawn relative to this position
 * Scale_x, Scale_y: default scaling;
 * Scale_By: Scale modifier
 * Comment: text to be ignored
*/

#ifndef BBSPRITES_H
#define BBSPRITES_H

#include "engine/includes/CSFML.h"
#include "engine/logic/bbDictionary.h"
#include "engine/graphics/bbTextures.h"
#include "engine/logic/bbIntTypes.h"

typedef struct { //bbSprites
	I32 numSprites;
	bbDictionary* dictionary;
	sfSprite* sprites[];

} bbSprites;

bbFlag bbSprites_new(bbSprites** self, bbTextures* textures, char* filePath,
				  float widgetscale, float drawablescale, float groundscale);

///when closing one map before opening another
bbFlag bbSprites_delete(bbSprites* sprites);

bbFlag bbSprites_lookup (sfSprite** self, bbSprites* sprites, char* key);


bbFlag bbSprites_lookupInt(bbSprites* sprites, I32* address, char* key);

#endif //BBSPRITES_H
