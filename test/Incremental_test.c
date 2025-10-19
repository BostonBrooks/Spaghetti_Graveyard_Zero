#include <stdio.h>
#include "engine/includes/CSFML.h"
#include "engine/graphics/bbGraphics.h"
#include "engine/graphics/bbColours.h"
#include "engine/widgets/bbWidget.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbTree.h"
#include "engine/user_input/bbInput.h"
#include "engine/2point5D/bbViewport.h"
#include "engine/2point5D/bbOverlays.h"
#include "engine/widgets/bbWidgetFunctions.h"
#include "engine/geometry/bbCoordinates.h"

sfRenderWindow* testWindow;
bbWidgets* testWidgets;
bbWidgetFunctions* testFunctions;
bbMapCoords testGoalPoint;



int main (void){

    testGoalPoint.i = 0;
    testGoalPoint.j = 0;
    testGoalPoint.k = 0;

    bbColours_init();

	printf("Hello World!\n");
	sfVideoMode mode;
    mode.width = 720;
	mode.height = 480;
	mode.bitsPerPixel = 32;
	sfRenderWindow* window = sfRenderWindow_create(mode, "early demo", sfResize | sfClose, NULL);
	sfRenderWindow_setFramerateLimit(window, 60);
	sfRenderWindow_setMouseCursorVisible(window, sfFalse);

	testWindow = window;
CLEARWINDOW(bbRed);

	bbGraphics graphics;
	bbTextures_new(&graphics.textures,
                   "./maps/map0/graphics/textures.csv");



	//bbDictionary_print(graphics.textures->dictionary);
//bbHere();
	bbSprites_new(&graphics.sprites, graphics.textures,
                  "./maps/map0/graphics/sprites.csv",1,1,1);

    //bbDictionary_print(graphics.sprites->dictionary);

CLEARWINDOW(bbRedOrange);

	bbDrawfunctions_new(&graphics.drawfunctions);


CLEARWINDOW(bbOrange);

	void* memtest = malloc(sizeof(char) * 1028);
	bbAnimations_new(&graphics.animations, graphics.sprites, graphics
            .drawfunctions, "./maps/map0/graphics/animations.csv");

	//bbDictionary_print(graphics.animations->dictionary);
CLEARWINDOW(bbYellowOrange);

	bbCompositions_new(&graphics.compositions, graphics.sprites, graphics
            .animations, graphics.drawfunctions,
            "./maps/map0/graphics/compositions.csv");
	//bbDictionary_print(graphics.compositions->dictionary);

CLEARWINDOW(bbYellow);




CLEARWINDOW(bbChartreuse);


CLEARWINDOW(bbGreen);
//bbHere();

	bbWidgetFunctions functions;
//	bbWidgetMouse_new(&functions);
	//testFunctions = &functions;


	bbWidgets widgets;
	bbWidgets_init(&widgets);
	//testWidgets = &widgets;

	bbMoose moose;

	bbMoose_Init(&moose, &widgets, &graphics);

	bbMooseFunctions_init(&moose.functions);
	bbMooseFunctions_populate(&moose.functions);


	int tst = bbMooseFunctions_getInt(&moose.functions,MooseIsOver, "ALWAYS");
	bbDebug("tst = %d\n", tst);
	tst = bbMooseFunctions_getInt(&moose.functions,MooseIsOver, "TELEPORT");
	bbDebug("tst = %d\n", tst);
	tst = bbMooseFunctions_getInt(&moose.functions,MooseIsOver, "HOVER");
	bbDebug("tst = %d\n", tst);


	bbInput input;
	bbInput_new(&input,window, &moose);

CLEARWINDOW(bbTeal);

//bbHere();
	bbWidget *layout;
//    bbWidget_Constructor* function0;
    bbScreenPoints SP;
    SP.x = 600*8;
    SP.y = 50*8;

	//Does not need to be listed in constructor table
    bbWidget_newLayout(&layout, &graphics, &widgets, NULL);




CLEARWINDOW(bbBlue);

    bbViewport* viewport;
    bbViewport_new(&viewport, 456, 466);
    bbAssert(viewport != NULL, "bad bbViewport_new\n");

    //bbViewport_draw(window, viewport);
    CLEARWINDOW(bbViolet);





//bbHere();
	bbWidget* viewportWidget;
	//Does not need to be listed in constructor table
    bbWidget_newViewport(&viewportWidget, &graphics, &widgets, layout,
                         viewport);

CLEARWINDOW(bbPurple);

//    bbWidgetFunctions_getFunction((void**)&function0,
//                                  testWidgets->functions,
//                                  WidgetConstructor, "Sphere");

//typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
//                                     bbWidgets* widgets, bbScreenPoints
//                                     screen_coords, bbWidget* parent);





    drawFuncClosure cl;


CLEARWINDOW(bbMagenta);

    bbOverlays *overlays;
    bbOverlays_new((void**)&overlays, &graphics, 7, 9);

    bbHere();


////////////New Code to replace widgets /////////////////

	//bbWidgets widgets0;
	//bbWidgets_init(&widgets0);
	bbWidget* widget0;

	bbScreenPoints SP0;

	SP0.x = rand()%(720*8); SP0.y = rand()%(480*8);
	bbWidget_constructor(&widget0, &widgets, &graphics, SP0, layout, "SPHERE");
    bbAssert(widget0 != NULL, "Returned NULL address\n");



	SP0.x = 500*8; SP0.y = 23*8;
	bbWidget_constructor(&widget0, &widgets, &graphics, SP0, layout, "BUTTON");


////////////////////////////////////////////////////////
    CLEARWINDOW(bbRed);


	int mapTime;
	for (mapTime = 0; ; mapTime++) {



        bbMapCoords difference;
        difference.i = testGoalPoint.i - viewport->viewpoint.i;
        difference.j = testGoalPoint.j - viewport->viewpoint.j;
        difference.k = 0;

        float speed = 8;

        float distance = sqrt(difference.i*difference.i
                + difference.j*difference.j);

        if (distance <= speed){
            viewport->viewpoint = testGoalPoint;
        } else {
            viewport->viewpoint.i += difference.i * speed / distance;
            viewport->viewpoint.j += difference.j * speed / distance;
        }



		bbMoose_isOver(&moose, &widgets);
		bbMoose_Update(&moose, &widgets, &graphics);



	if (mapTime % 50 == 0) bbPrintf("mapTime = %d\n", mapTime);
		cl.mapTime = mapTime;
        cl.GUI_time = mapTime;
        cl.graphics = &graphics;

        cl.target = viewport;


        bbOverlays_draw(overlays, &cl);


        cl.target = window;
        bbWidgets_draw(&widgets, &cl);

		bbMoose_Draw(&moose, &widgets, &graphics, window);
		sfRenderWindow_display(window);
        bbViewport_clear(viewport);
        bbFlag flag = bbInput_poll(&input, window);
        if (flag == Break) break;
	}

    sfRenderWindow_destroy(window);

    bbDebug("We made it!\n");
    exit(EXIT_SUCCESS);


}

