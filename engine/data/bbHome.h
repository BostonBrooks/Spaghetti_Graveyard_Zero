#include "engine/widgets/bbWidget.h"
#include "engine/spells/bbSpell.h"
#include "engine/user_input/bbInput.h"
#include "engine/2point5D/bbOverlays.h"

typedef struct {
    bbSpells spells;
    bbWidgets widgets;
    bbMouse mouse;
    bbInput input;
    bbViewport* viewport;
    bbDumbServer server;

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