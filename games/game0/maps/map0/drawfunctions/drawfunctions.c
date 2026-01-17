#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbPrime.h"
#include "engine/graphics/bbDrawfunctions.h"
#include "engine/logic/bbTerminal.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/viewport/bbViewport.h"
#include "engine/viewport/bbDrawables.h"
#include "engine/viewport/bbMapIcons.h"
#include "engine/geometry/bbViewportCoords.h"
#include "engine/data/bbHome.h"



#include "games/game0/maps/map0/drawfunctions/drawablesprite.h"
#include "games/game0/maps/map0/drawfunctions/drawableanimation.h"
#include "games/game0/maps/map0/drawfunctions/textboxindicator.h"
#include "games/game0/maps/map0/drawfunctions/widgettext.h"
#include "games/game0/maps/map0/drawfunctions/widgetstate.h"


//typedef bbFlag bbDrawFunction(void* drawable, void* frameDescriptor, void* cl);
bbFlag bbDF_test(void* drawable, void* frameDescriptor, void* cl) {
    bbHere();
    return Success;
}

//Draw a sprite belonging to a widget
bbFlag bbDF_widgetSprite(void* drawable, void* frameDescriptor, void* cl){
    bbWidget* widget = drawable;
    bbFrame* frame = frameDescriptor;
    drawFuncClosure* closure = cl;
    bbGraphicsApp* graphics = closure->graphics;

    I32 spriteInt = frame->handle.u64;
    sfSprite* sprite = graphics->sprites->sprites[spriteInt];


    //bbDebug("spriteInt = %d, sprite = %p, target = %p, window = %p\n",
    //        spriteInt, sprite, target, home.private.window);
    bbScreenPoints SP;
    SP.x = widget->rect.left + frame->offset.x;
    SP.y = widget->rect.top + frame->offset.y;

    sfVector2f position = bbScreenPoints_getV2f(SP);
    sfSprite_setPosition(sprite, position);


    sfRenderWindow_drawSprite(closure->target, sprite, NULL);

    return Success;
}

//Draw a sprite belonging to a widget
bbFlag bbDF_layerBoundary(void* drawable, void* frameDescriptor, void* cl){
    bbWidget* widget = drawable;
    bbFrame* frame = frameDescriptor;
    drawFuncClosure* closure = cl;
    bbGraphicsApp* graphics = closure->graphics;

    I32 spriteInt = frame->handle.u64;
    sfSprite* sprite = graphics->sprites->sprites[spriteInt];


    //bbDebug("spriteInt = %d, sprite = %p, target = %p, window = %p\n",
    //        spriteInt, sprite, target, home.private.window);
    bbScreenPoints SP;
    SP.x = 0;
    SP.y = 0;

    sfVector2f position = bbScreenPoints_getV2f(SP);
    sfSprite_setPosition(sprite, position);


    sfRenderWindow_drawSprite(closure->target, sprite, NULL);

    return Success;
}

// Draw an animation belonging to a widget;
bbFlag bbDF_widgetAnimation(void* drawable, void* frameDescriptor, void* cl){

    bbWidget* widget = drawable;
    bbFrame* frame_descriptor = frameDescriptor;
    drawFuncClosure* closure = cl;
    bbGraphicsApp* graphics = closure->graphics;

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
    bbGraphicsApp* graphics = closure->graphics;
    bbAnimation* animation = graphics->animations->animations[frame_descriptor->handle.u64];
    I32 drawFunctionInt = animation->drawFunction;
    bbDrawFunction *drawFunction = graphics->drawfunctions->functions[drawFunctionInt];
    return drawFunction(drawable, frame_descriptor, cl);


}

