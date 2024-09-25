#include <inttypes.h>

#ifndef BBGEOMETRY_H
#define BBGEOMETRY_H

#include "bbMapConstants.h"
#include "bbIntTypes.h"

///Fixed point, 2d coordinates, precision given by bbMap::m_ScreenPPP
typedef struct {
	///x axis is  right of top left
	I32 x;
	///y axis is down from top left
	I32 y;
} bbScreenCoordsI;

typedef struct {
	///x axis is  right of top left
	I32 x;
	///y axis is down from top left
	I32 y;
} bbViewportCoordsI;


typedef struct {
	///x axis is  right of top left
	float x;
	///y axis is down from top left
	float y;
} bbScreenCoordsF;



bbScreenCoordsF bbScreenCoordsI_getF(bbScreenCoordsI SCI, bbMapConstants* constants);
bbScreenCoordsI bbScreenCoordsF_getI(bbScreenCoordsF SCF, bbMapConstants* constants);
sfVector2f bbScreenCoordsI_getV2f(bbScreenCoordsI SCI, bbMapConstants* constants);


bool bbWidget_containsPoint(void* void_widget, bbScreenCoordsI SCI);
#endif //BBGEOMETRY_H