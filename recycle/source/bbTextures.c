#include "headers/bbSystemIncludes.h"
#include "headers/bbTextures.h"
#include "headers/bbDictionary.h"
#include "headers/bbIntTypes.h"

I32 _bbTextures_new(bbTextures** self, I32 numTextures){
	bbTextures* textures = calloc(1, sizeof(bbTextures));
	bbAssert(textures != NULL, "calloc failed\n");
	textures->m_NumTextures = numTextures;
	textures->m_Textures = calloc(numTextures, sizeof(sfTexture*));
	I32 flag = bbDictionary_new(&textures->m_Dictionary, numTextures);
	bbAssert(flag == f_Success, "bbDictionary_new failed\n");
	*self = textures;
	return f_Success;

}

I32 texture_load(bbTextures* textures, char* key, I32 address, char* filename,sfBool smooth){

	sfTexture* texture = sfTexture_createFromFile(filename, NULL);
	bbAssert(texture != NULL, "sfTexture failed to load, %s\n", filename);
	sfTexture_setSmooth(texture, smooth);
	textures->m_Textures[address] = texture;
	bbDictionary_add(textures->m_Dictionary, key, address);
	return f_Success;
}

I32 bbTextures_new(bbTextures** self, char* folderPath, I32 numTextures){

	bbTextures* textures;
	_bbTextures_new(&textures, numTextures);

	char string[256];

	sprintf(string, "%s/textures.csv", folderPath);

	FILE* file = fopen(string, "r");
	bbAssert(file != NULL, "fopen failed\n");

	fscanf(file, "%[^\n]\n", string);
	bbAssert(strcmp(string,
			"Label:,Virtual Address:,File:,Smooth:,Comment:") == 0,
			"bad textures.csv file\n");

	char key[KEY_LENGTH];
	int address;
	char fileName[256];
	char filePath[256];
	char smooth;
	int flag;

	while (fscanf(file, "%[^,],%d,%[^,],%c%*[^\n]\n", key, &address, fileName, &smooth) == 4){
		sprintf(filePath, "%s/%s", folderPath, fileName);
		//printf("%s\n", filePath);
		texture_load(textures, key, address, filePath, smooth == 'T' ? sfTrue : sfFalse);
	}

	fclose(file);

	*self = textures;
	return f_Success;
}

//if key is int, return texture at that address
//otherwise, look up key in dictionary and return the texture pointed to.
I32 bbTextures_lookup (sfTexture** self, bbTextures* textures, char* key){

	bbDictionary* dict = textures->m_Dictionary;

	I32 len = strlen(key);
	char digits[] = "0123456789";
	int int_len = strspn(key, digits);
	int address;
	if (len == int_len){
		address = atoi(key);
	} else {
		address = bbDictionary_lookup(dict, key);
		bbAssert(address >= 0, "bad data from dictionary\n");
	}

	sfTexture* texture = textures->m_Textures[address];

	*self = texture;

	return f_Success;
}
