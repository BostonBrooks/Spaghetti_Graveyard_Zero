#include "bbSystemIncludes.h"
/// contains data about the game?
#ifndef BBGAMECONSTANTS_H
#define BBGAMECONSTANTS_H

#include "bbGeometry.h"
#include "bbIntTypes.h"

typedef struct{
	//bbGame has no concept of bbScreenCoordsI or bbScreenCoordsF
    //window height pixels
	I32 Height;
    //window width pixels
	I32 Width;
}bbGameConstants;


#endif // BBGAMECONSTANTS_H