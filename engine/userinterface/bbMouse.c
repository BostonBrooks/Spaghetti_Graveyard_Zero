
#include "engine/userinterface/bbMouse.h"

#include "engine/userinterface/bbWidget.h"


bbFlag bbMouse_Init(bbMouse* mouse, void* Widgets, bbGraphicsApp* graphics)
{
    bbWidgets* widgets = (bbWidgets*)Widgets;
    mouse->position.x = 720*4;
    mouse->position.y = 480*4;
    mouse->leftDown = false;
    mouse->rightDown = false;
    mouse->leftChanged = false;
    mouse->rightChanged = false;
    mouse->wasOver = widgets->pool->null;
    mouse->isOver = widgets->pool->null;
    mouse->selected = widgets->pool->null;

    widgets->mouse = mouse;
    return Success;
}

bbFlag bbMouse_Event(bbMouse* mouse, sfEvent* event)
{
    sfMouseButton button;
    switch (event->type){
    case sfEvtMouseMoved:
        mouse->position = pixel_getScreenPoints(event->mouseMove.x,
                                                event->mouseMove.y);

        break;
        case sfEvtMouseButtonPressed:
            button = event->mouseButton.button;
            mouse->position = pixel_getScreenPoints(event->mouseButton.x,event->mouseButton.y);
            if (button == sfMouseLeft)
            {
                mouse->leftChanged = true;
                mouse->leftDown = true;
                mouse->previousPosition = mouse->position;

            } else if (button == sfMouseRight)
            {
                mouse->rightChanged = true;
                mouse->rightDown = true;
            }
            break;
        case sfEvtMouseButtonReleased:

            button = event->mouseButton.button;
            mouse->position = pixel_getScreenPoints(event->mouseButton.x,event->mouseButton.y);
            if (button == sfMouseLeft)
            {
                mouse->leftChanged = true;
                mouse->leftDown = false;
            } else if (button == sfMouseRight)
            {
                mouse->rightChanged = true;
                mouse->rightDown = false;
            }
            break;
    default:{
            bbDebug("input not recognised\n");
    }
    }
    return Success;
}

bbFlag bbMouse_isOver(bbMouse* mouse, void* Widgets)
{
    bbWidgets* widgets = (bbWidgets*)Widgets;

    bbMouse_isOver_cl cl;
    cl.widgets = widgets;

    bbTree* tree = widgets->tree;
    bbVPool* pool = tree->pool;
    void* root;
    bbVPool_lookup(pool, &root, tree->root);
    return bbTree_ascendingMapVisible(tree, root, bbMouse_isOverFunc, &cl);
    return Success;
}

bbFlag bbMouse_Update(bbMouse* mouse, void* Widgets, bbGraphicsApp* graphics)
{
    bbWidgets* widgets = Widgets;
    bbVPool* pool = widgets->pool;
    if(!bbVPool_handleIsEqual(pool, mouse->wasOver, pool->null)){
        bbWidget* toLeave;
        bbWidget* toEnter;

        bbVPool_lookup(pool, (void**)&toLeave, mouse->wasOver);
        bbVPool_lookup(pool, (void**)&toEnter, mouse->isOver);
        bbMouse_LeaveWidget(mouse, widgets, toLeave, graphics);
        bbMouse_EnterWidget(mouse, widgets, toEnter, graphics);

        mouse->wasOver = pool->null;

    }
    if (mouse->leftDown && mouse->leftChanged){

        bbWidget* widget;



        bbVPool_lookup(pool, (void**)&widget, mouse->isOver);
        bbMouse_LeftDownWidget (mouse, widgets, widget, graphics);

    } else if (!mouse->leftDown && mouse->leftChanged) {
        bbWidget* widget;
        if(!bbVPool_handleIsEqual(pool, mouse->selected, pool->null)) {
            bbVPool_lookup(pool, (void **) &widget, mouse->selected);
            bbMouse_LeftUpWidget(mouse, widgets, widget, graphics);
        }
    } else if (mouse->leftDown && !mouse->leftChanged) {
        bbWidget* widget;
        if(!bbVPool_handleIsEqual(pool, mouse->selected, pool->null)) {
            bbVPool_lookup(pool, (void **) &widget, mouse->selected);
            bbMouse_LeftDragWidget(mouse, widgets, widget, graphics);
        }
    }


    return Success;
}

