#include "engine/geometry/bbCoordinates.h"
#include "engine/includes/CSFML.h"
#include "engine/includes/game0.h"


bbMilliCoords bbMapCoords_getMilliCoords(bbMapCoords MC){
    bbMilliCoords mC;
    mC.i = MC.i * MILLS_PER_POINT;
    mC.j = MC.j * MILLS_PER_POINT;

    // unused for now
    mC.k = MC.k;
    return mC;
}

bbMapCoords bbMilliCoords_getMapCoords(bbMilliCoords mC){
    bbMapCoords MC;
    MC.i = bbArith_div(mC.i, MILLS_PER_POINT);
    MC.j = bbArith_div(mC.j, MILLS_PER_POINT);

    // unused for now
    MC.k = mC.k;
    return MC;
}

bbTileCoords bbMapCoords_getTileCoords(bbMapCoords MC){
    bbTileCoords TC;
    TC.i = bbArith_div(MC.i, POINTS_PER_TILE);
    TC.j = bbArith_div(MC.j, POINTS_PER_TILE);
    TC.k = MC.k;
    return TC;
}

bbSquareCoords bbMapCoords_getSquareCoords(bbMapCoords MC){
    bbSquareCoords SC;
    SC.i = bbArith_div(MC.i, POINTS_PER_SQUARE);
    SC.j = bbArith_div(MC.j, POINTS_PER_SQUARE);
    SC.k = MC.k;
    return SC;
}

bbSquareCoords bbTileCoords_getSquareCoords(bbTileCoords TC){
    bbSquareCoords SC;
    SC.i = bbArith_div(TC.i, POINTS_PER_TILE);
    SC.j = bbArith_div(TC.j, POINTS_PER_TILE);
    SC.k = TC.k;
    return SC;
}

/// get a vector from A to B, as seen on the 2d isometric projection
bbScreenPoints bbMapCoords_getScreenPoints_relative (bbMapCoords A,
                                                     bbMapCoords B){
    bbMapCoords delta;
    delta.i = B.i - A.i;
    delta.j = B.j - A.j;
    delta.k = B.k - A.k;

    bbScreenPoints SP;
    SP.x = delta.i + delta.j;
    SP.y = bbArith_div((delta.i - delta.j), 2) - delta.k;

    return SP;
}

bbFloat3D bbFloat3D_normalise (bbFloat3D foo){
    float abs = sqrt (foo.i * foo.i + foo.j * foo.j + foo.k * foo.k );
    foo.i /= abs;
    foo.j /= abs;
    foo.k /= abs;

    return foo;
}


bbMapCoords bbSquareCoords_getMapCoords(bbSquareCoords SC){
	bbMapCoords MC;
	MC.i = SC.i * POINTS_PER_SQUARE;
	MC.j = SC.j * POINTS_PER_SQUARE;
	MC.k = 0;

	return MC;
}

sfVector2f bbScreenPoints_getV2f(bbScreenPoints SP){
	sfVector2f V2f;
	V2f.x = (float) SP.x / SCREEN_PPP;
	V2f.y = (float) SP.y / SCREEN_PPP;

	return V2f;
}


bbScreenPoints pixel_getScreenPoints(I32 x, I32 y){
    bbScreenPoints SP;
    SP.x = x * SCREEN_PPP;
    SP.y = y * SCREEN_PPP;
    return SP;
}

I32 bbScreenPoints_inScreenPointsRect(bbScreenPoints SP,
                                      bbScreenPointsRect rect){

    if (SP.x < rect.left || SP.y < rect.top) return 0;

    I32 right = rect.left + rect.width;
    I32 bottom = rect.top + rect.height;

    if (SP.x > right || SP.y > bottom) return 0;

    return 1;
}