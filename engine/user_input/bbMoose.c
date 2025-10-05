
#include "engine/user_input/bbMoose.h"

#include "engine/widgets/bbWidget.h"


bbFlag bbMoose_Init(bbMoose* moose, void* widgets, bbGraphics* graphics)
{
    bbWidgets* Widgets = (bbWidgets*)widgets;
    moose->position.x = 720*4;
    moose->position.y = 480*4;
    moose->leftDown = false;
    moose->rightDown = false;
    moose->leftChanged = false;
    moose->rightChanged = false;
    moose->wasOver = Widgets->pool->null;
    moose->isOver = Widgets->pool->null;
    moose->selected = Widgets->pool->null;

    return Success;
}

bbFlag bbMoose_Event(bbMoose* moose, sfEvent* event)
{
    switch (event->type){
    case sfEvtMouseMoved:
        moose->position = pixel_getScreenPoints(event->mouseMove.x,
                                                event->mouseMove.y);

        break;
    default:{
            bbDebug("input not recognised\n");
    }
    }
    return Success;
}

bbFlag bbMoose_isOver(bbMoose* moose, void* widgets)
{

    bbAssert(0==1, "we made it\n");
    return Success;
}

bbFlag bbMoose_Update(bbMoose* moose, void* widgets, bbGraphics* graphics)
{
    bbWidgets* Widgets = (bbWidgets*)widgets;

    bbMoose_isOver(moose, widgets);

    return Success;
}