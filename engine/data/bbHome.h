#ifndef BBHOME_H
#define BBHOME_H

#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbSpell.h"
#include "engine/userinterface/bbInput.h"
#include "engine/dummyserver/bbDummySender.h"
#include "engine/viewport/bbViewport.h"
#include "engine/viewport/bbDrawables.h"
#include "engine/viewport/bbMapIcons.h"
#include "engine/viewport/bbUnits.h"
#include "engine/core/bbCore.h"
#include "engine/core/bbMessages.h"
#include "engine/network/bbNetwork.h"

typedef struct {
    bbSpells spells;
    bbWidgets widgets;
    bbMouse mouse;
    bbInput input;
    bbViewport* viewport;
    bbDummySender* server;
    sfRenderWindow* window;
    bbNetwork network;
    U64 mapTime;
    U64 UITime;
} bbPrivate;

typedef struct {
    //TODO add drawables and mapicons
    bbGraphics graphics;
    bbDrawables* drawables;
    bbMapIcons* mapIcons;
} bbConstant;

typedef struct {
    bbUnits* units;
    bbCore* core;
    //bbMessages* messages;

} bbShared;

typedef struct {
    bbPrivate private;
    bbConstant constant;
    bbShared shared;
} bbHome;

extern bbHome home;
#endif //BBHOME_H