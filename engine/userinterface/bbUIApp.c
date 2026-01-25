

#include "engine/userinterface/bbUIApp.h"

#include "engine/data/bbHome.h"

bbFlag bbUIApp_newWindow(bbUIApp* app)
{
    app->SplashTexture = sfTexture_createFromFile("./graphics/Splash.png", NULL);
    app->SplashSprite = sfSprite_create();
    sfSprite_setTexture(app->SplashSprite, app->SplashTexture, sfTrue);


    sfVideoMode mode;
    mode.width = 720;
    mode.height = 480;
    mode.bitsPerPixel = 32;

    sfRenderWindow* window = sfRenderWindow_create(mode, "early demo", sfResize | sfClose, NULL);
    sfRenderWindow_drawSprite(window, app->SplashSprite, NULL);
    sfRenderWindow_display(window);
    //sfRenderWindow_setFramerateLimit(window, 60);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    app->window = window;

    return Success;
}

bbFlag bbUIAPP_initSpells(bbUIApp* app)
{
    //bbSpells spells;
    bbSpells_init(&app->spells);

    bbSpell* null_spell;
    bbSpell_new(&null_spell, &app->spells, "NULL");
    bbSpell* spell1;
    bbSpell_new(&spell1, &app->spells, "SPELL1");

    bbSpell* spellN;
    bbSpell_new(&spellN, &app->spells, "SPELL2");
    bbSpell_new(&spellN, &app->spells, "SPELL3");

    return Success;
}

