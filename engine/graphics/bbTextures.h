/**
 * @file
 * @brief this file loads textures for use in the game
 * data is contained in games/game0/maps/map0/textures.csv
 *
 * textures.csv has the following fields
 *
 * Label: to be used in a dictionary to look up texture by name
 * Virtual Address: an index in an array of textures
 * File: used to locate the file in games/game0/graphics
 * Smooth: use gpu interpolation between pixel values
 * Comment: ignored by the program
 **/

#ifndef BBTEXTURES_H
#define BBTEXTURES_H

#include "engine/includes/csfml.h"
#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbIntTypes.h"

typedef struct { //bbTextures
	I32 m_NumTextures;
	sfTexture** m_Textures;
	bbDictionary* m_Dictionary;

} bbTextures;

I32 bbTextures_new(bbTextures** self, char* filepath, I32 numTextures);
I32 bbTextures_delete(bbTextures* textures);

//if key is int, return texture at that address
//otherwise, look up key in dictionary and return the texture pointed to.
I32 bbTextures_lookup (sfTexture** self, bbTextures* textures, char* key);

#endif //BBTEXTURES_H
