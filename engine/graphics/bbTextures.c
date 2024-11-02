#include <stdio.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/graphics/bbTextures.h"
#include "engine/logic/bbTerminal.h"
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
	char file_path[256]; //path to file relative to games/game0/
	char smooth;

	while (fscanf(file, "%[^,],%d,%[^,],%c,%*[^\n]\n", key, &address, file_path, &smooth) == 4){

	}
}