bbFlag bbMouse_isOverFunc(bbTree* tree, void* node, void* cl)
{
    bbWidget* widget = (bbWidget*)node;
    bbMouse_isOver_cl* closure = (bbMouse_isOver_cl*)cl;
    bbWidgets* widgets = closure->widgets;
    bbMouse* mouse = widgets->mouse;

    I32 funcInt = widget->mtable.isOver;

    if (funcInt == -1) return Continue;

    bbMouse_IsOver* func = mouse->functions.IsOver[funcInt];

    return func(mouse, widgets, widget);

}

bbFlag bbMouse_Draw(bbMouse* mouse, void* Widgets, bbGraphicsApp* graphics,
                    sfRenderWindow* window)
{

    bbWidgets* widgets = (bbWidgets*)Widgets;

    bbPool_Handle selectedHandle = mouse->selected;
    if (!bbVPool_handleIsEqual(widgets->pool, selectedHandle,
                              widgets->pool->null)){
        bbWidget* selected;
        bbVPool_lookup(widgets->pool, (void**)&selected, selectedHandle);

        if (selected->mtable.DragIcon >= 0){
            bbScreenPoints dragged_SP;
            dragged_SP.x = mouse->position.x - mouse->dragOrigin.x;
            dragged_SP.y = mouse->position.y - mouse->dragOrigin.y;
            sfVector2f pos = bbScreenPoints_getV2f(dragged_SP);
            sfSprite* sprite = graphics->sprites->sprites[selected->mtable.DragIcon];
            sfSprite_setPosition(sprite, pos);
            sfRenderWindow_drawSprite(window, sprite, NULL);


        }

    }

    sfVector2f pos;
    bbPool_Handle widgetHandle = mouse->isOver;
    bbWidget* widget;
    bbVPool_lookup(widgets->pool, (void**)&widget, widgetHandle);

    pos = bbScreenPoints_getV2f(mouse->position);
    int spriteInt = widget->mtable.MouseIcon;
    if (spriteInt < 0) spriteInt = 0;
    sfSprite* sprite = graphics->sprites->sprites[spriteInt];
    sfSprite_setPosition(sprite, pos);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    return Success;
}

bbFlag bbMouse_EnterWidget(void* mouse, void* widgets, void* Widget, void*
graphics)
{
    bbWidget* widget = Widget;
    bbMouse* Mouse = mouse;
    I32 funcInt = widget->mtable.Enter;

    if (funcInt == -1) return Success;

    bbMouse_Leave* func = Mouse->functions.Enter[funcInt];

    return func(mouse, widgets, Widget, graphics);
}

bbFlag bbMouse_LeaveWidget(void* Mouse, void* widgets, void* Widget, void*
graphics)
{
    bbWidget* widget = Widget;
    bbMouse* mouse = Mouse;
    I32 funcInt = widget->mtable.Leave;

    if (funcInt == -1) return Success;

    bbMouse_Leave* func = mouse->functions.Leave[funcInt];

    return func(Mouse, widgets, Widget, graphics);
}

bbFlag bbMouse_LeftDownWidget(void* Mouse, void* widgets, void* Widget,
                                void* graphics)
{
    bbWidget* widget = Widget;
    bbMouse* mouse = Mouse;
    I32 funcInt = widget->mtable.LeftDown;

    if (funcInt == -1) return Success;

    bbMouse_Leave* func = mouse->functions.LeftDown[funcInt];

    return func(Mouse, widgets, Widget, graphics);
}
bbFlag bbMouse_LeftUpWidget(void* Mouse, void* widgets, void* Widget,
                                  void* graphics)
{
    bbWidget* widget = Widget;
    bbMouse* mouse = Mouse;
    I32 funcInt = widget->mtable.LeftUp;

    if (funcInt == -1) return Success;

    bbMouse_Leave* func = mouse->functions.LeftUp[funcInt];

    return func(Mouse, widgets, Widget, graphics);
}

bbFlag bbMouse_LeftDragWidget(void* Mouse, void* widgets, void* Widget,
                            void* graphics)
{
    bbWidget* widget = Widget;
    bbMouse* mouse = Mouse;
    I32 funcInt = widget->mtable.LeftDrag;

    if (funcInt == -1) return Success;

    bbMouse_Leave* func = mouse->functions.LeftDrag[funcInt];

    return func(Mouse, widgets, Widget, graphics);
}