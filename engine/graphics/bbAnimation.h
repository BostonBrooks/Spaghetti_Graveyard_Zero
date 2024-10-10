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
	char m_Key[KEY_LENGTH];

	I32 v_DrawFunction; // default draw function for the given animation
	I32 m_Angles;
	I32 m_Frames;
	I32 m_Framerate;
	bbSprites* m_Sprites;
	//list of length m_Angles * m_Sprites
	I32 i_Sprites[];

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
