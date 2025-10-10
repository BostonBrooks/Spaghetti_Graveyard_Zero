
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
    sfMouseButton button;
    switch (event->type){
    case sfEvtMouseMoved:
        moose->position = pixel_getScreenPoints(event->mouseMove.x,
                                                event->mouseMove.y);

        break;
        case sfEvtMouseButtonPressed:
            button = event->mouseButton.button;
            moose->position = pixel_getScreenPoints(event->mouseButton.x,event->mouseButton.y);
            if (button == sfMouseLeft)
            {
                moose->leftChanged = true;
                moose->leftDown = true;
            } else if (button == sfMouseRight)
            {
                moose->rightChanged = true;
                moose->rightDown = true;
            }
            break;
        case sfEvtMouseButtonReleased:

            button = event->mouseButton.button;
            moose->position = pixel_getScreenPoints(event->mouseButton.x,event->mouseButton.y);
            if (button == sfMouseLeft)
            {
                moose->leftChanged = true;
                moose->leftDown = false;
            } else if (button == sfMouseRight)
            {
                moose->rightChanged = true;
                moose->rightDown = false;
            }
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
    bbWidgets* Widgets = widgets;
    bbVPool* pool = Widgets->pool;
    if(!bbVPool_handleIsEqual(pool, moose->wasOver, pool->null)){
        bbWidget* toLeave;
        bbWidget* toEnter;

        bbVPool_lookup(pool, (void**)&toLeave, moose->wasOver);
        bbVPool_lookup(pool, (void**)&toEnter, moose->isOver);
        bbMoose_LeaveWidget(moose, widgets, toLeave, graphics);
        bbMoose_EnterWidget(moose, widgets, toEnter, graphics);

        moose->wasOver = pool->null;

    }
    if (moose->leftDown && moose->leftChanged){

        bbWidget* widget;



        bbVPool_lookup(pool, (void**)&widget, moose->isOver);
        bbMoose_LeftDownWidget (moose, widgets, widget, graphics);
    } else if (!moose->leftDown && moose->leftChanged) {
        bbWidget* widget;
        if(!bbVPool_handleIsEqual(pool, moose->selected, pool->null)) {
            bbVPool_lookup(pool, (void **) &widget, moose->selected);
            bbMoose_LeftUpWidget(moose, widgets, widget, graphics);
        }
    }


    return Success;
}

bbFlag bbMoose_isOverFunc(bbTree* tree, void* node, void* cl)
{
    bbWidget* widget = (bbWidget*)node;
    bbMoose_isOver_cl* closure = (bbMoose_isOver_cl*)cl;
    bbWidgets* widgets = closure->widgets;
    bbMoose* moose = widgets->moose;

    I32 funcInt = widget->mtable.isOver;

    if (funcInt == -1) return Continue;

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
    sfSprite* sprite = graphics->sprites->sprites[spriteInt];
    sfSprite_setPosition(sprite, pos);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    return Success;
}

bbFlag bbMoose_EnterWidget(void* moose, void* widgets, void* widget, void*
graphics)
{
    bbWidget* Widget = widget;
    bbMoose* Moose = moose;
    I32 funcInt = Widget->mtable.Enter;

    if (funcInt == -1) return Success;

    bbDebug("funcInt = %d\n", funcInt);
    bbMoose_Leave* func = Moose->functions.Enter[funcInt];

    return func(moose, widgets, widget, graphics);
}

bbFlag bbMoose_LeaveWidget(void* moose, void* widgets, void* widget, void*
graphics)
{
    bbWidget* Widget = widget;
    bbMoose* Moose = moose;
    I32 funcInt = Widget->mtable.Leave;

    if (funcInt == -1) return Success;

    bbDebug("funcInt = %d\n", funcInt);
    bbMoose_Leave* func = Moose->functions.Leave[funcInt];

    return func(moose, widgets, widget, graphics);
}

bbFlag bbMoose_LeftDownWidget(void* moose, void* widgets, void* widget,
                                void* graphics)
{
    bbWidget* Widget = widget;
    bbMoose* Moose = moose;
    I32 funcInt = Widget->mtable.LeftDown;

    if (funcInt == -1) return Success;

    bbDebug("funcInt = %d\n", funcInt);
    bbMoose_Leave* func = Moose->functions.LeftDown[funcInt];

    return func(moose, widgets, widget, graphics);
}
bbFlag bbMoose_LeftUpWidget(void* moose, void* widgets, void* widget,
                                  void* graphics)
{
    bbWidget* Widget = widget;
    bbMoose* Moose = moose;
    I32 funcInt = Widget->mtable.LeftUp;

    if (funcInt == -1) return Success;

    bbDebug("funcInt = %d\n", funcInt);
    bbMoose_Leave* func = Moose->functions.LeftUp[funcInt];

    return func(moose, widgets, widget, graphics);
}