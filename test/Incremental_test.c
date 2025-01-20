#include <stdio.h>
#include "engine/includes/CSFML.h"
#include "engine/graphics/bbGraphics.h"
#include "engine/graphics/bbColours.h"
#include "engine/widgets/bbWidget.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbTree.h"
#include "engine/user_input/bbInput.h"
#include "engine/user_input/bbMouse.h"
#include "engine/2point5D/bbViewport.h"
#include "engine/2point5D/bbOverlay.h"

sfRenderWindow* testWindow;


int main (void){

    bbColours_init();

	printf("Hello World!\n");
	sfVideoMode mode;
	mode.height = 480;
	mode.width = 720;
	mode.bitsPerPixel = 32;
	sfRenderWindow* window = sfRenderWindow_create(mode, "early demo", sfResize | sfClose, NULL);
    testWindow = window;
	sfRenderWindow_setFramerateLimit(window, 60);

CLEARWINDOW(bbRed);

	bbGraphics graphics;
	bbTextures_new(&graphics.textures, "./maps/map0/textures.csv");



	//bbDictionary_print(graphics.textures->dictionary);
//bbHere();
	bbSprites_new(&graphics.sprites, graphics.textures, "./maps/map0/sprites.csv",1,1,1);

    //bbDictionary_print(graphics.sprites->dictionary);

CLEARWINDOW(bbRedOrange);

	bbDrawfunctions_new(&graphics.drawfunctions);

//bbHere();
CLEARWINDOW(bbOrange);

	bbAnimations_new(&graphics.animations, graphics.sprites, graphics.drawfunctions, "./maps/map0/animations.csv");

	//bbDictionary_print(graphics.animations->dictionary);
CLEARWINDOW(bbYellowOrange);

	bbCompositions_new(&graphics.compositions, graphics.sprites, graphics.animations, graphics.drawfunctions, "./maps/map0/compositions.csv");
	//bbDictionary_print(graphics.compositions->dictionary);

CLEARWINDOW(bbYellow);

    bbMouse mouse;
    bbMouse_new(&mouse, window, &graphics);

CLEARWINDOW(bbChartreuse);

    bbInput input;
    bbInput_new(&input,window, &mouse);

CLEARWINDOW(bbGreen);
//bbHere();
	bbWidgets widgets;
	bbWidgets_init(&widgets);

CLEARWINDOW(bbTeal);

//bbHere();
	bbWidget* layout;
    bbWidget_newLayout(&layout, &graphics, &widgets, NULL);

CLEARWINDOW(bbBlue);

    bbViewport* viewport;
    bbViewport_new(&viewport, 456, 466);
    bbAssert(viewport != NULL, "bad bbViewport_new\n");

    //bbViewport_draw(window, viewport);
    CLEARWINDOW(bbViolet);





//bbHere();
	bbWidget* Viewport;
    bbWidget_newViewport(&Viewport, &graphics, &widgets, layout, viewport);

CLEARWINDOW(bbPurple);

    bbOverlay mapIcons;
	bbOverlay_new(&mapIcons, 6, 6);



    drawFuncClosure cl;
	cl.target = window;
	cl.graphics = &graphics;

CLEARWINDOW(bbMagenta);

    bbOverlay *overlay;
    bbOverlay_new(&overlay, 2, 3);

    bbHere();

	int mapTime;
	for (mapTime = 0; ; mapTime++) {
bbPrintf("mapTime = %d\n", mapTime);
		cl.mapTime = mapTime;
        cl.GUI_time = mapTime;

        bbOverlay_draw(overlay, viewport, &graphics);

		descending_map(widgets.tree, layout, drawFunc, &cl);
        bbMouse_draw(&mouse, window);

		sfRenderWindow_display(window);
        bbViewport_clear(viewport);
        bbFlag flag = bbInput_poll(&input, window);
        if (flag == Break) break;
	}

    sfRenderWindow_destroy(window);

    bbDebug("We made it!\n");
    exit(EXIT_SUCCESS);


}