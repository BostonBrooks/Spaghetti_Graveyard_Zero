

#include "engine/core/bbAgent.h"
#include "engine/logic/bbVPool.h"

//typedef bbFlag bbAgent_Constructor (bbAgent** agent, struct bbAgents* agents, bbMapCoords coords, char* name);
bbFlag bbAgent_Constructor_NULL(bbAgent** self, struct bbAgents* agents, bbMapCoords coords, char* name)
{
    bbHere();
}

bbFlag bbAgentFunctions_populate(bbAgentFunctions* self)
{
    bbAgentFunctions_add(self, AgentConstructor,bbAgent_Constructor_NULL, "NULL");
    return Success;
}