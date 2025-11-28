#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbPrime.h"
#include "engine/graphics/bbDrawfunctions.h"
#include "engine/logic/bbTerminal.h"
#include "engine/widgets/bbWidget.h"
#include "engine/viewport/bbViewport.h"
#include "engine/viewport/bbDrawables.h"
#include "engine/viewport/bbMapIcons.h"
#include "engine/geometry/bbViewportCoords.h"
#include "engine/data/bbHome.h"

bbFlag bbDF_drawableAnimation(void* Drawable, void* frameDescriptor, void* cl){
    bbDrawable* drawable = Drawable;
    bbFrame* frame = frameDescriptor;
    drawFuncClosure* foo = cl;
    bbGraphics* graphics = foo->graphics;
    bbViewport* VP = foo->target;

    I32 animationInt = frame->handle.u64;
    bbAnimation* animation = graphics->animations->animations[animationInt];

    //TODO - angle doesnt have to be hard-wired
    I32 angle = 0;
    I32 frames = animation->frames;

    I32 frameInt = (I64)((double)(foo->mapTime - frame->startTime)
            *(double)animation->framerate*(double)frame->framerate) % frames;

    I32 spriteInt = animation->Sprites[angle*frames*frameInt].u64;

    sfSprite* sprite = animation->sprites->sprites[spriteInt];
    sfRenderTexture* renderTexture = VP->main.renderTexture;

    sfVector2f V2F = bbMapCoords_getV2f(drawable->coords, VP);

    sfSprite_setPosition(sprite,V2F);

    sfRenderTexture_drawSprite(renderTexture,sprite,NULL);

    return Success;


}