
#include <stdio.h>
#include <string.h>
#include "engine/graphics/bbComposition.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbPrime.h"
#include "engine/logic/bbDictionary.h"
#include "engine/graphics/bbDrawfunctions.h"

I32 bbComposition_new(bbComposition** self, bbSprites* sprites, bbAnimations* animations, bbDrawfunctions* drawfunctions, char* filePath){

	FILE* file = fopen(filePath, "r");
	bbAssert(file!= NULL, "bad fopen\n");

	I32 num_compositions;
	fscanf(file, "Number of Compositions:,%d%*[^\n]\n\n", &num_compositions);

	bbCompositions* compositions = malloc(sizeof(bbCompositions) + num_compositions * sizeof(bbComposition*));
	compositions->num = num_compositions;
	bbDictionary_new(&compositions->dictionary, nextPrime(num_compositions));

	char label[KEY_LENGTH];
	I32 num_frames;
	I32 address;
	bbComposition* composition;
	bbPool_Handle handle1;

	while(1){

		fscanf(file, "Label:,%[^,],Integer Address:,%d,num:,%d,%*[^\n]\n", label,&address, &num_frames);
		composition = malloc(sizeof(bbComposition)+num_frames*sizeof(bbFrame));

		handle1.u64 = address;
		bbDictionary_add(compositions->dictionary, label, handle1);
		composition->num_frames = num_frames;
		{
			char string[64];
			fscanf(file, "%[^\n]\n]", string);
			bbAssert(strcmp(string, "Type:,Asset:,Drawfunction:,Start Time:,Frame Rate:,") == 0,
					 "bad file\n")
		}

		char type[KEY_LENGTH];
		char asset[KEY_LENGTH];
		char drawfunction[KEY_LENGTH];
		I32 starttime;
		float framerate;

		bbPool_Handle handle, handle2;

		for(I32 i = 0; i < num_frames; i++) {
			fscanf(file, "%[^,],%[^,],%[^,],%d,%f,%*[^\n]\n", type, asset,
				   drawfunction, &starttime, &framerate);

			if (strcmp(type, "SPRITE") == 0) {
				//look up asset in sprites TODO detect errors

				bbDictionary_lookup(sprites->dictionary, asset, &handle);
				composition->frame[i].handle = handle;


			} else if (strcmp(type, "ANIMATION") == 0) {
				//look up asset in animations
				bbDictionary_lookup(animations->dictionary, asset, &handle);
				composition->frame[i].handle = handle;
			} else if (strcmp(type, "COMPOSITION") == 0) {
				//look up asset in compositions
				//look up asset in animations
				bbDictionary_lookup(compositions->dictionary, asset, &handle);
				composition->frame[i].handle = handle;
			} else {
				bbAssert(0 == 1, "bad type in compositions.csv\n");
			}
			bbDictionary_lookup(drawfunctions->dictionary, drawfunction, &handle2);
			composition->frame[i].drawfunction = handle2.u64;
			composition->frame[i].startTime = starttime;
			composition->frame[i].framerate = framerate;

		}

		compositions->compositions[address] = composition;
		char commas[32];

		if (fscanf(file,",%[^\n]\n", commas)==EOF) return 1;
	}
}
