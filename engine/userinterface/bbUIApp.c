

#include "engine/userinterface/bbUIApp.h"
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
    sfRenderWindow_setFramerateLimit(window, 60);
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

bbFlag bbUIApp_init(bbUIApp* app)
{
    bbUIAPP_initSpells(app);
}