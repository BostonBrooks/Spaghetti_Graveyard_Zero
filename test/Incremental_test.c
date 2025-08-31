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
#include "engine/2point5D/bbOverlays.h"
#include "engine/widgets/bbWidgetMouse.h"
#include "engine/widgets/bbWidgetFunctions.h"

sfRenderWindow* testWindow;
bbWidgets* testWidgets;
bbWidgetFunctions* testFunctions;

int main (void){

    bbColours_init();

	printf("Hello World!\n");
	sfVideoMode mode;
    mode.width = 720;
	mode.height = 480;
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

	bbWidgetFunctions functions;
	bbWidgetMouse_new(&functions);
	testFunctions = &functions;


	bbWidgets widgets;
	bbWidgets_init(&widgets);
	testWidgets = &widgets;

CLEARWINDOW(bbTeal);

//bbHere();
	bbWidget *layout;
    bbWidget_Constructor* function0;
    bbScreenPoints SP;
    SP.x = 600*8;
    SP.y = 50*8;

    bbWidget_newLayout(&layout, &graphics, &widgets, NULL);




CLEARWINDOW(bbBlue);

    bbViewport* viewport;
    bbViewport_new(&viewport, 456, 466);
    bbAssert(viewport != NULL, "bad bbViewport_new\n");

    //bbViewport_draw(window, viewport);
    CLEARWINDOW(bbViolet);





//bbHere();
	bbWidget* viewportWidget;
    bbWidget_newViewport(&viewportWidget, &graphics, &widgets, layout,
                         viewport);

CLEARWINDOW(bbPurple);

    bbWidgetFunctions_getFunction((void**)&function0,
                                  testWidgets->functions,
                                  WidgetConstructor, "Sphere");

//typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
//                                     void* widgets, bbScreenPoints
//                                     screen_coords, bbWidget* parent);

    bbWidget *sphere;
    function0(&sphere, &graphics, &widgets, SP, layout);



    drawFuncClosure cl;


CLEARWINDOW(bbMagenta);

    bbOverlays *overlays;
    bbOverlays_new((void**)&overlays, &graphics, 7, 9);

    bbHere();






	int mapTime;
	for (mapTime = 0; ; mapTime++) {

        sphere->rect.left = rand()%(720*8);
        sphere->rect.top = rand()%(480*8);

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
        bbWidgets_draw(&widgets, &cl);
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