bbFlag bbDF_composition(void* drawable, void* frameDescriptor, void* cl){

    bbFrame* self_frame = frameDescriptor;
    drawFuncClosure* closure = cl;
    bbGraphicsApp* graphics = closure->graphics;
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

bbFlag bbDF_mapiconTest(void* drawable, void* frameDescriptor, void* cl){
    bbDrawable* mapicon = drawable;
    drawFuncClosure* foo = cl;
    bbFrame* frame_descriptor = frameDescriptor;


    I32 spriteInt = frame_descriptor->handle.u64;

    bbGraphicsApp* graphics = foo->graphics;
    sfSprite* sprite = graphics->sprites->sprites[spriteInt];


    bbViewport* VP = foo->target;

    sfRenderTexture* renderTexture = VP->mapicon.renderTexture;

    sfVector2f V2F = bbMapCoords_getV2f_mapicon(mapicon->coords, VP);



    sfSprite_setPosition(sprite, V2F);
    sfRenderTexture_drawSprite(renderTexture, sprite, NULL);

    return Success;

}

bbFlag bbDF_eyeCandyTest(void* drawable, void* frameDescriptor, void* cl){
    bbDrawable* mapicon = drawable;
    drawFuncClosure* foo = cl;

    //bbDebug("eye candy\n", mapicon->label);
    I32 animationInt = 7;

    bbGraphicsApp* graphics = foo->graphics;
    I32 time = foo->mapTime;
    bbAnimation* animation = graphics->animations->animations[animationInt];
    I32 frames = animation->frames;
    I32 frame = time % frames;
    I32 spriteInt = animation->Sprites[frame].u64;
    bbSprites* sprites = animation->sprites;
    sfSprite* sprite = sprites->sprites[spriteInt];


    bbViewport* VP = foo->target;

    sfRenderTexture* renderTexture = VP->main.renderTexture;

    sfVector2f V2F = bbMapCoords_getV2f(mapicon->coords, VP);



    sfSprite_setPosition(sprite, V2F);
    sfRenderTexture_drawSprite(renderTexture, sprite, NULL);

    return Success;

}


bbFlag bbDF_widgetTextBox(void* drawable, void* frameDescriptor, void* cl)
{

    bbWidget* widget = drawable;
    bbFrame* frame = frameDescriptor;
    drawFuncClosure* closure = cl;
    bbGraphicsApp* graphics = closure->graphics;

    sfRenderWindow_drawText(closure->target, widget->typeData.textBox.text, NULL);
    return Success;


}


bbFlag bbDrawfunctions_new(bbDrawfunctions** drawfunctions){
    I32 num = 16;
    bbDrawfunctions* functions = malloc(sizeof(bbDrawfunctions) + num * sizeof(bbDrawFunction*));
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

    functions->functions[6] = bbDF_mapiconTest;
    handle.u64 = 6;
    bbDictionary_add(functions->dictionary, "MAPICONTEST", handle);


    functions->functions[7] = bbDF_eyeCandyTest;
    handle.u64 = 7;
    bbDictionary_add(functions->dictionary, "EYECANDYTEST", handle);


    functions->functions[8] = bbDF_widgetTextBox;
    handle.u64 = 8;
    bbDictionary_add(functions->dictionary, "TEXTBOX", handle);

    functions->functions[9] = bbDF_drawableSprite;
    handle.u64 = 9;
    bbDictionary_add(functions->dictionary, "DRAWABLESPRITE", handle);

    functions->functions[10] = bbDF_drawableAnimation;
    handle.u64 = 10;
    bbDictionary_add(functions->dictionary, "DRAWABLEANIMATION", handle);

    functions->functions[11] = bbDF_layerBoundary;
    handle.u64 = 11;
    bbDictionary_add(functions->dictionary, "LAYERBOUNDARY", handle);

    functions->functions[12] = bbDF_textboxIndicator;
    handle.u64 = 12;
    bbDictionary_add(functions->dictionary, "TEXTBOXINDICATOR", handle);

    functions->functions[13] = bbDF_widgetText;
    handle.u64 = 13;
    bbDictionary_add(functions->dictionary, "WIDGETTEXT", handle);

    functions->functions[14] = bbDF_widgetState;
    handle.u64 = 14;
    bbDictionary_add(functions->dictionary, "WIDGETSTATE", handle);

    functions->functions[15] = bbDF_drawableAnimationWAngle;
    handle.u64 = 15;
    bbDictionary_add(functions->dictionary, "DRAWABLEANIMATIONWANGLE", handle);


    *drawfunctions = functions;
    return Success;
}