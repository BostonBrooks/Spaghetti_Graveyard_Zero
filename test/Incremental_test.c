#include <stdio.h>
#include "engine/includes/csfml.h"
#include "engine/graphics/bbGraphics.h"
#include "engine/widgets/bbWidget.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbTree.h"

int main (void){
	printf("Hello World!\n");
	sfVideoMode mode;
	mode.height = 480;
	mode.width = 720;
	mode.bitsPerPixel = 32;
	sfRenderWindow* window = sfRenderWindow_create(mode, "early demo", sfResize | sfClose, NULL);


	bbGraphics graphics;
	bbTextures_new(&graphics.textures, "./maps/map0/textures.csv");

	bbSprites_new(&graphics.sprites, graphics.textures, "./maps/map0/sprites.csv",1,1,1);


	bbDrawfunctions_new(&graphics.drawfunctions);

	bbAnimations_new(&graphics.animations, graphics.sprites, graphics.drawfunctions, "./maps/map0/animations.csv");


	bbWidgets widgets;
	bbWidgets_init(&widgets);


	bbWidget* layout;
	bbWidget_layoutNew(&layout, &graphics, &widgets, NULL);

	bbWidget* viewport;
	bbWidget_viewportNew(&viewport, &graphics, &widgets, layout);

	targets cl;
	cl.target = window;
	cl.graphics = &graphics;

	descending_map(widgets.tree, layout, drawFunc, &cl);

	sfRenderWindow_display(window);

	sfTime time = sfSeconds(5);
	sfSleep(time);
	sfRenderWindow_destroy(window);

	bbHere();
	exit(EXIT_SUCCESS);
}