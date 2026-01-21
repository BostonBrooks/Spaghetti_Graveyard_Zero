

#include "engine/core/bbAgent.h"
#include "engine/data/bbHome.h"
#include "engine/logic/bbVPool.h"

//typedef bbFlag bbAgent_Constructor (bbAgent** agent, struct bbAgents* agents, bbMapCoords coords, char* name);
bbFlag bbAgent_Constructor_SKELETON(bbAgent** self, struct bbAgents* agents, bbMapCoords coords, char* name)
{
    bbAgent* agent;
    bbVPool_alloc(agents->pool, (void**)&agent);

    agent->type = 0;
    agent->state = AgentState_frozen;
    agent->targetUnit = home.private.viewportApp.units->pool->null;
    agent->targetCoords = coords;
    agent->position = coords;

    bbUnit* unit;
    bbUnit_new(&unit, home.private.viewportApp.units, &home.constant.graphics,coords);

    unit->moveableType = MoveableType_MovingToViewpoint;
    bbPool_Handle handle;
    bbVPool_reverseLookup(home.private.viewportApp.units->pool, unit, &handle);

    agent->unit = handle;
    agent->moveable.u64 = 0;
    bbList_pushL(&agents->list, agent);


    bbFlag flag = bbMoveables_attachUnit(&home.shared.core->moveables, handle);
    *self = agent;

    return Success;
}

bbFlag bbAgent_Constructor_PLAYER(bbAgent** self, struct bbAgents* agents, bbMapCoords coords, char* name)
{
    bbAgent* agent;
    bbVPool_alloc(agents->pool, (void**)&agent);

    agent->type = 0;
    agent->state = AgentState_frozen;
    agent->targetUnit = home.private.viewportApp.units->pool->null;
    agent->targetCoords = coords;
    agent->position = coords;

    bbUnit* unit;
    bbUnit_new(&unit, home.private.viewportApp.units, &home.constant.graphics,coords);
    unit->drawable.frames[0].handle.u64 = 10;
    unit->moveableType = MoveableType_MovingToGoalPoint;

    bbPool_Handle handle;
    bbVPool_reverseLookup(home.private.viewportApp.units->pool, unit, &handle);

    agent->unit = handle;
    agent->moveable.u64 = 0;
    bbList_pushL(&agents->list, agent);


    bbFlag flag = bbMoveables_attachUnit(&home.shared.core->moveables, handle);

    home.shared.agents->player = agent;

    *self = agent;

    return Success;
}

bbFlag bbAgentFunctions_populate(bbAgentFunctions* self)
{
    bbAgentFunctions_add(self, AgentConstructor,bbAgent_Constructor_SKELETON, "SKELETON");
    bbAgentFunctions_add(self, AgentConstructor,bbAgent_Constructor_PLAYER, "PLAYER");
    return Success;
}

//typedef bbFlag bbAgent_OnCommand (bbAgent* agent, bbAgentCommandType type, bbPool_Handle data);
