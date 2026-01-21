#include "engine/userinterface/bbUIApp.h"
#include  "games/game0/maps/map0/spawner.h"
#include "engine/core/bbCoreInputs.h"
#include "engine/data/bbHome.h"
#include "engine/network/bbNetworkApp.h"
#include "engine/core/bbAgent.h"


//Global variables used for testing only :(
bbWidgets* testWidgets;
bbMapCoords testGoalPoint;

_Thread_local char* thread;
sfClock* testClock = NULL;
bbHome home;

int main(void)
{

    home.shared.playmode = PlayMode_pause;
    bbCore core;
    bbCore_init(&core);
    home.shared.core = &core;

    bbUIApp_newWindow(&home.private.UI);
    bbGraphicsApp_init(&home.constant.graphics);
    bbNetworkApp_init(&home.private.network);
    //TODO: viewport is initialised here and not in bbViewportApp.
    //fix this after migrating from Incremental_test.c to bbUIApp_test.c
    bbUIApp_init(&home.private.UI);
    bbViewportApp_init(&home.private.viewportApp);
    bbAgents_new(&home.shared.agents, 12, 12,256);
    spawnEverything();


    home.private.mapTime = 0;


    bbCore_incrementClock(&core, true);
    bbCore_react(&core);
    while (1)
    {
/* We're not playing with network or networktime right now
        if (home.private.network.send_ready && home.private.network.receive_ready)
        {
            char str[64];
            sprintf(str, "maptime = %llu", home.private.mapTime );

            bbNetwork_sendStr(&home.private.network, str);
            bbNetworkTime_ping(&home.private.network);
            bbNetworkApp_checkInbox(&home.private.network);
            bbNetworkApp_checkTime(&home.private.network);

        }
  */
        if (home.shared.playmode == PlayMode_play)
        {
            bbCore_updateViewpoint(&core, true);
            bbCore_react(&core);

            bbCore_updateMoveables(&core, true);
            bbCore_react(&core);
        }
        bbMouse_isOver(&home.private.UI.mouse, &home.private.UI.widgets);
        bbMouse_Update(&home.private.UI.mouse, &home.private.UI.widgets, &home.constant.graphics);

        if (home.private.mapTime % 60 == 0 && home.shared.playmode != PlayMode_pause) {bbPrintf("mapTime = %llu\n", home.private.mapTime/60)};
        bbUIApp_draw(&home.private.UI);

        bbFlag flag = bbInput_poll(&home.private.UI.input, home.private.UI.window);

        if (flag == Break) break;
        if (home.shared.playmode == PlayMode_play)
        {
            bbCore_incrementClock(&core, true);
            bbCore_react(&core);
        }


        if (home.shared.playmode == PlayMode_rewind)
        {
            bbCore_rewindUntilTime(&core,  home.private.mapTime - 1);
            bbCore_clearFuture(&core);
        }
    }

    printf("We made it to the end!\n");
    exit(0);
}