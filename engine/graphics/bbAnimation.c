#include <stdio.h>
#include <string.h>
#include "engine/includes/CSFML.h"
#include "engine/logic/bbString.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbPrime.h"
#include "engine/graphics/bbTextures.h"
#include "engine/graphics/bbSprites.h"
#include "engine/graphics/bbAnimation.h"
#include "engine/graphics/bbDrawfunctions.h"


I32 bbAnimations_new(bbAnimations** self, bbSprites* Sprites, bbDrawfunctions* drawfunctions,  char* filePath) {
	FILE *file = fopen(filePath, "r");
	bbAssert(file != NULL, "bad fopen\n");

	I32 num;
	fscanf(file, "Number of Animations:,%d%*[^\n]\n", &num);

	bbAnimations *animations = malloc(
			sizeof(bbAnimations) + num * sizeof(bbPool_Handle));
	animations->numAnimations = num;
    bbDictionary_new(&animations->dictionary, nextPrime(num));
    //bbDictionary_new(&animations->dictionary, 1);

	fscanf(file, "%*[^\n]\n");

	char key[KEY_LENGTH];
	I32 address;
	bbPool_Handle handle;
	I32 radius;
	I32 height;
	char drawfunctionStr[KEY_LENGTH];
	bbPool_Handle drawfunctionHandle;
	I32 angles;
	I32 frames;
	float framerate;
	I32 spriteInt;
	bbPool_Handle spriteHandle;

	while (fscanf(file, "%[^,],%d,%d,%d,%[^,],%d,%d,%f",
				 key,&address,&radius,&height,drawfunctionStr,&angles,&frames,&framerate) == 8){

		bbAnimation* animation = malloc(sizeof(*animation) + angles*frames*sizeof(bbPool_Handle));
		bbAssert(animation!=NULL, "bad malloc\n");
		bbStr_setStr(animation->key, key, KEY_LENGTH);
		animation->radius = radius;
		animation->height = height;

		bbDictionary_lookup(drawfunctions->dictionary, drawfunctionStr, &drawfunctionHandle);

		animation->drawFunction = drawfunctionHandle.u64;
		animation->angles = angles;
		animation->sprites = Sprites;
		animation->frames = frames;
		animation->framerate = framerate;

		//bbDebug("label = %s, angles = %d, frames = %d, framerate = %f\n",
		//		animation->key, animation->angles, animation->frames, animation->framerate);
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

    // bbDictionary_print(animations->dictionary);
	return Success;
}