#ifndef BBAGENT_H
#define BBAGENT_H
#include "engine/viewport/bbUnits.h"


typedef enum
{
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
} bbAgentFunctionType;


typedef struct
{
    I32 constructor;
    I32 update;
    I32 onCommand;
} bbAgentFunctionsTable;

typedef struct
{
    char* name;
    
    // Used as bbAgent_Constructor
    I32 constructor;
    bbAgentFunctionsTable functions;
} bbAgentType;

typedef struct
{
    //ints are easier to serialise
    I32 type;
    bbAgentState state;
    bbPool_Handle targetUnit;
    bbMapCoords targetCoords;
    bbMapCoords position;
    bbPool_Handle unit;
    I32 moveable;
    

} bbAgent;

typedef struct
{
    bbSquareCoords coords;
    bbList list;
} bbAgentsSquare;

typedef bbFlag bbAgent_Update (bbAgent* agent, void* unused);
typedef bbFlag bbAgent_OnCommand (bbAgent* agent, bbAgentCommandType type, bbPool_Handle data);
typedef bbFlag bbAgent_Constructor (bbAgent* agent, struct bbAgents* agents, bbMapCoords coords);

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
    
    
} bbAgentFunctions;

typedef struct bbAgents
{
    bbVPool* pool;
    //here goes bbAgents that don't fit into any squares
    bbList list;
    
    bbAgentFunctions functions;
    
    bbDictionary* agent_type_dict;
    bbAgentType agent_types[2];
    
    
    

    I32 squares_i;
    I32 squares_j;
    bbAgentsSquare squares[];

} bbAgents;




bbFlag bbAgents_new(bbAgents* agents);

bbFlag bbAgent_constructor(bbAgent** self,
                           bbAgents* agents,
                           char* type,
                           //not all units need to be named
                           char* name,
                           bbMapCoords coords);

bbFlag bbAgent_onCommand(bbAgent* self, bbAgents* agents, bbAgentCommandType type, bbPool_Handle data);
bbFlag bbAgent_update(bbAgent* self, bbAgents* agents);


bbFlag bbAgentFunctions_new(bbAgentFunctions** self);
bbFlag bbAgentFunctions_populate(bbAgentFunctions* self);
bbFlag bbAgentFunctions_add(bbAgentFunctions* functions, bbAgentFunctionType fnType, void* fnPointer, char* key );
bbFlag bbAgentFunctions_getFunction(void** function, bbAgentFunctions* functions, bbAgentFunctionType fnType, char* key);
I32 bbAgentFunctions_getInt(bbAgentFunctions* functions, bbAgentFunctionType fnType, char* key);


#endif //BBAGENT_H