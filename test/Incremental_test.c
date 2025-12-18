#include <stdio.h>
#include <time.h>
#include "engine/includes/CSFML.h"
#include "engine/graphics/bbGraphics.h"
#include "engine/graphics/bbColours.h"
#include "engine/graphics/bbFonts.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbTree.h"
#include "engine/userinterface/bbInput.h"
#include "engine/viewport/bbViewport.h"
#include "engine/userinterface/bbWidgetFunctions.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/dummyserver/bbDummySender.h"
#include "engine/dummyserver/bbDummyReceiver.h"
#include "engine/userinterface/bbSpell.h"
#include "engine/data/bbHome.h"
#include "engine/viewport/bbDrawables.h"
#include "engine/viewport/bbMapIcons.h"
#include "engine/avoidance/bbAvoidables.h"
#include "engine/viewport/bbUnits.h"


bbWidgets* testWidgets;
bbMapCoords testGoalPoint;

I32 hash(unsigned char *str, I32 n_bins);

bbHome home;

int main (void){
    srand(time(NULL));

    //trying to replicate a bug
    I32 magic_number = 256;
    bbPool_Handle testHandle;
    testHandle.u64 = 33333;



    testGoalPoint.i = 10000;
    testGoalPoint.j = 10000;
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

	home.private.window = window;
CLEARWINDOW(bbRed);

	//bbGraphics graphics;
	bbTextures_new(&home.constant.graphics.textures,
                   "./maps/map0/graphics/textures.csv");



	//bbDictionary_print(graphics.textures->dictionary);
//bbHere();
	bbSprites_new(&home.constant.graphics.sprites, home.constant.graphics
    .textures,
                  "./maps/map0/graphics/sprites.csv",1,1,1);

    //bbDictionary_print(graphics.sprites->dictionary);

CLEARWINDOW(bbRedOrange);

	bbDrawfunctions_new(&home.constant.graphics.drawfunctions);


CLEARWINDOW(bbOrange);

	void* memtest = malloc(sizeof(char) * 1028);
	bbAnimations_new(&home.constant.graphics.animations, home.constant
    .graphics.sprites, home.constant.graphics
            .drawfunctions, "./maps/map0/graphics/animations.csv");

	//bbDictionary_print(graphics.animations->dictionary);
CLEARWINDOW(bbYellowOrange);

	bbCompositions_new(&home.constant.graphics.compositions, home.constant
    .graphics.sprites, home.constant.graphics
            .animations, home.constant.graphics.drawfunctions,
            "./maps/map0/graphics/compositions.csv");
	//bbDictionary_print(graphics.compositions->dictionary);

CLEARWINDOW(bbYellow);

	bbFonts_new(&home.constant.graphics.fonts, "./maps/map0/graphics/fonts.csv");

CLEARWINDOW(bbChartreuse);


CLEARWINDOW(bbGreen);
//bbHere();


	bbDummySender_new(&home.private.server);


    //bbSpells spells;
    bbSpells_init(&home.private.spells);

    bbSpell* null_spell;
    bbSpell_new(&null_spell, &home.private.spells, "NULL");
	bbSpell* spell1;
    bbSpell_new(&spell1, &home.private.spells, "SPELL1");

    bbSpell* spellN;
    bbSpell_new(&spellN, &home.private.spells, "SPELL2");
    bbSpell_new(&spellN, &home.private.spells, "SPELL3");

	//bbWidgets widgets;
	bbWidgets_init(&home.private.widgets);
	//testWidgets = &widgets;

	//bbMouse mouse;

	bbMouse_Init(&home.private.mouse, &home.private.widgets, &home.constant
    .graphics);

	bbMouseFunctions_init(&home.private.mouse.functions);
	bbMouseFunctions_populate(&home.private.mouse.functions);


	bbInput input;
	bbInput_new(&input,window, &home.private.mouse, &home.private.widgets);

CLEARWINDOW(bbTeal);

bbHere();
	bbWidget *layout;

    bbScreenPoints SP;
    SP.x = 600*8;
    SP.y = 50*8;

	//Does not need to be listed in constructor table
    bbWidget_newLayout(&layout, &home.constant.graphics, &home.private.widgets, NULL);




CLEARWINDOW(bbBlue);

    //bbViewport* viewport;
    bbViewport_new(&home.private.viewport, 456, 466);
    bbAssert(home.private.viewport != NULL, "bad bbViewport_new\n");

    CLEARWINDOW(bbViolet);





//bbHere();
	bbWidget* viewportWidget;
	//Does not need to be listed in constructor table
    bbWidget_newViewport(&viewportWidget, &home.constant.graphics, &home.private.widgets, layout,
                         home.private.viewport);

CLEARWINDOW(bbPurple);

//    bbWidgetFunctions_getFunction((void**)&function0,
//                                  testWidgets->functions,
//                                  WidgetConstructor, "Sphere");

//typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
//                                     bbWidgets* widgets, bbScreenPoints
//                                     screen_coords, bbWidget* parent);





    drawFuncClosure cl;


CLEARWINDOW(bbMagenta);


    bbHere();

//does this crash?
    I32 hash_value = hash("SPELLSLOT", magic_number);

    void* testPtr;
    bbWidgetFunctions_getFunction(&testPtr, home.private.widgets.functions,
                                  WidgetConstructor, "SPELLSLOT");

	//bbWidgets widgets0;
	//bbWidgets_init(&widgets0);
    bbWidget* widget0;
    bbWidget* widget1;

	bbScreenPoints SP0;


    SP0.x = 58*8; SP0.y = 100*8;
    bbWidget_constructor(&widget1, &home.private.widgets, &home.constant.graphics,
                         SP0, layout,"SPELLMENU");


    SP0.x = 97*8; SP0.y = 422*8;
    bbWidget_constructor(&widget0, &home.private.widgets, &home.constant.graphics,
                        SP0, layout,"SPELLBAR");



	SP0.x = 497*8; SP0.y = 12*8;
	bbWidget_constructor(&home.private.widgets.dialog, &home.private.widgets, &home.constant.graphics,
                         SP0, layout, "TEXTBOX");


	bbPool_Handle handle;
	bbVPool_reverseLookup(home.private.widgets.pool, home.private.widgets.dialog, &handle);
	bbDictionary_add(home.private.widgets.dict, "DIALOG", handle);

	SP0.x = 497*8; SP0.y = 355*8;
	bbWidget_constructor(&home.private.widgets.prompt, &home.private.widgets, &home.constant.graphics,
                         SP0, layout, "TEXTBOX");
	bbVPool_reverseLookup(home.private.widgets.pool, home.private.widgets.prompt, &handle);
	bbDictionary_add(home.private.widgets.dict, "PROMPT", handle);

	bbPool_Handle bounds;
	bounds.i32x2.x = 200*8;
	bounds.i32x2.y = 45*8;
	bbWidget_onCommand(home.private.widgets.prompt, &home.private.widgets, bbWC_setDimensions, bounds);

	SP0.x = 497*8; SP0.y = 416*8;
	bbWidget_constructor(&home.private.widgets.command, &home.private.widgets, &home.constant.graphics,
                         SP0, layout, "TEXTBOX");

	bbVPool_reverseLookup(home.private.widgets.pool, home.private.widgets.command, &handle);
	bbDictionary_add(home.private.widgets.dict, "COMMAND", handle);

	home.private.widgets.textbox = home.private.widgets.command;
	bounds.i32x2.x = 200 * 8;
	bounds.i32x2.y = 45*8;
	bbWidget_onCommand(home.private.widgets.command, &home.private.widgets, bbWC_setDimensions, bounds);
	bounds.i32x2.x = 64;
	bounds.i32x2.y = 1;
	bbWidget_onCommand(home.private.widgets.command, &home.private.widgets, bbWC_setBounds, bounds);


	SP0.x = 58*8; SP0.y = 100*8;
	bbWidget_constructor(&widget1, &home.private.widgets, &home.constant.graphics,
						 SP0, layout,"CONNECTMENU");

	SP0.x = 11*8; SP0.y = 11*8;
	bbWidget_constructor(&widget1, &home.private.widgets, &home.constant.graphics,
						 SP0, layout,"TOPLEFT");

	SP0.x = 11*8; SP0.y = 11*8;
	bbWidget_constructor(&widget0, &home.private.widgets, &home.constant.graphics,
						 SP0, widget1,"CURRENTSPELL");

	SP0.x = 46*8; SP0.y = 11*8;
	bbWidget_constructor(&widget0, &home.private.widgets, &home.constant.graphics,
						 SP0, widget1, "CONNECTICON");

	SP0.x = rand()%(720*8); SP0.y = rand()%(480*8);
	bbWidget_constructor(&widget0, &home.private.widgets, &home.constant.graphics,
                         SP0, layout, "SPHERE");





	SP0.x = 500*8; SP0.y = 23*8;
	bbWidget_constructor(&widget0, &home.private.widgets, &home.constant.graphics,
                         SP0, layout, "BUTTON");


    SP0.x = 500*8; SP0.y = 125*8;
    bbWidget_constructor(&widget0, &home.private.widgets, &home.constant.graphics,
                         SP0, layout, "BOX");

    SP0.x = 570*8; SP0.y = 125*8;
    bbWidget_constructor(&widget0, &home.private.widgets, &home.constant.graphics,
                         SP0, layout, "CARD");


////////////////////////////////////////////////////////
    CLEARWINDOW(bbRed);


    bbSpell_setActive(spell1, &home.private.spells, home.private.server, 0);




    bbAvoidables* avoidables;
    bbDrawables_new((void**)&home.constant.drawables,  12, 12);
    bbMapIcons_new((void**) &home.constant.mapIcons,  12, 12);
    bbUnits_new((void**)&home.shared.units, 12, 12);
    bbAvoidables_new((void**)&avoidables, 12, 12);

    cl.mapTime = home.private.mapTime;
    cl.GUI_time = home.private.mapTime;
    cl.graphics = &home.constant.graphics;
    cl.target = home.private.viewport;

    //bbDrawables_draw(drawables, &cl,0, 0,3, 3);

    for (I32 i = 0; i<24;i++){
        for (I32 j=0; j<24;j++){

            bbMapCoords MC;
            MC.i = i * (POINTS_PER_SQUARE / 2);
            MC.j = j * (POINTS_PER_SQUARE / 2);
            MC.k = 0;

            MC.i += rand()%(100 * POINTS_PER_PIXEL);
            MC.j += rand()%(100 * POINTS_PER_PIXEL);

            bbDrawable* drawable;
            bbDrawable_newTree(&drawable, home.constant.drawables, &home.constant.graphics,
                               MC);
            bbMapIcon* mapicon;
            bbMapIcon_new(&mapicon, home.constant.mapIcons,&home.constant.graphics, MC);
            bbAvoidable* avoidable;
            bbAvoidable_new(&avoidable, avoidables, MC, 160);


        }
    }

    for (I32 i = 0; i<12;i++) {
        for (I32 j = 0; j < 12; j++) {
            bbMapCoords MC;

            MC.i = i * (POINTS_PER_SQUARE);
            MC.j = j * (POINTS_PER_SQUARE);
            MC.k = 0;

            MC.i += rand()%(100 * POINTS_PER_PIXEL);
            MC.j += rand()%(100 * POINTS_PER_PIXEL);

            bbUnit* unit;
            bbUnit_new(&unit,home.shared.units, &home.constant.graphics,MC);
        }
    }

    bbUnit* player;
    bbUnit_newCat(&player, home.shared.units, &home.constant.graphics,
               home.private.viewport->viewpoint);

    CLEARWINDOW(bbRedOrange);

	for (home.private.mapTime = 0; ; home.private.mapTime++) {

/*
		unsigned char ch = 'a' + rand()%26;
        bbPool_Handle handle;
        handle.u64 = ch;
		bbWidget_onCommand(home.private.widgets.dialog, &home.private.widgets, bbWC_putChar, handle);

*/

        bbDummySender_textMessage(home.private.server, "TEST", home.private
        .mapTime);

        bbMapCoords difference;
        difference.i = testGoalPoint.i - home.private.viewport->viewpoint.i;
        difference.j = testGoalPoint.j - home.private.viewport->viewpoint.j;
        difference.k = 0;

        float speed = 8;

        float distance = sqrt(difference.i*difference.i
                + difference.j*difference.j);

        if (distance <= speed){
            home.private.viewport->viewpoint = testGoalPoint;
        } else {
            home.private.viewport->viewpoint.i += difference.i * speed / distance;
            home.private.viewport->viewpoint.j += difference.j * speed / distance;
        }

        bbUnit_setLocation((bbDrawable*)player, home.shared.units,
                               home.private.viewport->viewpoint);

		bbMouse_isOver(&home.private.mouse, &home.private.widgets);
		bbMouse_Update(&home.private.mouse, &home.private.widgets, &home.constant.graphics);

		bbDummyReceiver_receive(home.private.server, home.private.mapTime );

	if (home.private.mapTime % 50 == 0) bbPrintf("mapTime = %d\n", home.private.mapTime);
		cl.mapTime = home.private.mapTime;
        cl.GUI_time = home.private.mapTime;
        cl.graphics = &home.constant.graphics;

        cl.target = home.private.viewport;

//TODO change bbDrawables_draw(drawables, &cl, 0, 0, 12, 12); signature back
        bbDrawablesPlus_draw( &cl, 0, 0, 12, 12);
bbAvoidables_draw(avoidables, &cl, 0, 0, 12, 12);




        cl.target = window;
        bbWidgets_draw(&home.private.widgets, &cl);

		bbMouse_Draw(&home.private.mouse, &home.private.widgets, &home.constant.graphics, window);


		sfRenderWindow_display(window);
        bbViewport_clear(home.private.viewport);
        bbFlag flag = bbInput_poll(&input, window);
        if (flag == Break) break;
	}

    sfRenderWindow_destroy(window);

    bbDebug("We made it!\n");
    exit(EXIT_SUCCESS);


}

