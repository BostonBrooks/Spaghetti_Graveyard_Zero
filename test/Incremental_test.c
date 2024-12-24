#include <stdio.h>
#include "engine/includes/csfml.h"
#include "engine/graphics/bbGraphics.h"
#include "engine/widgets/bbWidget.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbTree.h"

//TODO cleanup global value


int main (void){


	printf("Hello World!\n");
	sfVideoMode mode;
	mode.height = 480;
	mode.width = 720;
	mode.bitsPerPixel = 32;
	sfRenderWindow* window = sfRenderWindow_create(mode, "early demo", sfResize | sfClose, NULL);
	sfRenderWindow_setFramerateLimit(window, 60);
//bbHere();
	bbGraphics graphics;
	bbTextures_new(&graphics.textures, "./maps/map0/textures.csv");

	//bbDictionary_print(graphics.textures->dictionary);
//bbHere();
	bbSprites_new(&graphics.sprites, graphics.textures, "./maps/map0/sprites.csv",1,1,1);


//bbHere();
	bbDrawfunctions_new(&graphics.drawfunctions);

	//bbDictionary_print(graphics.sprites->dictionary);
//bbHere();
	bbAnimations_new(&graphics.animations, graphics.sprites, graphics.drawfunctions, "./maps/map0/animations.csv");

	//bbDictionary_print(graphics.animations->dictionary);

	bbCompositions_new(&graphics.compositions, graphics.sprites, graphics.animations, graphics.drawfunctions, "./maps/map0/compositions.csv");
	//bbDictionary_print(graphics.compositions->dictionary);


//bbHere();
	bbWidgets widgets;
	bbWidgets_init(&widgets);


//bbHere();
	bbWidget* layout;
	bbWidget_layoutNew(&layout, &graphics, &widgets, NULL);

//bbHere();
	bbWidget* viewport;
	bbWidget_viewportNew(&viewport, &graphics, &widgets, layout);

//bbHere();
    drawFuncClosure cl;
	cl.target = window;
	cl.graphics = &graphics;


//bbHere();
	int mapTime;
	for (mapTime = 0; ; mapTime++) {

		cl.mapTime = mapTime;
        cl.GUI_time = mapTime;
		descending_map(widgets.tree, layout, drawFunc, &cl);
		sfRenderWindow_display(window);

		sfEvent event;
		sfRenderWindow_pollEvent(window, &event);
		if (event.type == sfEvtKeyPressed) break;
	}
//bbHere();

	sfRenderWindow_destroy(window);

    bbDebug("We made it!\n");
	exit(EXIT_SUCCESS);
}