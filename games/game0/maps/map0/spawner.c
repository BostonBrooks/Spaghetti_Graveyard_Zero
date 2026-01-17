#include "spawner.h"

#include "engine/data/bbHome.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/viewport/bbDrawables.h"
#include "engine/viewport/bbMapIcons.h"

bbFlag spawnEverything(void)
{
    bbViewportApp* app = &home.private.viewportApp;
    for (I32 i = 0; i<24;i++){
        for (I32 j=0; j<24;j++){

            bbMapCoords MC;
            MC.i = i * (POINTS_PER_SQUARE / 2);
            MC.j = j * (POINTS_PER_SQUARE / 2);
            MC.k = 0;

            MC.i += rand()%(100 * POINTS_PER_PIXEL);
            MC.j += rand()%(100 * POINTS_PER_PIXEL);

            bbDrawable* drawable;
            bbDrawable_newTree(&drawable, app->drawables, &home.constant.graphics,
                               MC);
            bbMapIcon* mapicon;
            bbMapIcon_new(&mapicon, app->mapIcons,&home.constant.graphics, MC);
            bbAvoidable* avoidable;
            bbAvoidable_new(&avoidable, app->avoidables, MC, 160);


        }
    }

    for (I32 i = 0; i<12;i++) {
        for (I32 j = 0; j < 12; j++) {
            bbMapCoords MC;

            MC.i = i * (POINTS_PER_SQUARE);
            MC.j = j * (POINTS_PER_SQUARE);
            MC.k = 0;

            MC.i += rand()%(100 * POINTS_PER_PIXEL);
            MC.j += rand()%(100 * POINTS_PER_PIXEL);

            bbUnit* unit;
            bbUnit_new(&unit,app->units, &home.constant.graphics,MC);
            bbPool_Handle handle;
            bbVPool_reverseLookup(app->units->pool,unit,  &handle);
            bbMoveables_attachUnit(&home.shared.core->moveables, handle);

//test
            bbUnit* testunit;
            bbVPool_lookup(home.private.viewportApp.units->pool, (void**)&testunit, handle);
        }
    }

    bbUnit* player;
    bbUnit_newCat(&player, app->units, &home.constant.graphics,
               home.private.viewportApp.viewport.viewpoint);
    home.shared.player = player;
}
