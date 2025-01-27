#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbPrime.h"
#include "engine/graphics/bbDrawfunctions.h"
#include "engine/logic/bbTerminal.h"
#include "engine/widgets/bbWidget.h"
#include "engine/2point5D/bbViewport.h"
#include "engine/2point5D/bbOverlays.h"
#include "engine/2point5D/bbViewportCoords.h"

extern sfRenderWindow* testWindow;


//typedef bbFlag bbDrawFunction(void* drawable, void* frameDescriptor, void* cl);
bbFlag bbDF_test(void* drawable, void* frameDescriptor, void* cl) {
	//bbHere();
	return Success;
}

//Draw a sprite belonging to a widget
bbFlag bbDF_widgetSprite(void* drawable, void* frameDescriptor, void* cl){
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
bbFlag bbDF_widgetAnimation(void* drawable, void* frameDescriptor, void* cl){

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
bbFlag bbDF_widgetAnimationDefault(void* drawable, void* frameDescriptor, void* cl){
	bbWidget* widget = drawable;
	bbFrame* frame_descriptor = frameDescriptor;
    drawFuncClosure* closure = cl;
    bbGraphics* graphics = closure->graphics;
	bbAnimation* animation = graphics->animations->animations[frame_descriptor->handle.u64];
	I32 drawFunctionInt = animation->drawFunction;
	bbDrawFunction *drawFunction = graphics->drawfunctions->functions[drawFunctionInt];
	return drawFunction(drawable, frame_descriptor, cl);


}

bbFlag bbDF_composition(void* drawable, void* frameDescriptor, void* cl){

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


///draw the viewport to the screen
bbFlag bbDF_widgetViewport(void* drawable, void* frameDescriptor, void* cl){
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

bbFlag bbDF_overlayTest(void* drawable, void* frameDescriptor, void* cl){
    bbOverlay* overlay = drawable;
    drawFuncClosure* foo = cl;

    bbDebug("overlay\n", overlay->label);
    I32 spriteInt = 86;

    bbGraphics* graphics = foo->graphics;
    sfSprite* sprite = graphics->sprites->sprites[spriteInt];


    bbViewport* VP = foo->target;

    sfRenderTexture* renderTexture = VP->overlay.renderTexture;

    sfVector2f V2F = bbMapCoords_getV2f_overlay(overlay->coords, VP);



    sfSprite_setPosition(sprite, V2F);
    sfRenderTexture_drawSprite(renderTexture, sprite, NULL);

    return Success;

}

bbFlag bbDF_eyeCandyTest(void* drawable, void* frameDescriptor, void* cl){
    bbOverlay* overlay = drawable;
    drawFuncClosure* foo = cl;

    bbDebug("eye candy\n", overlay->label);
    I32 spriteInt = 8;

    bbGraphics* graphics = foo->graphics;
    sfSprite* sprite = graphics->sprites->sprites[spriteInt];


    bbViewport* VP = foo->target;

    sfRenderTexture* renderTexture = VP->main.renderTexture;

    sfVector2f V2F = bbMapCoords_getV2f(overlay->coords, VP);



    sfSprite_setPosition(sprite, V2F);
    sfRenderTexture_drawSprite(renderTexture, sprite, NULL);

    return Success;

}

bbFlag bbDrawfunctions_new(bbDrawfunctions** drawfunctions){
	I32 num = 8;
	bbDrawfunctions* functions = malloc(sizeof(bbDrawfunctions) + num * sizeof(bbDrawFunction));
    bbAssert(functions!=NULL, "bad malloc");
	bbDictionary_new(&functions->dictionary, nextPrime(num));

	functions->num = num;
	bbPool_Handle handle;

	functions->functions[0] = bbDF_test;
	handle.u64 = 0;
	bbDictionary_add(functions->dictionary, "TEST", handle);

	functions->functions[1] = bbDF_widgetSprite;
	handle.u64 = 1;
	bbDictionary_add(functions->dictionary, "WIDGETSPRITE", handle);

	functions->functions[2] = bbDF_widgetAnimation;
	handle.u64 = 2;
	bbDictionary_add(functions->dictionary, "WIDGETANIMATION", handle);

	functions->functions[3] = bbDF_widgetAnimationDefault;
	handle.u64 = 3;
	bbDictionary_add(functions->dictionary, "DEFAULT", handle);

	functions->functions[4] = bbDF_composition;
	handle.u64 = 4;
	bbDictionary_add(functions->dictionary, "COMPOSITION", handle);

    functions->functions[5] = bbDF_widgetViewport;
    handle.u64 = 5;
    bbDictionary_add(functions->dictionary, "WIDGETVIEWPORT", handle);

    functions->functions[6] = bbDF_overlayTest;
    handle.u64 = 6;
    bbDictionary_add(functions->dictionary, "OVERLAYTEST", handle);


    functions->functions[7] = bbDF_eyeCandyTest;
    handle.u64 = 7;
    bbDictionary_add(functions->dictionary, "EYECANDYTEST", handle);


    *drawfunctions = functions;
	return Success;
}