#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbPrime.h"
#include "engine/graphics/bbDrawfunctions.h"
#include "engine/logic/bbTerminal.h"
#include "engine/widgets/bbWidget.h"
#include "engine/2point5D/bbViewport.h"
#include "engine/2point5D/bbOverlays.h"

extern sfRenderWindow* testWindow;



//typedef bbFlag bbDrawFunction(void* drawable, void* frameDescriptor, void* cl);
bbFlag bbDrawFunction_test(void* drawable, void* frameDescriptor, void* cl) {
	//bbHere();
	return Success;
}

//Draw a sprite belonging to a widget
bbFlag bbDrawFunction_sprite(void* drawable, void* frameDescriptor, void* cl){
	bbWidget* widget = drawable;
	bbFrame* frame = frameDescriptor;
    drawFuncClosure* closure = cl;
    bbGraphics* graphics = closure->graphics;

	I32 spriteInt = frame->handle.u64;
	sfSprite* sprite = graphics->sprites->sprites[spriteInt];


    //bbDebug("spriteInt = %d, sprite = %p, target = %p, window = %p\n",
    //        spriteInt, sprite, target, testWindow);
	bbScreenPoints SP;
	SP.x = widget->rect.left + frame->offset.x;
	SP.y = widget->rect.top + frame->offset.y;

	sfVector2f position = bbScreenPoints_getV2f(SP);
	sfSprite_setPosition(sprite, position);


    sfRenderWindow_drawSprite(closure->target, sprite, NULL);

//bbHere();
	return Success;
}

// Draw an animation belonging to a widget;
bbFlag bbDrawFunction_animation(void* drawable, void* frameDescriptor, void* cl){

	bbWidget* widget = drawable;
	bbFrame* frame_descriptor = frameDescriptor;
    drawFuncClosure* closure = cl;
    bbGraphics* graphics = closure->graphics;

	bbAnimation* animation = graphics->animations->animations[frame_descriptor->handle.u64];

	I32 angle = 0;
	I32 frames = animation->frames;


	//bbDebug("key = %s, maptime = %d, starttime= %d, framerate = %f, frames = %d\n",
	//		animation->key, mapTime, frame_descriptor->startTime,animation->framerate, animation->frames );
	I32 frame = (int)((double)(closure->mapTime - frame_descriptor->startTime) *
            (double)animation->framerate * frame_descriptor->framerate) % animation->frames;
	I32 sprite_int = animation->Sprites[angle*frames+frame].u64;
	sfSprite* sprite = animation->sprites->sprites[sprite_int];



	bbScreenPoints SP;
	SP.x = widget->rect.left + frame_descriptor->offset.x;
	SP.y = widget->rect.top + frame_descriptor->offset.y;
	sfVector2f position = bbScreenPoints_getV2f(SP);

	sfSprite_setPosition(sprite, position);
	sfRenderWindow_drawSprite(closure->target, sprite, NULL);

	return Success;
}

//Look up default draw function for a given animation
bbFlag bbDrawfunction_default(void* drawable, void* frameDescriptor, void* cl){
	bbWidget* widget = drawable;
	bbFrame* frame_descriptor = frameDescriptor;
    drawFuncClosure* closure = cl;
    bbGraphics* graphics = closure->graphics;
	bbAnimation* animation = graphics->animations->animations[frame_descriptor->handle.u64];
	I32 drawFunctionInt = animation->drawFunction;
	bbDrawFunction *drawFunction = graphics->drawfunctions->functions[drawFunctionInt];
	return drawFunction(drawable, frame_descriptor, cl);


}

bbFlag bbDrawfunction_composition(void* drawable, void* frameDescriptor, void* cl){

	bbFrame* self_frame = frameDescriptor;
    drawFuncClosure* closure = cl;
    bbGraphics* graphics = closure->graphics;
	bbComposition* composition = graphics->compositions->compositions[self_frame->handle.u64];
	bbFrame* input_frame;
	bbFrame output_frame;
	//void* output_object;

	//bbDebug("composition->num_frames = %d\n", composition->num_frames);
	for (int i = 0; i < composition->num_frames; i++){
		input_frame = &composition->frame[i];

		output_frame.type = input_frame->type;
		output_frame.handle = input_frame->handle;
		output_frame.offset.x = input_frame->offset.x + self_frame->offset.x;
		output_frame.offset.y = input_frame->offset.y + self_frame->offset.y;
		output_frame.framerate = input_frame->framerate * self_frame->framerate;
		output_frame.startTime = input_frame->startTime + self_frame->startTime;
		output_frame.drawfunction = input_frame->drawfunction;


		if (output_frame.drawfunction <0 || output_frame.drawfunction> 4){
			//bbDebug ("drawfunction == %d, type = %d\n",
			//		 output_frame.drawfunction, output_frame.type);
		} else {

			bbDrawFunction *drawFunction =graphics->drawfunctions->functions[output_frame.drawfunction];
			drawFunction(drawable, &output_frame, cl);
		}
	}
    return Success;
}

bbFlag bbDrawfunction_viewport(void* drawable, void* frameDescriptor, void* cl){
    bbWidget* widget = drawable;
    bbFrame* frame_descriptor = frameDescriptor;
    drawFuncClosure* closure = cl;
    bbViewport* viewport = widget->extra_data;

    bbScreenPoints SP;
    SP.x = widget->rect.left;
    SP.y = widget->rect.top;
    sfVector2f pos = bbScreenPoints_getV2f(SP);

    sfSprite_setPosition(viewport->background.sprite, pos);

    bbViewport_draw(closure->target, viewport);
    return Success;
}

bbFlag bbDrawfunction_overlay(void* drawable, void* frameDescriptor, void* cl){
    bbOverlay* overlay = drawable;
    drawFuncClosure* foo = cl;

    bbDebug("overlay label: %s\n", overlay->label);

    return Success;

}

bbFlag bbDrawfunctions_new(bbDrawfunctions** drawfunctions){
	I32 num = 7;
	bbDrawfunctions* functions = malloc(sizeof(bbDrawfunctions) + num * sizeof(bbDrawFunction));
    bbAssert(functions!=NULL, "bad malloc");
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

	functions->functions[4] = bbDrawfunction_composition;
	handle.u64 = 4;
	bbDictionary_add(functions->dictionary, "COMPOSITION", handle);

    functions->functions[5] = bbDrawfunction_viewport;
    handle.u64 = 5;
    bbDictionary_add(functions->dictionary, "VIEWPORT", handle);

    functions->functions[6] = bbDrawfunction_overlay;
    handle.u64 = 6;
    bbDictionary_add(functions->dictionary, "OVERLAY", handle);


    *drawfunctions = functions;
	return Success;
}