#include "headers/bbSystemIncludes.h"
#include "headers/bbTextures.h"
#include "headers/bbSprites.h"
#include "headers/bbDictionary.h"
#include "headers/bbGame.h"
#include "headers/bbAnimation.h"
#include "headers/bbIntTypes.h"




I32 _bbAnimations_new(bbAnimations** self, I32 numAnimations){
	bbAnimations* animations = calloc(1, sizeof(bbAnimations));
	bbAssert(animations != NULL, "calloc failed\n");
	animations->m_NumAnimations = numAnimations;
	I32 flag = bbDictionary_new(&animations->m_Dictionary, numAnimations);
    animations->m_Animations = calloc(numAnimations, sizeof(bbAnimation*));
	bbAssert(flag == f_Success, "bbDictionary_new failed\n");
	*self = animations;
	return f_Success;

}
I32 animation_load(bbAnimations* animations, bbSprites* sprites, char* key, I32 address, I32 DrawFunction, I32 angles, I32 frames, I32 framerate, int* spriteInts){
	bbAnimation* anim = calloc(1, sizeof(bbAnimation) + angles * frames * sizeof(I32));
	bbAssert(anim != NULL, "calloc failed");
	strcpy(anim->m_Key, key);
	anim->v_DrawFunction = DrawFunction;
	anim->m_Angles = angles;
	anim->m_Frames = frames;
	anim->m_Sprites = sprites;
	anim->m_Framerate = framerate;

	for (I32 i = 0; i < angles*frames; i++){
		anim->i_Sprites[i] = spriteInts[i];
	}

	animations->m_Animations[address] = anim;
	bbDictionary_add(animations->m_Dictionary, key, address);



	return f_Success;
}


I32 bbAnimations_new(bbAnimations** self, bbSprites* Sprites, char* folderPath,
						 I32 numAnimations){
	bbAnimations* animations;
	_bbAnimations_new(&animations, numAnimations);

	char string[256];
	sprintf(string, "%s/animations.csv", folderPath);

	FILE* file = fopen(string,"r");

	bbAssert(file != NULL, "fopen failed\n");
	fscanf(file, "%[^\]]%*[^\n]\n", string);
	bbAssert(strcmp(string,
					"Label:,V_Address:,V_DrawFunction:,Angles:,Frames:,Framerate:,Sprites[") == 0,
			 "bad sprites.csv file\n");

	fscanf(file, "%[^\n]\n", string);

	char key[KEY_LENGTH];
	I32 address, drawFunction, angles, frames, framerate, sprites[256];
	I32 flag = 1;
	while (fscanf(file, "%[^,],%d,%d,%d,%d,%d", key, &address, &drawFunction, &angles, &frames, &framerate) == 6){

		for (I32 i = 0; i < angles * frames; i++){
			fscanf(file, ",%[^,]", string);
			//bbPrintf(",%s", string);
			I32 spriteInt = bbDictionary_lookup(Sprites->m_Dictionary, string);

			sprites[i] = spriteInt;

		}
		fscanf(file, "%*[^\n]\n");
		animation_load(animations, Sprites, key, address,drawFunction,angles, frames, framerate, sprites);
	}
	*self = animations;

	return f_Success;

}

