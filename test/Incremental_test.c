#include <stdio.h>
#include "engine/includes/CSFML.h"
#include "engine/graphics/bbGraphics.h"
#include "engine/graphics/bbColours.h"
#include "engine/wodgets/bbWodget.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbTree.h"
#include "engine/user_input/bbInput.h"
#include "engine/user_input/bbMouse.h"
#include "engine/2point5D/bbViewport.h"
#include "engine/2point5D/bbOverlays.h"
#include "engine/wodgets/bbWodgetMouse.h"

sfRenderWindow* testWindow;
bbWodgets* testWodgets;
bbWodgetFunctions* testFunctions;

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


CLEARWINDOW(bbOrange);

	void* memtest = malloc(sizeof(char) * 1028);
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

	bbWodgetFunctions functions;
	bbWodgetMouse_new(&functions);
	testFunctions = &functions;


	bbWodgets wodgets;
	bbWodgets_init(&wodgets);
	testWodgets = &wodgets;

CLEARWINDOW(bbTeal);

//bbHere();
	bbWodget* layout;
    bbWodget_newLayout(&layout, &graphics, &wodgets, NULL);

CLEARWINDOW(bbBlue);

    bbViewport* viewport;
    bbViewport_new(&viewport, 456, 466);
    bbAssert(viewport != NULL, "bad bbViewport_new\n");

    //bbViewport_draw(window, viewport);
    CLEARWINDOW(bbViolet);





//bbHere();
	bbWodget* Viewport;
    bbWodget_newViewport(&Viewport, &graphics, &wodgets, layout, viewport);

CLEARWINDOW(bbPurple);





    drawFuncClosure cl;


CLEARWINDOW(bbMagenta);

    bbOverlays *overlays;
    bbOverlays_new(&overlays, &graphics, 7, 9);

    bbHere();

	int mapTime;
	for (mapTime = 0; ; mapTime++) {

        viewport->viewpoint.i = 5120 * sin(mapTime / 360.0) + 7000;
        viewport->viewpoint.j = 5120 * cos(mapTime / 360.0) + 7000;

	if (mapTime % 50 == 0) bbPrintf("mapTime = %d\n", mapTime);
		cl.mapTime = mapTime;
        cl.GUI_time = mapTime;
        cl.graphics = &graphics;

        cl.target = viewport;
        //bbOverlay_drawTest(overlays, viewport, &graphics);


        bbOverlays_draw(overlays, &cl);


        cl.target = window;
        bbWodgets_draw(&wodgets, &cl);
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

