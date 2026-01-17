//typedef bbFlag bbMouse_IsOver (struct bbMouse* mouse, struct bbWidgets* widgets, struct bbWidget* widget);
#ifndef MOOSE_H
#define MOOSE_H

#include "engine/core/bbCoreInputs.h"
#include "engine/logic/bbVPool.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/viewport/bbViewport.h"
#include "engine/geometry/bbViewportCoords.h"
#include "engine/data/bbHome.h"
#include "engine/userinterface/bbSpell.h"

extern bbMapCoords testGoalPoint;

//catch all, eg Layout widget
bbFlag IsOver_Always(bbMouse* mouse, bbWidgets* widgets, bbWidget* widget)
{

    bbVPool* pool = widgets->pool;
    bbPool_Handle handle;
    bbVPool_reverseLookup(pool,widget,&handle);
    if (!bbVPool_handleIsEqual(pool,handle,mouse->isOver))
    {
        mouse->wasOver = mouse->isOver;
        mouse->isOver = handle;
    }

    return Break;

}

//if the mouse is over the widget, it teleports to somewhere else, execution continues
bbFlag IsOver_Teleport(bbMouse* mouse, bbWidgets* widgets, bbWidget* widget)
{

    bbScreenPointsRect rect = widget->rect;
    bbScreenPoints point = mouse->position;

    if (bbScreenPoints_inScreenPointsRect(point, rect)){
        widget->rect.left = rand()%(720*SCREEN_PPP - 52*SCREEN_PPP);
        widget->rect.top = rand()%(480*SCREEN_PPP - 52*SCREEN_PPP);


    }


    return Continue;
}

//mouse hovers over widget, uses pointer defined by widget
bbFlag IsOver_Hover(bbMouse* mouse, bbWidgets* widgets, bbWidget* widget)
{

    bbScreenPointsRect rect = widget->rect;
    bbScreenPoints point = mouse->position;

    if (bbScreenPoints_inScreenPointsRect(point, rect)){
        bbVPool* pool = widgets->pool;
        bbPool_Handle handle;
        bbVPool_reverseLookup(pool,widget,&handle);

        if (!bbVPool_handleIsEqual(pool,handle,mouse->isOver))
        {
            mouse->wasOver = mouse->isOver;
            mouse->isOver = handle;
        }
        return Break;
    }
    return Continue;
}

bbFlag IsOver_Viewport(bbMouse* mouse, bbWidgets* widgets, bbWidget* widget)
{

    bbScreenPointsRect rect = widget->rect;
    bbScreenPoints point = mouse->position;

    if (bbScreenPoints_inScreenPointsRect(point, rect)){
        bbVPool* pool = widgets->pool;
        bbPool_Handle handle;
        bbVPool_reverseLookup(pool,widget,&handle);

        if (mouse->rightDown /*&& mouse->rightChanged*/){
            //convert mouse coords into map coords and update goal point
            bbScreenPoints viewportCoords;
            viewportCoords.x = point.x - widget->rect.left;
            viewportCoords.y = point.y - widget->rect.top;


            bbViewport* VP = widget->extra_data;

            bbMapCoords MC = bbScreenCoords_getMapCoords(viewportCoords, VP);

            //TODO set false to true
            bbCore_setGoalPoint(home.shared.core, MC, false);
            bbCore_react(home.shared.core);


        }

        if (!bbVPool_handleIsEqual(pool,handle,mouse->isOver))
        {
            mouse->wasOver = mouse->isOver;
            mouse->isOver = handle;
        }
        return Break;
    }
    return Continue;
}

bbFlag Viewport_LeftDown(void* Mouse, void* widgets, void* Widget, void*
graphics){
    bbSpells* spells = &home.private.UI.spells;
    bbSpell* spell = spells->currentSpell;
    //bbDummySender* server = home.private.server;
    U64 gameTime = home.private.mapTime;
    bbWidget* widget = Widget;
    bbMouse* mouse = Mouse;
    bbScreenPoints point = mouse->position;

    bbScreenPoints viewportCoords;
    viewportCoords.x = point.x - widget->rect.left;
    viewportCoords.y = point.y - widget->rect.top;
    bbViewport* VP = widget->extra_data;

    bbMapCoords MC = bbScreenCoords_getMapCoords(viewportCoords, VP);
    //calculate map coords


    //bbSpell_receiveClick(spell, (void*) spells, MC, server, gameTime);

    return Success;
}
#endif
