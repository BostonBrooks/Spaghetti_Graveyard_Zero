#include <stdio.h>
#include <string.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/graphics/bbTextures.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbPrime.h"
#include "engine/includes/csfml.h"
#include "games/game0/bbConstants.h"
#include "engine/logic/bbPrime.h"


I32 bbTextures_new(bbTextures** self, char* filepath){

	FILE* file = fopen(filepath, "r");

	bbAssert(file != NULL, "bad fopen\n");
	I32 num;
	fscanf(file, "Number of Textures,%d%*[^\n]\n", &num);

	bbTextures* textures = malloc(sizeof( bbTextures) + num * sizeof (sfTexture*));
	textures->numTextures = num;

	bbDictionary_new(&textures->dictionary, nextPrime(num));

	{
		char string[64];
		fscanf(file, "%[^\n]\n", string);
		bbAssert(strcmp(string, "Label:,Integer Address:,File:,Smooth:,Comment:") == 0,
				 "bad file\n");

	}

	char key[KEY_LENGTH];
	int address;
    bbPool_Handle handle;
    //path to file relative to games/game0/
	char file_path[256];
	char smooth;
    struct sfTexture* texture;


	while (fscanf(file, "%[^,],%d,%[^,],%c,%*[^\n]\n", key, &address, file_path, &smooth) == 4){
        //What do I pass as area?
        sfTexture_createFromFile(file_path, NULL);
        sfTexture_setSmooth(texture, smooth == 'T' ? sfTrue : sfFalse);
        handle.u64 = address;
        bbDictionary_add(textures->Dictionary, key, handle);
        textures->textures[address] = texture;

	}

    *self = textures;
    return Success;
}