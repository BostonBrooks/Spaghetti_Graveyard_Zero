/**
 * @file
 * @brief sfTexture is define in SFML as raw pixel data
 * bbTextures is a container for sfTextures
*/

#ifndef BBTEXTURES_H
#define BBTEXTURES_H

#include "bbSystemIncludes.h"
#include "bbDictionary.h"
#include "bbIntTypes.h"

typedef struct { //bbTextures
	I32 m_NumTextures;
	sfTexture** m_Textures;
	bbDictionary* m_Dictionary;

} bbTextures;

I32 bbTextures_new(bbTextures** self, char* folderPath, I32 numTextures);

//if key is int, return texture at that address
//otherwise, look up key in dictionary and return the texture pointed to.
I32 bbTextures_lookup (sfTexture** self, bbTextures* textures, char* key);

#endif //BBTEXTURES_H
