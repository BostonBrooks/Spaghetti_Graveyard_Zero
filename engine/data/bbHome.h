#ifndef BBHOME_H
#define BBHOME_H

#include "engine/core/bbCore.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbSpell.h"
#include "engine/userinterface/bbInput.h"

#include "engine/viewport/bbViewport.h"
#include "engine/viewport/bbDrawables.h"
#include "engine/viewport/bbMapIcons.h"
#include "engine/viewport/bbUnits.h"
#include "engine/network/bbNetwork.h"
#include "engine/userinterface/bbUIApp.h"
#include "engine/viewport/bbViewportApp.h"

typedef enum
{
    PlayMode_play,
    PlayMode_pause,
    PlayMode_rewind
} bbPlaymodeType;

typedef struct {
    bbUIApp UI;
    //bbDummySender* server;
    bbNetwork network;
    U64 mapTime;

    //Old stuff being migrated to bbUIApp
    sfRenderWindow* window;
    //bbSpells spells;
    bbWidgets widgets;
    bbMouse mouse;
    bbInput input;
    //bbViewport* viewport;
    U64 UITime;
    bbViewportApp viewportApp;
} bbPrivate;

typedef struct {
    //TODO add drawables and mapicons
    bbGraphicsApp graphics;
    //bbDrawables* drawables;
    //bbMapIcons* mapIcons;
} bbConstant;

typedef struct {
    //bbUnits* units;
    bbCore* core;
    bbUnit* player;
    //bbMessages* messages;
    bbPlaymodeType playmode;
} bbShared;

typedef struct {
    bbPrivate private;
    bbConstant constant;
    bbShared shared;
} bbHome;

extern bbHome home;
#endif //BBHOME_H