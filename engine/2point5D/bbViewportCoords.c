#include "engine/2point5D/bbViewportCoords.h"



sfVector2f bbMapCoords_getV2f(bbMapCoords MC, bbViewport* VP){
    sfVector2f V2F;
    V2F.x = VP->width/2.0
            + (MC.i - VP->viewpoint.i) / (1.0 * POINTS_PER_PIXEL)
            + (MC.j - VP->viewpoint.j) / (1.0 * POINTS_PER_PIXEL);

    V2F.y = VP->height/2.0
            + (MC.i - VP->viewpoint.i) / (2.0 * POINTS_PER_PIXEL)
            - (MC.j - VP->viewpoint.j) / (2.0 * POINTS_PER_PIXEL)
            - (MC.k - VP->viewpoint.k) / (1.0 * POINTS_PER_PIXEL);

    return V2F;
}

sfVector2f bbMapCoords_getV2f_overlay(bbMapCoords MC, bbViewport* VP){
    sfVector2f V2F;
    V2F.x = VP->width/2.0
          + (MC.i - VP->viewpoint.i) / (1.0 * POINTS_PER_PIXEL * OVERLAY_SCALE)
          + (MC.j - VP->viewpoint.j) / (1.0 * POINTS_PER_PIXEL * OVERLAY_SCALE);

    V2F.y = VP->height/2.0
          + (MC.i - VP->viewpoint.i) / (2.0 * POINTS_PER_PIXEL * OVERLAY_SCALE)
          - (MC.j - VP->viewpoint.j) / (2.0 * POINTS_PER_PIXEL * OVERLAY_SCALE);

    return V2F;
}

bbMapCoords V2f_overlay_getMapCoords(sfVector2f V2F, bbViewport* VP){
	bbMapCoords MC;
	MC.i = ((V2F.x / 2 + V2F.y - VP->height/2 - VP->width / 4) * POINTS_PER_PIXEL * OVERLAY_SCALE) + VP->viewpoint.i;
	MC.j = ((V2F.x / 2 - V2F.y + VP->height/2 - VP->width / 4) * POINTS_PER_PIXEL * OVERLAY_SCALE) + VP->viewpoint.j;
	MC.k = 0;
	return MC;
}