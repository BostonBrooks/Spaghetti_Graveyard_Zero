#include <math.h>
#include "engine/core/bbMoveable.h"

#include "engine/core/bbCoreInputs.h"
#include "engine/data/bbHome.h"
#include "engine/logic/bbBloatedPool.h"


bbMilliCoords getForce(bbMoveables* moveables, bbMoveable* moveableA, bbMoveable* moveableB)
{

    //SpriteUnits[subject].Forces.i += (10000*idist)/dist/(dist - footprint)/(dist - footprint);
    //from Spaghetti_Graveyard_Demos/OldNoTerrainDemo/06_Units.h
    bbMilliCoords mC;
    mC.i = 1;
    mC.j = 1;
    mC.k = 1;

    return mC;
}

bbMilliCoords sumForces(bbMoveables* moveables, bbMoveable* moveableA)
{
    bbMoveable* moveableB;
    bbMilliCoords single, total;
    total.i = 0;
    total.j = 0;
    total.k = 0;

    for (I32 i=0; i < 256; i++)
    {
        moveableB = &moveables->moveables[i];
        if (moveableB->type == MoveableType_Unused || moveableB->type == MoveableType_None) continue;
        if (moveableA == moveableB) continue;
        single = getForce(moveables,moveableA, moveableB);
        total.i += single.i;
        total.j += single.j;

    }
    return total;
}

bbFlag bbMoveables_init(bbMoveables* moveables)
{
    bbHere()
    moveables->updatesPerFrame = 4;
    for (I32 i = 0; i < numSegments; i++)
    {
        //I haven't decided yet...
        moveables->repulsions[i] = 0;

    }
    moveables->repulsion_scale = 1000;
    moveables->segment_length = 1000;
    moveables->useCoordsA = true;

    for (I32 i = 0; i < numMoveables; i++)
    {
        moveables->moveables[i].type = MoveableType_Unused;
    }

    return Success;
}

bbFlag bbMoveables_clear(bbMoveables* moveables)
{
    for (I32 i = 0; i < numMoveables; i++)
    {
        moveables->moveables[i].type = MoveableType_Unused;
    }
    return Success;

}

bbFlag bbMoveables_attachUnit(bbMoveables* moveables, bbPool_Handle handle)
{
    for (I32 i = 0; i < numMoveables; i++)
    {
        if (moveables->moveables[i].type == MoveableType_Unused)
        {
            moveables->moveables[i].type = MoveableType_None;
            moveables->moveables[i].unit = handle;

            return Success;
        }
    }
    return None;
}

bbFlag bbMoveables_getInput(bbMoveables* moveables)
{
    moveables->useCoordsA = true;
    for (I32 i = 0; i < numMoveables; i++)
    {
        bbMoveable* moveable = &moveables->moveables[i];
        if (moveable->type == MoveableType_Unused) continue;
        bbUnit* unit;


        bbVPool_lookup(home.private.viewportApp.units->pool, (void**)&unit, moveable->unit);

        bbMapCoords mapCoords; bbMilliCoords mC;
        mapCoords = unit->drawable.coords;
        mC = bbMapCoords_getMilliCoords(mapCoords);
        moveable->coordsA = mC;
        moveable->coordsOriginal = mC;

        //mapCoords = unit->goalPoint;
        mapCoords = home.private.viewportApp.viewport.viewpoint;
        mC = bbMapCoords_getMilliCoords(mapCoords);
        moveable->goalPoint = mC;

        moveable->type = unit->moveableType;

    }
    return Success;
}

bbFlag bbMoveables_updateOnce(bbMoveables* moveables)
{
    //for now, just move 2048 mills toward goal point
    if (moveables->useCoordsA)
    {

        for (I32 i = 0; i < numMoveables; i++)
        {
            bbMoveable* moveable = &moveables->moveables[i];

            if (moveable->type != MoveableType_Moving) continue;

            bbMilliCoords currentLocation = moveable->coordsA;
            bbMilliCoords goalPoint = moveable->goalPoint;

            double distance_i = goalPoint.i - currentLocation.i;
            double distance_j = goalPoint.j - currentLocation.j;

            double distance = sqrt(distance_i * distance_i + distance_j * distance_j);

            if (distance < 1024)
            {
                moveable->coordsB = goalPoint;
            }

            double delta_i = distance_i / distance * 1024;
            double delta_j = distance_j / distance * 1024;

            bbMilliCoords forces = sumForces(moveables, moveable);

            bbDebug("forces.i = %lld, forces.j = %lld\n", forces.i, forces.j);
            moveable->coordsB.i = currentLocation.i + delta_i + forces.i;
            moveable->coordsB.j = currentLocation.j + delta_j + forces.j;


        }
        moveables->useCoordsA = false;
        return Success;
    } else {

        for (I32 i = 0; i < numMoveables; i++)
        {
            bbMoveable* moveable = &moveables->moveables[i];

            if (moveable->type != MoveableType_Moving) continue;

            bbMilliCoords currentLocation = moveable->coordsB;
            bbMilliCoords goalPoint = moveable->goalPoint;

            double distance_i = goalPoint.i - currentLocation.i;
            double distance_j = goalPoint.j - currentLocation.j;

            double distance = sqrt(distance_i * distance_i + distance_j * distance_j);

            if (distance < 2048)
            {
                moveable->coordsA = goalPoint;
            }

            double delta_i = distance_i / distance * 2048;
            double delta_j = distance_j / distance * 2048;

            bbMilliCoords forces = sumForces(moveables, moveable);
            bbDebug("forces.i = %lld, forces.j = %lld\n", forces.i, forces.j);

            moveable->coordsA.i = currentLocation.i + delta_i + forces.i;
            moveable->coordsA.j = currentLocation.j + delta_j + forces.j;
        }
        moveables->useCoordsA = true;
        return Success;
    }
}

