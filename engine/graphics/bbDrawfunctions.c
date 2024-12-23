#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbPrime.h"
#include "engine/graphics/bbDrawfunctions.h"
#include "engine/logic/bbTerminal.h"
#include "engine/widgets/bbWidget.h"
//extern sfRenderWindow* testWindow;

//TODO cleanup global value
extern int mapTime;

bbFlag bbDrawFunction_test(struct bbGraphics* graphics, void* drawable, void* frameDescriptor, void* target) {
	//bbHere();
	return Success;
}

//Draw a sprite belonging to a widget
bbFlag bbDrawFunction_sprite(struct bbGraphics* graphics, void* drawable, void* frameDescriptor, void* target){
	bbWidget* widget = drawable;
	bbFrame* frame = frameDescriptor;
	I32 spriteInt = frame->handle.u64;
	sfSprite* sprite = graphics->sprites->sprites[spriteInt];


    //bbDebug("spriteInt = %d, sprite = %p, target = %p, window = %p\n",
    //        spriteInt, sprite, target, testWindow);
	bbScreenPoints SP;
	SP.x = widget->rect.left + frame->offset.x;
	SP.y = widget->rect.top + frame->offset.y;

	sfVector2f position = bbScreenPoints_getV2f(SP);
	sfSprite_setPosition(sprite, position);
//bbHere();

    //bbAssert(target == testWindow, "wrong target\n"); //target is good
    sfVector2f pos = sfSprite_getPosition(sprite); //sprite is good
    //bbDebug("pos = (%f,%f)\n", pos.x, pos.y);
    //Causes exit when not run in gdb
    //TODO TODO TODO WARNING  - works now?
	sfRenderWindow_drawSprite(target, sprite, NULL);

//bbHere();
	return Success;
}

// Draw an animation belonging to a widget;
bbFlag bbDrawFunction_animation(struct bbGraphics* graphics, void* drawable, void* frameDescriptor, void* target){

	bbWidget* widget = drawable;
	bbFrame* frame_descriptor = frameDescriptor;

	bbAnimation* animation = graphics->animations->animations[frame_descriptor->handle.u64];

	I32 angle = 0;
	I32 frames = animation->frames;


	//bbDebug("key = %s, maptime = %d, starttime= %d, framerate = %f, frames = %d\n",
	//		animation->key, mapTime, frame_descriptor->startTime,animation->framerate, animation->frames );
	I32 frame = (int)((double)(mapTime - frame_descriptor->startTime) * (double)animation->framerate) % animation->frames;
	I32 sprite_int = animation->Sprites[angle*frames+frame].u64;
	sfSprite* sprite = animation->sprites->sprites[sprite_int];



	bbScreenPoints SP;
	SP.x = widget->rect.left + frame_descriptor->offset.x;
	SP.y = widget->rect.top + frame_descriptor->offset.y;
	sfVector2f position = bbScreenPoints_getV2f(SP);

	sfSprite_setPosition(sprite, position);
	sfRenderWindow_drawSprite(target, sprite, NULL);

	return Success;
}

//Look up default draw function for a given animation
bbFlag bbDrawfunction_default(struct bbGraphics* graphics, void* drawable, void* frameDescriptor, void* target){
	bbWidget* widget = drawable;
	bbFrame* frame_descriptor = frameDescriptor;
	bbAnimation* animation = graphics->animations->animations[frame_descriptor->handle.u64];
	I32 drawFunctionInt = animation->drawFunction;
	bbDrawFunction *drawFunction = graphics->drawfunctions->functions[drawFunctionInt];
	return drawFunction(graphics, drawable, frameDescriptor, target);

}

bbFlag bbDrawfunctions_new(bbDrawfunctions** drawfunctions){
	I32 num = 4;
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

	functions->functions[2] = bbDrawFunction_animation;
	handle.u64 = 2;
	bbDictionary_add(functions->dictionary, "ANIMATION", handle);

	functions->functions[3] = bbDrawfunction_default;
	handle.u64 = 3;
	bbDictionary_add(functions->dictionary, "DEFAULT", handle);

	*drawfunctions = functions;
	return Success;
}