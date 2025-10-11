//typedef bbFlag bbMoose_IsOver (struct bbMoose* moose, struct bbWidgets* widgets, struct bbWidget* widget);
#ifndef MOOSE_H
#define MOOSE_H

#include "engine/logic/bbVPool.h"
#include "engine/widgets/bbWidget.h"
#include "engine/2point5D/bbViewport.h"
#include "engine/2point5D/bbViewportCoords.h"

extern bbMapCoords testGoalPoint;

//catch all, eg Layout widget
bbFlag IsOver_Always(bbMoose* moose, bbWidgets* widgets, bbWidget* widget)
{

    bbVPool* pool = widgets->pool;
    bbPool_Handle handle;
    bbVPool_reverseLookup(pool,widget,&handle);
    if (!bbVPool_handleIsEqual(pool,handle,moose->isOver))
    {
        bbHere();
        moose->wasOver = moose->isOver;
        moose->isOver = handle;
    }

    return Break;

}

//if the mouse is over the widget, it teleports to somewhere else, execution continues
bbFlag IsOver_Teleport(bbMoose* moose, bbWidgets* widgets, bbWidget* widget)
{

    bbScreenPointsRect rect = widget->rect;
    bbScreenPoints point = moose->position;

    if (bbScreenPoints_inScreenPointsRect(point, rect)){
        bbDebug("Mouse interacts with Sphere\n");
        widget->rect.left = rand()%(720*8 - 52*8);
        widget->rect.top = rand()%(480*8 - 52*8);


    }


    return Continue;
}

//mouse hovers over widget, uses pointer defined by widget
bbFlag IsOver_Hover(bbMoose* moose, bbWidgets* widgets, bbWidget* widget)
{

    bbScreenPointsRect rect = widget->rect;
    bbScreenPoints point = moose->position;

    if (bbScreenPoints_inScreenPointsRect(point, rect)){
        bbVPool* pool = widgets->pool;
        bbPool_Handle handle;
        bbVPool_reverseLookup(pool,widget,&handle);

        if (!bbVPool_handleIsEqual(pool,handle,moose->isOver))
        {
            bbHere();
            moose->wasOver = moose->isOver;
            moose->isOver = handle;
        }
        return Break;
    }
    return Continue;
}

bbFlag IsOver_Viewport(bbMoose* moose, bbWidgets* widgets, bbWidget* widget)
{

    bbScreenPointsRect rect = widget->rect;
    bbScreenPoints point = moose->position;

    if (bbScreenPoints_inScreenPointsRect(point, rect)){
        bbVPool* pool = widgets->pool;
        bbPool_Handle handle;
        bbVPool_reverseLookup(pool,widget,&handle);

        if (moose->rightDown && moose->rightChanged){
            //convert moose coords into map coords and update goal point
            bbScreenPoints viewportCoords;
            viewportCoords.x = point.x - widget->rect.left;
            viewportCoords.y = point.y - widget->rect.top;


            bbViewport* VP = widget->extra_data;

            bbMapCoords MC = bbScreenCoords_getMapCoords(viewportCoords, VP);

            //testGoalPoint =

            bbDebug("MC.i = %d, MC.j = %d\nVP.i = %d, VP.j = %d\nGP.i = %d, "
                    "GP.j = %d\n", MC.i, MC.j, VP->viewpoint.i,VP->viewpoint.j,
                    testGoalPoint.i, testGoalPoint.j);
        }

        if (!bbVPool_handleIsEqual(pool,handle,moose->isOver))
        {
            bbHere();
            moose->wasOver = moose->isOver;
            moose->isOver = handle;
        }
        return Break;
    }
    return Continue;
}

#endif
