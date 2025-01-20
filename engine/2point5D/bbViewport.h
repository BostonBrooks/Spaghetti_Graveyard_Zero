/**
 * @file
 * @brief the viewport is a widget that can be drawn to the screen,
 * and can be clicked by the player.
 * viewport has a bbViewport object which does the actual rendering of
 * the ground surface and bbDrawables
 **/
#ifndef BBVIEWPORT_H
#define BBVIEWPORT_H

#include "engine/includes/CSFML.h"
#include "engine/logic/bbFlag.h"
#include "engine/geometry/bbCoordinates.h"

typedef struct {
	sfRenderTexture* renderTexture;
	sfTexture* texture;
	sfSprite* sprite;
} bbRenderable;



typedef struct {
	bbRenderable background;
	bbRenderable ground;
	bbRenderable main;
    bbRenderable overlay;

    sfRenderStates renderStates;
	sfShader* shader;

    bbMapCoords viewpoint;
    int height;
    int width;

} bbViewport;

bbFlag bbRenderable_new(bbRenderable* renderable, I32 height, I32 width);
bbFlag bbViewport_new(bbViewport** viewport,  I32 height, I32 width);
bbFlag bbViewport_draw(sfRenderWindow* window, bbViewport* viewport);


#endif // BBVIEWPORT_H