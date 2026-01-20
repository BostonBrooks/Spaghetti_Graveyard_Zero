#include "engine/core/bbAgent.h"



bbFlag bbAgentFunctions_init(bbAgentFunctions* functions)
{
    I32 magic_number = nextPrime(256);

    functions->Constructor = calloc(magic_number, sizeof(bbAgent_Constructor*));
    bbAssert(functions->Constructor != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Constructor_dict, magic_number);
    functions->Constructor_available = 0;

    functions->Update = calloc(magic_number, sizeof(bbAgent_Constructor*));
    bbAssert(functions->Update != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Update_dict, magic_number);
    functions->Update_available = 0;

    functions->OnCommand = calloc(magic_number, sizeof(bbAgent_Constructor*));
    bbAssert(functions->OnCommand != NULL, "bad calloc\n");
    bbDictionary_new(&functions->OnCommand_dict, magic_number);
    functions->OnCommand_available = 0;

    return Success;

}

bbFlag bbAgentFunctions_add(bbAgentFunctions* functions, bbAgentFunctionType fnType, void* fnPointer, char* key )
{
    U32 available;
    bbPool_Handle handle;
    I32 magic_number = nextPrime(256);

    switch(fnType)
    {
    case AgentConstructor:
        available = functions->Constructor_available++;
        bbAssert(available < magic_number, "out of space\n");
        functions->Constructor[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->Constructor_dict, key, handle);
        return Success;

    case AgentOnCommand:
        available = functions->OnCommand_available++;
        bbAssert(available < magic_number, "out of space\n");
        functions->OnCommand[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->OnCommand_dict, key, handle);
        return Success;
    case AgentUpdate:

        available = functions->Update_available++;
        bbAssert(available < magic_number, "out of space\n");
        functions->Update[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->Update_dict, key, handle);
        return Success;

    default:
        bbAssert(0, "bad agent function type\n");
    }
}

I32 bbAgentFunctions_getInt(bbAgentFunctions* functions, bbAgentFunctionType fnType, char* key)
{
    bbDictionary* dict;
    switch(fnType)
    {
    case AgentConstructor:
        dict = functions->Constructor_dict;
        break;
    case AgentOnCommand:
        dict = functions->OnCommand_dict;
        break;
    case AgentUpdate:
        dict = functions->Update_dict;
        break;
    default:
        bbAssert(0, "bad agent function type\n");
    }
    bbPool_Handle handle;
    bbDictionary_lookup(dict, key, &handle);
    return handle.u64;
}


I32 bbAgents_getSquareIndex(I32 i, I32 j, I32 squares_i){
    return i + squares_i * j;
}

bbFlag bbAgent_update(bbAgent* agent, bbAgents* agents)
{
    I32 type = agent->type;

    bbAgentType* agentType = &agents->agent_types[type];

    bbAgent_Update* function = agents->functions.Update[agentType->functions.update];

    return function(agent, (void*) agents);
}

bbFlag bbAgent_constructor(bbAgent** self,
                           bbAgents* agents,
                           char* type,
                           //not all units need to be named
                           char* name,
                           bbMapCoords coords)
{
    bbAgent* agent;
    bbAgent_Constructor* constructor;
    bbPool_Handle handle;
    bbDictionary_lookup(agents->functions.Constructor_dict, type, &handle);
    constructor = agents->functions.Constructor[handle.u64];
    constructor(&agent, agents, coords, name);
    return Success;
}

bbFlag bbAgent_onCommand(bbAgent* agent, bbAgents* agents, bbAgentCommandType type, bbPool_Handle data)
{
    I32 agentTypeInt = agent->type;
    bbAgentType* agentType = &agents->agent_types[agentTypeInt];
    bbAgent_OnCommand* function = agents->functions.OnCommand[agentTypeInt];
    return function(agent, type, data);
}
