/**
 * @file
 * @brief The functions in this folder define the behavior of an object with class bbActor and type NULL
 */
#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbSystemIncludes.h"
#include "recycle/headers/bbFlags.h"
#include "headers/bbActor.h"

///	Spawn a null actor on selected map at coordinates mc
I32 bbActor_NULL_new(bbActor** actor, I32 map, bbMapCoords mc){}

/// Update actor
I32 bbActor_NULL_update(bbActor* actor){}

/// Send a command to the actor
I32 bbActor_NULL_onCommand(bbActor* actor, I32 command, void* data){}

/// Delete actor, (being careful not to leave any dangling pointers)
I32 bbActor_NULL_delete(bbActor* actor){}
