#include "engine/userinterface/bbUIApp.h"
#include "engine/data/bbHome.h"


//Global variables used for testing only :(
bbWidgets* testWidgets;
bbMapCoords testGoalPoint;
bool doRewind;
_Thread_local char* thread;
sfClock* testClock = NULL;
bbHome home;

int main(void)
{
    bbUIApp_newWindow(&home.private.UI);
    bbGraphicsApp_init(&home.constant.graphics);
    bbUIApp_init(&home.private.UI);

    sfSleep(sfSeconds(5));
    printf("We made it to the end!\n");
    exit(0);
}