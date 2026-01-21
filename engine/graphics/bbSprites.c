#include <stdio.h>
#include <string.h>
#include "engine/graphics/bbSprites.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/includes/CSFML.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbPrime.h"
#include "engine/logic/bbString.h"
#include "engine/data/bbHome.h"


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

bbFlag bbSprite_new(bbSprites* sprites, char* key, I32 address, sfTexture* texture, sprite_dimensions* dimensions){

	sfSprite* sprite = sfSprite_create();
    bbAssert(sprite != NULL, "sfSprite_create() returned NULL\n");

    //bbDebug("spriteInt = %d, sprite = %p\n", address, sprite);

	sfSprite_setTexture(sprite, texture, sfTrue);

	sfIntRect rect;
	rect.left = dimensions->left;
	rect.top = dimensions->top;
	rect.width = dimensions->width;
	rect.height = dimensions->height;
	sfSprite_setTextureRect(sprite, rect);

	sfVector2f origin;
	origin.x = dimensions->originx;
	origin.y = dimensions->originy;
	sfSprite_setOrigin(sprite, origin);

	sfVector2f scale;
	scale.x = dimensions->scalex;
	scale.y = dimensions->scaley;
	sfSprite_setScale(sprite, scale);

	sprites->sprites[address] = sprite;
	bbPool_Handle handle;
	handle.u64 = address;

	bbDictionary_add(sprites->dictionary, key, handle);
// Test code seems to work
/*    printf("address = %d\n", address);
    sfVector2f pos;
    pos.x = 150;
    pos.y = 100;
    sfRenderWindow_clear(home.private.window, sfBlue);
    sfSprite_setPosition(sprite, pos);
    sfRenderWindow_drawSprite(home.private.window, sprite,NULL);
    sfRenderWindow_display(home.private.window);
*/
	return Success;
}

bbFlag bbSprites_new(bbSprites** self, bbTextures* textures, char* filePath,
				  float widgetscale, float drawablescale, float groundscale)
{

	FILE* file = fopen(filePath, "r");
	bbAssert(file!= NULL, "bad fopen\n");

	I32 num;
	fscanf(file, "Number of Sprites:,%d%*[^\n]\n", &num);

	bbSprites* sprites = malloc(sizeof(bbSprites) + num * sizeof (sfSprite*));


	sprites->numSprites = num;
    bbDictionary_new(&sprites->dictionary, nextPrime(num));



	fscanf(file, "%*[^\n]\n");


	char key[KEY_LENGTH];
	I32 address;
	char texture[KEY_LENGTH];
	sfTexture* texturePtr;
	sprite_dimensions dimensions;
	char scale_by[KEY_LENGTH];

	while(fscanf(file, "%[^,],%d,%[^,],%d,%d,%d,%d,%f,%f,%f,%f,%[^,],%*[^\n]\n",
				 key, &address, texture, &dimensions.left, &dimensions.top, &dimensions.width,
				 &dimensions.height, &dimensions.originx, &dimensions.originy, &dimensions.scalex,
				 &dimensions.scaley, scale_by) == 12) {

		if(0 == strcmp(scale_by, "Widget")){
			dimensions.scalex *= widgetscale;
			dimensions.scaley *= widgetscale;
		} else if(0 == strcmp(scale_by, "Drawable")){
			dimensions.scalex *= drawablescale;
			dimensions.scaley *= drawablescale;
		} else if(0 == strcmp(scale_by, "Ground")){
			dimensions.scalex *= groundscale;
			dimensions.scaley *= groundscale;
		} else  {
			bbWarning(0 == strcmp(scale_by, "None"), "bad Scale By in sprites.csv\n");
		}


		bbTextures_lookup(&texturePtr, textures, texture);
		bbSprite_new(sprites, key, address, texturePtr, &dimensions);
	}

	fclose(file);
	*self = sprites;

    //bbDictionary_print(sprites->dictionary);
	return Success;
}

bbFlag bbSprites_lookup (sfSprite** self, bbSprites * sprites, char* key){

	I32 len = strlen(key);
	char digits[] = "0123456789";
	I32 int_len = strspn(key, digits);
	I32 address;
	if(len == int_len){
		address = atoi(key);

	} else {
		bbPool_Handle handle;
		bbDictionary_lookup(sprites->dictionary, key, &handle);
		address = handle.u64;
	}
	bbAssert(address < sprites->numSprites, "address out of bounds\n");

	*self = sprites->sprites[address];

	return Success;
}

bbFlag bbSprites_lookupInt(bbSprites* sprites, I32* address, char* key){

	I32 len = strlen(key);
	char digits[] = "0123456789";
	I32 int_len = strspn(key, digits);
	I32 address1;
	if(len == int_len){
		address1 = atoi(key);

	} else {
		bbPool_Handle handle;
		bbDictionary_lookup(sprites->dictionary, key, &handle);
		address1 = handle.u64;
	}
	bbAssert(address1 < sprites->numSprites,
             "address (%d) out of bounds (%d)\n", address1,sprites->numSprites);

	*address = address1;

	return Success;
}
