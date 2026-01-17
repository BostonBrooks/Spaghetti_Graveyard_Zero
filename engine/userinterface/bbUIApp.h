/** This class provides and interface from other systems to things that are drawn on the screen and user inputs
Everything in this module can be considered private data and not shared over the network
**/
#ifndef BBUIAPP_H
#define BBUIAPP_H
#include "bbInput.h"
#include "bbSpell.h"

#include "engine/logic/bbFlag.h"
#include "engine/viewport/bbViewport.h"

//If network not connected, open network settings
typedef enum
{
    NetConnected,
    NetConnecting,
    NetDisconnected,
    NetDisconnecting
} bbNetState;

typedef enum
{
    LayerGame,
    LayerSpellMenu,
    LayerNetworkMenu,
} bbLayerType;


typedef struct
{
    sfRenderWindow* window;
    bbWidgets widgets;
    bbMouse mouse;
    bbInput input;
    //TODO move to bbViewportApp
   // bbViewport* viewport;
    bbSpells spells;

    bbNetState netState;
    bbLayerType activeLayer;

    //UI time increments one tick per frame, cant be paused or rewound like game time
    U64 UITime;


    //little bit of data that aren't part of a module
    sfTexture* SplashTexture;
    sfSprite* SplashSprite;
} bbUIApp;

bbFlag bbUIApp_newWindow(bbUIApp* app);
bbFlag bbUIApp_init(bbUIApp* app);


bbFlag bbUIApp_draw(bbUIApp* app);

bbFlag bbUIApp_setNetState(bbUIApp* app, bbNetState netState);
bbFlag bbUIApp_setActiveLayer(bbUIApp* app, bbLayerType layerType);

bbFlag bbUIApp_setPrompt(bbUIApp, char* string);
bbFlag bbUIApp_putDialog(bbUIApp, char* string);
#endif // BBUIAPP_H