bbFlag bbUIApp_spawnWidgets(bbUIApp* app)
{
	bbHere()
    bbWidget *layout;
    bbScreenPoints SP;
    SP.x = 600*SCREEN_PPP;
    SP.y = 50*SCREEN_PPP;

    bbWidget_newLayout(&layout, &home.constant.graphics, &app->widgets, NULL);
    bbWidget* viewportWidget;
    //Does not need to be listed in constructor table


	bbWidget_newViewport(&viewportWidget, &home.constant.graphics, &app->widgets, layout,
						 &home.private.viewportApp.viewport);


    bbWidget* widget0;
    bbWidget* widget1;

    bbScreenPoints SP0;



	bbPool_Handle handle;
/*

    SP0.x = 497*SCREEN_PPP; SP0.y = 12*SCREEN_PPP;
    bbWidget_constructor(&app->widgets.dialog, &app->widgets, &home.constant.graphics,
                         SP0, layout, "TEXTBOX");


    bbVPool_reverseLookup(app->widgets.pool, app->widgets.dialog, &handle);
    bbDictionary_add(app->widgets.dict, "DIALOG", handle);

    bbPool_Handle bounds;
    bounds.i32x2.x = 200*SCREEN_PPP;
    bounds.i32x2.y = 322*SCREEN_PPP;
    bbWidget_onCommand(app->widgets.dialog, &app->widgets, bbWC_setDimensions, bounds);

    SP0.x = 497*SCREEN_PPP; SP0.y = 355*SCREEN_PPP;
    bbWidget_constructor(&app->widgets.prompt, &app->widgets, &home.constant.graphics,
                         SP0, layout, "TEXTBOX");
    bbVPool_reverseLookup(app->widgets.pool, app->widgets.prompt, &handle);
    bbDictionary_add(app->widgets.dict, "PROMPT", handle);


	bounds.i32x2.x = 200*SCREEN_PPP;
	bounds.i32x2.y = 45*SCREEN_PPP;
	bbWidget_onCommand(app->widgets.prompt, &app->widgets, bbWC_setDimensions, bounds);

	SP0.x = 497*SCREEN_PPP; SP0.y = 416*SCREEN_PPP;
	bbWidget_constructor(&app->widgets.command, &app->widgets, &home.constant.graphics,
                         SP0, layout, "TEXTBOX");

	bbVPool_reverseLookup(app->widgets.pool, app->widgets.command, &handle);
	bbDictionary_add(app->widgets.dict, "COMMAND", handle);

	app->widgets.textbox = app->widgets.command;
	bounds.i32x2.x = 200 * SCREEN_PPP;
	bounds.i32x2.y = 45*SCREEN_PPP;
	bbWidget_onCommand(app->widgets.command, &app->widgets, bbWC_setDimensions, bounds);
	bounds.i32x2.x = 64;
	bounds.i32x2.y = 1;
	bbWidget_onCommand(app->widgets.command, &app->widgets, bbWC_setBounds, bounds);

*/
	/*
	SP0.x = 58*SCREEN_PPP; SP0.y = 100*SCREEN_PPP;
	bbWidget_constructor(&widget1, &app->widgets, &home.constant.graphics,
						 SP0, layout,"CONNECTMENU");*/



	bbVPool_reverseLookup(app->widgets.pool, layout, &handle);
	bbDictionary_add(app->widgets.dict, "LAYOUT", handle);

	bbWidget_constructor2(&widget0,
			 &app->widgets,
			 "GAME",
			 "LAYOUT",
			 "GAME2",
			 0,
			 0);
/*
	SP0.x = 58*SCREEN_PPP; SP0.y = 100*SCREEN_PPP;
	bbWidget_constructor(&widget1, &app->widgets, &home.constant.graphics,
						 SP0, layout,"SPELLMENU");
*/
	bbWidget_constructor2(&widget0,
		 &app->widgets,
		 "SPELLMENU",
		 "LAYOUT",
		 "SPELLMENU",
		 58*SCREEN_PPP,
		 100*SCREEN_PPP);

/*
	SP0.x = 97*SCREEN_PPP; SP0.y = 422*SCREEN_PPP;
	bbWidget_constructor(&widget0, &app->widgets, &home.constant.graphics,
						SP0, layout,"SPELLBAR");
*/
	bbWidget_constructor2(&widget0,
			 &app->widgets,
			 "SPELLBAR",
			 "LAYOUT",
			 "SPELLBAR2",
			 97*SCREEN_PPP,
			 422*SCREEN_PPP);

	bbWidget_constructor2(&widget0,
				 &app->widgets,
				 "CONNECTMENU",
				 "LAYOUT",
				 "CONNECTMENU2",
				 58*SCREEN_PPP,
				 100*SCREEN_PPP);

	bbWidget_constructor2(&widget0,
					 &app->widgets,
					 "TOPLEFT",
					 "LAYOUT",
					 "TOPLEFT2",
					 11*SCREEN_PPP,
					 11*SCREEN_PPP);

	bbWidget_constructor2(&widget0,
						 &app->widgets,
						 "BUTTON",
						 "LAYOUT",
						 "BUTTON2",
						 500*SCREEN_PPP,
						 23*SCREEN_PPP);

	bbWidget_constructor2(&widget0,
							 &app->widgets,
							 "SPHERE",
							 "LAYOUT",
							 "SPHERE2",
							 rand()%(720*SCREEN_PPP),
							 rand()%(480*SCREEN_PPP));

	bbWidget_constructor2(&widget0,
							 &app->widgets,
							 "CARD",
							 "LAYOUT",
							 "CARD2",
							 620*SCREEN_PPP,
							 100*SCREEN_PPP);

	bbWidget_constructor2(&widget0,
						 &app->widgets,
						 "BOX",
						 "LAYOUT",
						 "BOX",
						 500*SCREEN_PPP,
						 125*SCREEN_PPP);

	//Only used when testing animations
	//SP0.x = 0; SP0.y = 0;
	//bbWidget_constructor(&widget0, &app->widgets, &home.constant.graphics,
	//					 SP0, layout, "ANIMATIONTEST");

	return Success;
}

bbFlag bbUIApp_init(bbUIApp* app)
{
    bbUIAPP_initSpells(app);

    bbWidgets_init(&app->widgets);
    bbMouse_Init(&app->mouse, &app->widgets, &home.constant.graphics);
    bbMouseFunctions_init(&app->mouse.functions);
    bbMouseFunctions_populate(&app->mouse.functions);
    bbInput_new(&app->input,app->window, &app->mouse, &app->widgets);
	bbHere()
	bbUIApp_spawnWidgets(app);

	//TODO set active spell
	//bbSpell_setActive(spell1, &app->spells, home.private.server, 0);
}


bbFlag bbUIApp_draw(bbUIApp* app)
{
	drawFuncClosure cl;
	cl.mapTime = home.private.mapTime;
	cl.GUI_time = home.private.mapTime;
	cl.graphics = &home.constant.graphics;
	cl.target = &home.private.viewportApp.viewport;

	bbDrawablesPlus_draw( &cl, 0, 0, 12, 12);
	bbAvoidables_draw(home.private.viewportApp.avoidables, &cl, 0, 0, 12, 12);
	cl.target = app->window;
	bbWidgets_draw(&app->widgets, &cl);
	bbMouse_Draw(&app->mouse, &app->widgets, &home.constant.graphics, app->window);
	sfRenderWindow_display(app->window);
	bbViewport_clear(&home.private.viewportApp.viewport);
}