
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

    bbMoose_isOver_cl cl;
    cl.widgets = Widgets;

    bbTree* tree = Widgets->tree;
    bbVPool* pool = tree->pool;
    void* root;
    bbVPool_lookup(pool, &root, tree->root);
    return bbTree_ascendingMapVisible(tree, root, bbMoose_isOverFunc, &cl);
    return Success;
}

bbFlag bbMoose_Update(bbMoose* moose, void* widgets, bbGraphics* graphics)
{


    return Success;
}

bbFlag bbMoose_isOverFunc(bbTree* tree, void* node, void* cl)
{
    bbWidget* widget = (bbWidget*)node;
    bbMoose_isOver_cl* closure = (bbMoose_isOver_cl*)cl;
    bbWidgets* widgets = closure->widgets;
    bbMoose* moose = widgets->moose;

    I32 funcInt = widget->mtable.isOver;

    bbMoose_IsOver* func = moose->functions.IsOver[funcInt];

    return func(moose, widgets, widget);

}

bbFlag bbMoose_Draw(bbMoose* moose, void* widgets, bbGraphics* graphics, sfRenderWindow* window)
{
    bbWidgets* Widgets = (bbWidgets*)widgets;
    sfVector2f pos = bbScreenPoints_getV2f(moose->position);
    bbPool_Handle widgetHandle = moose->isOver;
    bbWidget* widget;
    bbVPool_lookup(Widgets->pool, (void**)&widget, widgetHandle);
    I32 spriteInt = widget->mtable.MouseIcon;
    bbDebug("spriteInt=%d\n", spriteInt);
    sfSprite* sprite = graphics->sprites->sprites[spriteInt];
    sfSprite_setPosition(sprite, pos);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    return Success;
}