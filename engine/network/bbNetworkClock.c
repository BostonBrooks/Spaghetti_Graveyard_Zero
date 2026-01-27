#include "engine/network/bbNetworkClock.h"

I32 sortByTimeDifference(void* a, void* b)
{
    bbNetworkClock_maths* A = a;
    bbNetworkClock_maths* B = b;
    return (A->time_difference > B->time_difference);
}


