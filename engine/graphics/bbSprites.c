#include <stdio.h>
#include <string.h>
#include "engine/graphics/bbSprites.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/includes/csfml.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbPrime.h"
#include "engine/logic/bbString.h"


typedef struct {
	I32 left;
	I32 top;
	I32 width;
	I32 height;
	float originx;
	float originy;
	float scalex;
	float scaley;
} sprite_dimensions;


I32 bbSprites_new(bbSprites** self, bbTextures* textures, char* filePath,
				  float widgetscale, float drawablescale, float groundscale)
{
	FILE* file = fopen(filePath, "r");
	bbAssert(file!= NULL, "bad fopen\n");

	I32 num;
	fscanf(file, "Number of Sprites,%d%*[^\n]\n", &num);

	bbSprites* sprites = malloc(sizeof(sprites) + num * sizeof (sfSprite*));

	sprites->numSprites = num;
	bbDictionary_new(&sprites->dictionary, nextPrime(num));

	{
		char string[64];
		fscanf(file, "%[^\n]\n", string);
		bbAssert(strcmp(string, "Label:,Integer Address:,Texture:,Left:,Top:,Width:,Height:,Origin X:,Origin Y:,Scale X:,Scale Y:,Scale By:,Comment:") == 0,
				 "bad file\n");

	}

	char key[KEY_LENGTH];
	I32 address;
	char texture[KEY_LENGTH];
	sprite_dimensions dimensions;
	char scale_by[KEY_LENGTH];

	while(fscanf(file, "%[^,],%d,%[^,],%d,%d,%d,%d,%f,%f,%f,%f,%[^,],%*[^\n]\n",
				 key, &address, texture, &dimensions.left, &dimensions.top, &dimensions.width,
				 &dimensions.height, &dimensions.originx, &dimensions.originy, &dimensions.scalex,
				 &dimensions.scaley, scale_by) == 12)
	{

	}
}

