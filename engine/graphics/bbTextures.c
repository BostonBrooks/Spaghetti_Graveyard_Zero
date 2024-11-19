#include <stdio.h>
#include <string.h>
#include "engine/logic/bbIntTypes.h"
#include "engine/graphics/bbTextures.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbPrime.h"
#include "engine/includes/csfml.h"
#include "games/game0/bbConstants.h"
#include "engine/logic/bbPrime.h"


bbFlag bbTextures_new(bbTextures** self, char* filepath){

	FILE* file = fopen(filepath, "r");

	bbAssert(file != NULL, "bad fopen\n");
	I32 num;
	fscanf(file, "Number of Textures:,%d%*[^\n]\n", &num);

	bbTextures* textures = malloc(sizeof( bbTextures) + num * sizeof (sfTexture*));
	textures->numTextures = num;

	bbDictionary_new(&textures->dictionary, nextPrime(num));


		fscanf(file, "%*[^\n]\n");


	char key[KEY_LENGTH];
	int address;
    bbPool_Handle handle;
    //path to file relative to games/game0/
	char file_path[256];
	char smooth;
    struct sfTexture* texture;


	while (fscanf(file, "%[^,],%d,%[^,],%c,%*[^\n]\n", key, &address, file_path, &smooth) == 4){
        //What do I pass as area?
        texture = sfTexture_createFromFile(file_path, NULL);
        sfTexture_setSmooth(texture, smooth == 'T' ? sfTrue : sfFalse);
		//bbDebug("address = %d\n", address);
        handle.u64 = address;
        bbDictionary_add(textures->dictionary, key, handle);
        textures->textures[address] = texture;

	}

	fclose(file);
    *self = textures;
    return Success;
}

bbFlag bbTextures_lookup (sfTexture** self, bbTextures* textures, char* key){

	I32 len = strlen(key);
	char digits[] = "0123456789";
	I32 int_len = strspn(key, digits);
	I32 address;
	//bbDebug("key = %s\n", key);
	if(len == int_len){
		address = atoi(key);

	} else {
		bbPool_Handle handle;
		bbDictionary_lookup(textures->dictionary, key, &handle);
		address = handle.u64;
	}
	bbAssert(address < textures->numTextures,
			 "key = %s, address = %d, numTextures = %d\n",key, address,
             textures->numTextures);

	*self = textures->textures[address];

	return Success;
}