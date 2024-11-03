/**
 * @file
 * @brief sfTexture is define in SFML as raw pixel data
 * bbTextures is a container for sfTextures
*/

#ifndef BBANIMATION_H
#define BBANIMATION_H

#include "engine/includes/csfml.h"
#include "engine/logic/bbDictionary.h"
#include "engine/graphics/bbSprites.h"
#include "engine/logic/bbIntTypes.h"

typedef struct {
	char key[KEY_LENGTH];
	I32 radius;
	I32 height;
	I32 drawFunction; // default draw function for the given animation
	I32 angles;
	I32 frames;
	I32 framerate;
	bbSprites* sprites; //the container where sprites are found
	//list of length angles * sprites, integer addresses into a bbSprites container
	I32 Sprites[];

} bbAnimation;

typedef struct { //bbAnimations
	I32 m_NumAnimations;
	//pointer to array of pointers to variable sized animations
	bbAnimation** m_Animations;
	bbDictionary* m_Dictionary;

} bbAnimations;

I32 bbAnimations_new(bbAnimations** self, bbSprites* Sprites, char* folderPath,
		I32 numAnimations);

I32 bbAnimations_delete(bbAnimations* animations);

I32 bbAnimations_lookupInt(bbAnimations* animations, char* key);

#endif //BBANIMATION_H
