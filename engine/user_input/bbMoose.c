
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

    Widgets->moose = moose;
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
    bbWidgets* Widgets = (bbWidgets*)widgets;

    bbTree* tree = Widgets->tree;
    bbVPool* pool = tree->pool;
    void* root;
    bbVPool_lookup(pool, &root, tree->root);
    return bbTree_ascendingMapVisible(tree, root, bbMoose_isOverFunc, NULL);
    return Success;
}

bbFlag bbMoose_Update(bbMoose* moose, void* widgets, bbGraphics* graphics)
{


    return Success;
}

bbFlag bbMoose_isOverFunc(bbTree* tree, void* node, void* cl)
{
    bbHere();
//TODO print pool element header
    return Continue;
}