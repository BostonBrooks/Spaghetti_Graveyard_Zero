#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbPrime.h"
#include "engine/graphics/bbDrawfunctions.h"
#include "engine/logic/bbTerminal.h"
#include "engine/widgets/bbWidget.h"

bbFlag bbDrawFunction_test(struct bbGraphics* graphics, void* drawable, void* frameDescriptor, void* target) {
	bbHere();
	return Success;
}

bbFlag bbDrawFunction_sprite(struct bbGraphics* graphics, void* drawable, void* frameDescriptor, void* target){
	bbWidget* widget = drawable;
	bbFrame* frame = frameDescriptor;
	I32 spriteInt = frame->handle.u64;
	sfSprite* sprite = graphics->sprites->sprites[spriteInt];

	bbScreenPoints SP;
	SP.x = widget->rect.left + frame->offset.x;
	SP.y = widget->rect.top + frame->offset.y;
	sfVector2f position = bbScreenPoints_getV2f(SP);

	sfSprite_setPosition(sprite, position);

	sfRenderWindow_drawSprite(target, sprite, NULL);

	return Success;
}

bbFlag bbDrawfunctions_new(bbDrawfunctions** drawfunctions){
	I32 num = 2;
	bbDrawfunctions* functions = malloc(sizeof(bbDrawfunctions) + num * sizeof(bbDrawFunction));
	bbDictionary_new(&functions->dictionary, nextPrime(num));

	functions->num = num;
	bbPool_Handle handle;

	functions->functions[0] = bbDrawFunction_test;
	handle.u64 = 0;
	bbDictionary_add(functions->dictionary, "TEST", handle);

	functions->functions[1] = bbDrawFunction_sprite;
	handle.u64 = 1;
	bbDictionary_add(functions->dictionary, "SPRITE", handle);

	*drawfunctions = functions;
	return Success;
}