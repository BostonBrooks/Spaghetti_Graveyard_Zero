
#include "engine/user_input/bbMoose.h"


bbFlag bbMoose_Init(bbMoose* moose, bbWidgets* widgets, bbGraphics* graphics)
{
    moose->position.x = 720*4;
    moose->position.y = 480*4;
    moose->leftDown = false;
    moose->rightDown = false;
    moose->leftChanged = false;
    moose->rightChanged = false;
    moose->wasOver = widgets->pool->null;
    moose->isOver = widgets->pool->null;
    moose->selected = widgets->pool->null;

    bbMooseFunctions_populate(moose);
    return Success;
}