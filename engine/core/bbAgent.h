#ifndef BBAGENT_H
#define BBAGENT_H
#include "engine/viewport/bbUnits.h"


typedef enum
{
    AgentState_frozen,
    AgentState_towardUnit,
    AgentState_towardCoords
} bbAgentState;

typedef enum
{
    AgentCommand_setTargetPoint,
    AgentCommand_setTargetUnit
} bbAgentCommandType ;


typedef enum
{
    AgentConstructor,
    AgentOnCommand,
    AgentUpdate,
    AgentType
} bbAgentFunctionType;


typedef struct
{
    I32 constructor;
    I32 update;
    I32 onCommand;
} bbAgentFunctionsTable;

typedef struct
{
    char name[64];
    bbAgentFunctionsTable functions;
} bbAgentType;

typedef struct
{
    //ints are easier to serialize
    I32 type;
    bbAgentState state;
    bbPool_Handle targetUnit;
    bbMapCoords targetCoords;
    bbMapCoords position;
    bbPool_Handle unit;
    bbPool_Handle moveable;

    bbPool_ListElement listElement;
    

} bbAgent;


typedef bbFlag bbAgent_Update (bbAgent* agent, void* agents);
typedef bbFlag bbAgent_OnCommand (bbAgent* agent, bbAgentCommandType type, bbPool_Handle data);
typedef bbFlag bbAgent_Constructor (bbAgent** agent, void* agents, bbMapCoords coords, char* name);

typedef struct
{


    bbAgent_Constructor** Constructor;
    bbDictionary* Constructor_dict;
    I32 Constructor_available;

    bbAgent_Update** Update;
    bbDictionary* Update_dict;
    I32 Update_available;
    
    bbAgent_OnCommand** OnCommand;
    bbDictionary* OnCommand_dict;
    I32 OnCommand_available;

    //this isn't so much a function as a set of attributes
    bbAgentType* Type;
    bbDictionary* Type_dict;
    I32 Type_available;
    
    
} bbAgentFunctions;

typedef struct bbAgents
{
    bbVPool* pool;
    bbList list;
    
    bbAgentFunctions functions;
    bbDictionary*  named_agents;
    bbDictionary* agent_type_dict;

    bbAgent* player;


    //I was going to put agents into squares but then I decided not to :P
    //if an agent is looking for something to react to, it can search through bbUnit squares
} bbAgents;




bbFlag bbAgents_new(bbAgents** agents, I32 squares_i, I32 squares_j, I32 numAgentTypes);


bbFlag bbAgent_constructor(bbAgent** self,
                           bbAgents* agents,
                           char* type,
                           //not all units need to be named
                           char* name,
                           bbMapCoords coords);

bbFlag bbAgent_newEmpty(bbAgent** self,
                           bbAgents* agents,
                           //not all units need to be named
                           char* name,
                           bbMapCoords coords);

//bbFlag bbAgent_new(bbAgent** self, bbAgents* agents, bbMapCoords coords, char* key);
bbFlag bbAgent_onCommand(bbAgent* self, bbAgents* agents, bbAgentCommandType type, bbPool_Handle data);
bbFlag bbAgent_update(bbAgent* self, bbAgents* agents);

bbFlag bbAgentTypes_init(bbAgents* agents);

bbFlag bbAgentFunctions_init(bbAgentFunctions* self);
bbFlag bbAgentFunctions_populate(bbAgentFunctions* self);
bbFlag bbAgentFunctions_add(bbAgentFunctions* functions, bbAgentFunctionType fnType, void* fnPointer, char* key );
bbFlag bbAgentFunctions_getFunction(void** function, bbAgentFunctions* functions, bbAgentFunctionType fnType, char* key);
I32 bbAgentFunctions_getInt(bbAgentFunctions* functions, bbAgentFunctionType fnType, char* key);


#endif //BBAGENT_H