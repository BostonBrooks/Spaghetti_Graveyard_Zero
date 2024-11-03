#include <stdio.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/graphics/bbTextures.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbPrime.h"
#include "engine/includes/csfml.h"
#include "games/game0/bbConstants.h"

I32 next_prime(I32 n);

I32 bbTextures_new(bbTextures** self, char* filepath){

	FILE* file = fopen(filepath);
	bbAssert(file != NULL, "bad fopen\n");
	I32 numTextures;
	fscanf(file, "Number of Sprites,%d%*[^\n]\n", &numTextures);

	bbTextures* textures = malloc(sizeof( bbTextures) + numTextures * sizeof (sfTexture*));
	textures->numTextures = numTextures;

	bbDictionary_new(&textures->Dictionary, next_prime(numTextures));

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