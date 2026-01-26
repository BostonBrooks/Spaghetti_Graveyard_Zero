#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbPoolHandle.h"
#include "engine/network/bbNetworkPacket.h"

typedef enum
{
    NetworkCode_setGoalpoint
} bbNetworkCode_type;

typedef union
{
    bbMapCoords mapCoords;
} bbNetCode_data;

typedef struct
{
    bbPool_ListElement listElement;
    bbNetworkCode_type type;
    U64 sendTick;
    U64 actTick;
    U8 player;
    bbNetCode_data data;
} bbNetworkCode;


typedef struct
{
    bbVPool* pool;
    bbList priorityQueue;
} bbNetworkCodes;

bbFlag bbNetworkCodes_receiveNetworkPacket(bbNetworkCodes* networkCodes, bbNetworkPacket* packet);
