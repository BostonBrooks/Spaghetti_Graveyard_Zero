#include <stdio.h>
#include "engine/includes/csfml.h"
#include "engine/graphics/bbGraphics.h"
#include "engine/widgets/bbWidget.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbTree.h"

sfRenderWindow* testWindow;

int main (void){
	printf("Hello World!\n");
	sfVideoMode mode;
	mode.height = 480;
	mode.width = 720;
	mode.bitsPerPixel = 32;
	sfRenderWindow* window = sfRenderWindow_create(mode, "early demo", sfResize | sfClose, NULL);
    testWindow = window;

	bbGraphics graphics;
    I32 flag;
	flag = bbTextures_new(&graphics.textures, "./maps/map0/textures.csv");

    bbAssert(flag == Success, "Bad flag from bbTextures_new");

/* some debug code
    bbPool_Handle tempHandle;
    bbDictionary_lookup(graphics.textures->dictionary, "VIEWPORT_720", &tempHandle);
    bbDebug("VIEWPORT_720 is at %llu\n", tempHandle.u64);
*/

//bbHere()
bbSprites_new(&graphics.sprites, graphics.textures, ""
                                                            "./maps/map0/sprites.csv",1,1,1);
//bbHere()

	bbDrawfunctions_new(&graphics.drawfunctions);

//bbHere()
	bbAnimations_new(&graphics.animations, graphics.sprites, graphics.drawfunctions, "./maps/map0/animations.csv");

//bbHere()

	bbWidgets widgets;
	bbWidgets_init(&widgets);
//bbHere()


	bbWidget* layout;
	bbWidget_layoutNew(&layout, &graphics, &widgets, NULL);

//bbHere()

	bbWidget* viewport;
	bbWidget_viewportNew(&viewport, &graphics, &widgets, layout);

/*test sprites: we get here
bbHere()
    int num_sprites = graphics.sprites->numSprites;

    sfRenderWindow* window2;
    window2 = sfRenderWindow_create(mode, "early demo", sfResize | sfClose,NULL);

    for (int i = 0; i < num_sprites; i++){
        bbPrintf("XXXXX sprites[%d] XXXXX\n", i);
        sfSprite* sprite = graphics.sprites->sprites[i];

        sfRenderWindow_drawSprite(window2, sprite, NULL);
        sfRenderWindow_display(window2);
        sfTime time = sfSeconds(0.1);
        sfSleep(time);
    }
*/
bbHere() //sometimes we get here

	targets cl;
	cl.target = window;
	cl.graphics = &graphics;

	descending_map(widgets.tree, layout, drawFunc, &cl);
//bbHere() //sometimes we get here
	sfRenderWindow_display(window);
//bbHere()

	sfTime time = sfSeconds(5);
	sfSleep(time);
	sfRenderWindow_destroy(window);

    bbDebug("We made it!\n");
	exit(EXIT_SUCCESS);
}