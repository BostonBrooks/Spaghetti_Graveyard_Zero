#ifndef BBMOVEABLE_H
#define BBMOVEABLE_H
#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbPoolHandle.h"

//can't include this file or else circular
//#include "engine/viewport/bbUnits.h"

typedef enum
{
    //not associated with a bbUnit
    MoveableType_Unused,
    //Does not interact
    MoveableType_None,
    //Repels other moveables
    MoveableType_Fixed,
    //Can be pushed around
    MoveableType_Stationary,
    //Can move and push things around
    MoveableType_MovingToViewpoint,

    MoveableType_MovingToGoalPoint

} bbMoveable_type;

typedef struct
{
    bbPool_Handle unit;
    bbMoveable_type type;
    //radius
    //speed
    //force

    //coordsA and coordsB work like a double-buffer
    bbMilliCoords coordsOriginal;
    bbMilliCoords coordsA;
    bbMilliCoords coordsB;
    //goalPoint could be a pointer to another avoidable, but for now it is updated once per frame
    bbMilliCoords goalPoint;
} bbMoveable;

//force function is made of numSegments-1 linear segments.
// TODO: Is force a function of distance or squared distance?
#define numSegments 256
#define numMoveables 256

typedef struct
{
    I32 updatesPerFrame;
    //force function is made of numSegments-1 linear segments.
    I32 repulsions[numSegments];
    //divide by this before updating
    I32 repulsion_scale;
    I32 segment_length;
    bool useCoordsA;
    bbMoveable moveables[numMoveables];

} bbMoveables;


/**
 * How do we calculate force:
 *
 * We have: delta i, delta j, and an array of values
 *
 * We want: force in the i direction, force in the j direction
 *
 *
 */
bbMilliCoords getForce(bbMoveables* moveables, bbMoveable* moveableA, bbMoveable* moveableB);

bbFlag bbMoveables_init(bbMoveables* moveables);


bbFlag bbMoveables_attachUnit(bbMoveables* moveables, bbPool_Handle handle);

//get positions and goal points
bbFlag bbMoveables_getInput(bbMoveables* moveables);

// calculate one step of ordinary differential equation
bbFlag bbMoveables_updateOnce(bbMoveables* moveables);

// calculate updatesPerFrame steps of ordinary differential equation
bbFlag bbMoveables_update(bbMoveables* moveables);

// place instructions on the Core to move units. (for now just put back to the bbUnit)
bbFlag bbMoveables_putOutput(bbMoveables* moveables);

bbFlag bbMoveables_putOutput_Core(bbMoveables* moveables);

#endif  //BBMOVEABLE