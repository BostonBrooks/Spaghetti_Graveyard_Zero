/**
 * @file
 * @brief the viewport is a widget that can be drawn to the screen,
 * and can be clicked by the player.
 * viewport has a bbViewport object which does the actual rendering of
 * the ground surface and bbDrawables
 **/
#ifndef BBVIEWPORT_H
#define BBVIEWPORT_H

#include "engine/includes/csfml.h"
typedef struct {
	sfRenderTexture* renderTexture;
	sfTexture* texture;
	sfSprite* sprite;
} bbViewport_renderable;

typedef struct {
	bbViewport_renderable background;
	bbViewport_renderable ground;
	bbViewport_renderable main;
	bbViewport_renderable highlights;
	bbViewport_renderable healthbars;

	bbViewport_renderable output;

	//renderstates and shader?
} bbViewport;


#endif // BBVIEWPORT_H