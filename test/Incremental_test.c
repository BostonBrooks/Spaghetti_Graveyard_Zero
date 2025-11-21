#include <stdio.h>
#include "engine/includes/CSFML.h"
#include "engine/graphics/bbGraphics.h"
#include "engine/graphics/bbColours.h"
#include "engine/graphics/bbFonts.h"
#include "engine/widgets/bbWidget.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbTree.h"
#include "engine/user_input/bbInput.h"
#include "engine/2point5D/bbViewport.h"
#include "engine/2point5D/bbOverlays.h"
#include "engine/widgets/bbWidgetFunctions.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/dumbserver/bbDumbServer.h"
#include "engine/spells/bbSpell.h"

sfRenderWindow* testWindow;
bbWidgets* testWidgets;
bbMapCoords testGoalPoint;
bbDumbServer* testServer;
U64 testMapTime;

I32 hash(unsigned char *str, I32 n_bins);

int main (void){


    //trying to replicate a bug
    I32 magic_number = 256;
    bbPool_Handle testHandle;
    testHandle.u64 = 33333;



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

	bbFonts_new(&graphics.fonts, "./maps/map0/graphics/fonts.csv");

CLEARWINDOW(bbChartreuse);


CLEARWINDOW(bbGreen);
//bbHere();


    bbSpells spells;
    bbSpells_init(&spells);

	bbWidgets widgets;
	bbWidgets_init(&widgets);
	//testWidgets = &widgets;

	bbMouse mouse;

	bbMouse_Init(&mouse, &widgets, &graphics);

	bbMouseFunctions_init(&mouse.functions);
	bbMouseFunctions_populate(&mouse.functions);


	bbInput input;
	bbInput_new(&input,window, &mouse, &widgets);

CLEARWINDOW(bbTeal);

bbHere();
	bbWidget *layout;

    bbScreenPoints SP;
    SP.x = 600*8;
    SP.y = 50*8;

	//Does not need to be listed in constructor table
    bbWidget_newLayout(&layout, &graphics, &widgets, NULL);




CLEARWINDOW(bbBlue);

    bbViewport* viewport;
    bbViewport_new(&viewport, 456, 466);
    bbAssert(viewport != NULL, "bad bbViewport_new\n");

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

//does this crash?
    I32 hash_value = hash("SPELLSLOT", magic_number);

    void* testPtr;
    bbWidgetFunctions_getFunction(&testPtr, widgets.functions,
                                  WidgetConstructor, "SPELLSLOT");

	//bbWidgets widgets0;
	//bbWidgets_init(&widgets0);
    bbWidget* widget0;
    bbWidget* widget1;

	bbScreenPoints SP0;


    SP0.x = 58*8; SP0.y = 100*8;
    bbWidget_constructor(&widget1, &widgets, &graphics,
                         SP0, layout,"SPELLMENU");


    SP0.x = 97*8; SP0.y = 422*8;
    bbWidget_constructor(&widget0, &widgets, &graphics,
                        SP0, layout,"SPELLBAR");

    SP0.x = 11*8; SP0.y = 11*8;
    bbWidget_constructor(&widget1, &widgets, &graphics,
                         SP0, layout,"CURRENTSPELL");

	SP0.x = 497*8; SP0.y = 12*8;
	bbWidget_constructor(&widgets.dialog, &widgets, &graphics,
                         SP0, layout, "TEXTBOX");




	SP0.x = 497*8; SP0.y = 355*8;
	bbWidget_constructor(&widgets.prompt, &widgets, &graphics,
                         SP0, layout, "TEXTBOX");

	bbPool_Handle bounds;
	bounds.i32x2.x = 25;
	bounds.i32x2.y = 3;
	bbWidget_onCommand(widgets.prompt, &widgets, bbWC_setBounds, bounds);

	SP0.x = 497*8; SP0.y = 416*8;
	bbWidget_constructor(&widgets.command, &widgets, &graphics,
                         SP0, layout, "TEXTBOX");

	bounds.i32x2.x = 64;
	bounds.i32x2.y = 1;
	bbWidget_onCommand(widgets.command, &widgets, bbWC_setBounds, bounds);

	SP0.x = rand()%(720*8); SP0.y = rand()%(480*8);
	bbWidget_constructor(&widget0, &widgets, &graphics,
                         SP0, layout, "SPHERE");



	SP0.x = 500*8; SP0.y = 23*8;
	bbWidget_constructor(&widget0, &widgets, &graphics,
                         SP0, layout, "BUTTON");


    SP0.x = 500*8; SP0.y = 125*8;
    bbWidget_constructor(&widget0, &widgets, &graphics,
                         SP0, layout, "BOX");

    SP0.x = 500*8; SP0.y = 300*8;
    bbWidget_constructor(&widget0, &widgets, &graphics,
                         SP0, layout, "CARD");


////////////////////////////////////////////////////////
    CLEARWINDOW(bbRed);


	bbDumbServer_new(&testServer);



	int mapTime;
	for (mapTime = 0; ; mapTime++) {

testMapTime=mapTime;


		unsigned char ch = 'a' + rand()%26;
        bbPool_Handle handle;
        handle.u64 = ch;
		bbWidget_onCommand(widgets.dialog, &widgets, bbWC_putChar, handle);



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



		bbMouse_isOver(&mouse, &widgets);
		bbMouse_Update(&mouse, &widgets, &graphics);

		bbDumbServer_react(testServer, mapTime );

	if (mapTime % 50 == 0) bbPrintf("mapTime = %d\n", mapTime);
		cl.mapTime = mapTime;
        cl.GUI_time = mapTime;
        cl.graphics = &graphics;

        cl.target = viewport;


        bbOverlays_draw(overlays, &cl);


        cl.target = window;
        bbWidgets_draw(&widgets, &cl);

		bbMouse_Draw(&mouse, &widgets, &graphics, window);


		sfRenderWindow_display(window);
        bbViewport_clear(viewport);
        bbFlag flag = bbInput_poll(&input, window);
        if (flag == Break) break;
	}

    sfRenderWindow_destroy(window);

    bbDebug("We made it!\n");
    exit(EXIT_SUCCESS);


}

