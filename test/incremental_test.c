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

    sfClock* testClock1;
    testClock1 = sfClock_create();
    U64 run_time;
    U64 rest_time;

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

    rest_time = sfTime_asMicroseconds(sfClock_restart(testClock1));

    bbDebug("setup time = %llu", rest_time);

    while (1)
    {
        sfClock_restart(testClock1);
// We're not playing with network or networktime right now
        if (home.private.network.send_ready && home.private.network.receive_ready)
        {
            char str[64];
            sprintf(str, "maptime = %llu", home.private.mapTime );

            //bbNetwork_sendStr(&home.private.network, str);

            bbMapCoords MC;
            MC.i = 193;
            MC.j = -193;
            MC.k = 391;

            bbNetworkApp_sendGoalpoint(&home.private.network, &MC);
            bbNetworkTime_ping(&home.private.network);
            bbNetworkApp_checkInbox(&home.private.network);
            bbNetworkTime_updateTimeDiff(home.private.network.extra_data);

        }

        if (home.shared.playmode == PlayMode_play)
        {
            bbCore_updateViewpointToPlayer(&core, true);
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

        bbNetworkTime* network_time = home.private.network.extra_data;

        run_time = sfTime_asMicroseconds(  sfClock_restart(testClock1));

        if (network_time->timeCalibrated)
        {

            bbNetworkTime_waitInt(network_time, network_time->network_tick_time + 1);

        }

        rest_time = sfTime_asMicroseconds(  sfClock_restart(testClock1));
        double framerate = (double) 1000000 / (double) (run_time+rest_time);
        double load = (double) run_time / (double) (run_time+rest_time);
        bbDebug("run_time = %llu, rest_time = %llu, "
                "framerate = %f, load = %f\n",
                run_time, rest_time, framerate, load);


    }

    printf("We made it to the end!\n");
    exit(0);
}