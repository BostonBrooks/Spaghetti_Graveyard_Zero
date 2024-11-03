#include <stdio.h>
#include <string.h>
#include "engine/includes/csfml.h"
#include "engine/logic/bbString.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbPrime.h"
#include "engine/graphics/bbTextures.h"
#include "engine/graphics/bbSprites.h"
#include "engine/graphics/bbAnimation.h"


I32 bbAnimations_new(bbAnimations** self, bbSprites* Sprites, char* filePath) {
	FILE* file = fopen(filePath, "r");
	bbAssert(file != NULL, "bad fopen\n");

	I32 num;
	fscanf(file, "Number of Animations:,%d%*[^\n]\n", &num);

	bbAnimations* animations = malloc(sizeof(bbAnimations) + num * sizeof(bbPool_Handle));
	animations->numAnimations = num;
	bbDictionary_new(&animations->dictionary, nextPrime(num));

	char string[64];
	fscanf(file, "%[^\n]\n", string);
	bbAssert(strcmp(string, "Label:,Integer Address:,Texture:,Left:,Top:,Width:,Height:,Origin X:,Origin Y:,Scale X:,Scale Y:,Scale By:,Comment:") == 0,
			 "bad file\n");

	{
		char string[128];
		fscanf(file, "%[^\n]\n", string);
		bbAssert(strcmp(string, "Label:,Integer Address:,Radius:,Height:,Draw Function,Angles:,Frames:,Framerate:,Sprites:,…,Comment:") == 0,
				 "bad file\n");

	}

	char key[KEY_LENGTH];
	I32 address;
	bbPool_Handle handle;
	I32 radius;
	I32 height;
	I32 drawfunction;
	I32 angles;
	I32 frames;
	float framerate;
	I32 spriteInt;
	I32 spriteHandle;

	while (fscanf(file, "%[^,],%d,%d,%d,%d,%d,%d,%f",
				 key,&address,&radius,&height,&drawfunction,&angles,&frames,&framerate) == 8){

		bbAnimation* animation = malloc(sizeof(*animation) + angles*frames*sizeof(bbPool_Handle));
		bbAssert(animation!=NULL, "bad malloc\n");
		bbStr_setStr(animation->key, key, KEY_LENGTH);
		animation->radius = radius;
		animation->height = height;
		animation->drawFunction = drawfunction;
		animation->angles = angles;
		animation->sprites = Sprites;

		for(I32 i = 0; i < angles*frames; i++){

			fscanf(file, ",%[^,]", key);
			bbSprites_lookupInt(Sprites, &spriteInt, key );
			spriteHandle.u64 = spriteInt;
			animation->Sprites[i] = spriteHandle;
		}
		fscanf(file, "%*[^\n]\n");

		handle.u64 = address;

		animations->animations[address] = animation;
		bbDictionary_add(animations->dictionary, animation->key, handle);
	}

	*self = animations;
	return Success;
}