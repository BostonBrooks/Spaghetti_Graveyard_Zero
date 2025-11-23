#ifndef BBHOME_H
#define BBHOME_H

#include "engine/widgets/bbWidget.h"
#include "engine/spells/bbSpell.h"
#include "engine/user_input/bbInput.h"
#include "engine/2point5D/bbOverlays.h"
#include "engine/dummyserver/bbDummySender.h"

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
    bbOverlays* overlays;
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