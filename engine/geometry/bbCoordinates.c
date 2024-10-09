#include "engine/geometry/bbCoordinates.h"

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