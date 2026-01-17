#include "engine/logic/bbTerminal.h"
#include "engine/userinterface/bbWidget.h"

bbFlag NULL_Constructor (bbWidget** reference, void* graphics,
                         void* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{
    bbDebug("NULL Constructor\n");
    return Success;
}

bbFlag NULL_Update (bbWidget* widget, void* unused)
{
    bbDebug("NULL Update\n");
    return Success;
}

bbFlag NULL_Destructor (bbWidget* widget, void* unused)
{
    bbDebug("NULL Destructor\n");
    return Success;
}

bbFlag NULL_OnCommand (bbWidget* widget, void* data)
{
    bbDebug("NULL OnCommand\n");
    return Success;
}

bbFlag NULL_OnTimer (bbWidget* widget, void* void_timerNode)
{
    bbDebug("NULL OnTimer\n");
    return Continue;
}

bbFlag NULL_Hide (bbWidget* widget, void* void_timerNode)
{
    bbDebug("NULL Hide\n");
    return Continue;
}
bbFlag NULL_Unhide (bbWidget* widget, void* void_timerNode)
{
    bbDebug("NULL Unhide\n");
    return Continue;
}