bbFlag bbMoveables_update(bbMoveables* moveables)
{
    for (I32 i = 0; i < moveables->updatesPerFrame; i++)
    {
        bbMoveables_updateOnce(moveables);
    }

    return Success;
}

bbFlag bbMoveables_putOutput(bbMoveables* moveables)
{
    if (moveables->useCoordsA)
    {
        for (I32 i = 0; i < numMoveables; i++)
        {
            bbMoveable* moveable = &moveables->moveables[i];

            if (moveable->type != MoveableType_Moving) continue;

            bbUnit* unit;
            bbVPool_lookup(home.private.viewportApp.units->pool, (void**)&unit, moveable->unit);

            bbMapCoords mapCoords; bbMilliCoords mC;

            mC = moveable->coordsA;
            mapCoords = bbMilliCoords_getMapCoords(mC);

            //TODO bbUnit_setLocation
            unit->drawable.coords = mapCoords;
        }
        return Success;
    }else
    {
        for (I32 i = 0; i < numMoveables; i++)
        {
            bbMoveable* moveable = &moveables->moveables[i];

            if (moveable->type != MoveableType_Moving) continue;

            bbUnit* unit;
            bbVPool_lookup(home.private.viewportApp.units->pool, (void**)&unit, moveable->unit);

            bbMapCoords mapCoords; bbMilliCoords mC;



            mC = moveable->coordsB;
            mapCoords = bbMilliCoords_getMapCoords(mC);

            //TODO bbUnit_setLocation
            unit->drawable.coords = mapCoords;
        }
        return Success;
    }
}

//TODO if called by bbInstruction_updateMoveables_fn then isInput == false
//add argument to bbMoveables_putOutput_Core
bbFlag bbMoveables_putOutput_Core(bbMoveables* moveables)
{
    if (moveables->useCoordsA)
    {
        for (I32 i = 0; i < numMoveables; i++)
        {
            bbMoveable* moveable = &moveables->moveables[i];

            if (moveable->type != MoveableType_Moving) continue;

            bbMapCoords mapCoords; bbMilliCoords mC;


            I32 delta_i = moveable->coordsA.i - moveable->coordsOriginal.i;
            I32 delta_j = moveable->coordsA.j - moveable->coordsOriginal.j;

            float rotation = atan2(delta_i, delta_j);

           // bbDebug("delta_i = %d, delta_j = %d, rotation = %f\n", delta_i, delta_j,rotation);


            mC = moveable->coordsA;
            mapCoords = bbMilliCoords_getMapCoords(mC);

            bbCore_moveRotateUnit(home.shared.core, mapCoords, rotation, moveable->unit, false);

        }
        return Success;
    }else
    {
        for (I32 i = 0; i < numMoveables; i++)
        {
            bbMoveable* moveable = &moveables->moveables[i];

            if (moveable->type != MoveableType_Moving) continue;

            bbMapCoords mapCoords; bbMilliCoords mC;


            I32 delta_i = moveable->coordsB.i - moveable->coordsOriginal.i;
            I32 delta_j = moveable->coordsB.j - moveable->coordsOriginal.j;

            float rotation = atan2(delta_i, delta_j);

            //bbDebug("delta_i = %d, delta_j = %d, rotation = %f\n", delta_i, delta_j,rotation);


            mC = moveable->coordsB;
            mapCoords = bbMilliCoords_getMapCoords(mC);

            bbCore_moveRotateUnit(home.shared.core, mapCoords,rotation, moveable->unit, false);

        }
        return Success;
    }
}