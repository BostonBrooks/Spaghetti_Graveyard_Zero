#ifndef BBHOME_H
#define BBHOME_H

#include "engine/widgets/bbWidget.h"
#include "engine/userinterface/bbSpell.h"
#include "engine/userinterface/bbInput.h"
#include "engine/dummyserver/bbDummySender.h"
#include "engine/viewport/bbViewport.h"
#include "engine/viewport/bbDrawables.h"

typedef struct {
    bbSpells spells;
    bbWidgets widgets;
    bbMouse mouse;
    bbInput input;
    bbViewport* viewport;
    bbDummySender* server;
    sfRenderWindow* window;
    U64 mapTime;
    U64 UITime;
} bbPrivate;

typedef struct {
    //TODO add drawables and mapicons
    bbGraphics graphics;
} bbConstant;

typedef struct {

} bbShared;

typedef struct {
    bbPrivate private;
    bbConstant constant;
    bbShared shared;
} bbHome;

extern bbHome home;
#endif //BBHOME_H