#include "engine/user_input/bbMooseFunctions.h"

#include <stdlib.h>

#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbTerminal.h"


bbFlag bbMooseFunctions_init(bbMooseFunctions* functions)
{
    I32 magic_number = 256;

    functions->IsOver = calloc(magic_number, sizeof(bbMoose_IsOver));
    bbAssert(functions->IsOver != NULL, "bad calloc\n");
    bbDictionary_new(&functions->IsOver_dict, magic_number);
    functions->IsOver_available = 0;


    functions->Enter = calloc(magic_number, sizeof(bbMoose_Enter));
    bbAssert(functions->Enter != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Enter_dict, magic_number);
    functions->Enter_available = 0;


    functions->Leave = calloc(magic_number, sizeof(bbMoose_Leave));
    bbAssert(functions->Leave != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Leave_dict, magic_number);
    functions->Leave_available = 0;



    return Success;
}

bbFlag bbMooseFunctions_add(bbMooseFunctions* functions, MooseFunctionType fnType, void* fnPointer, char* key )
{


    I32 available;
    bbPool_Handle handle;
    I32 magic_number = 256;
    switch (fnType)
    {
    case MooseIsOver:

        available = functions->IsOver_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->IsOver[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->IsOver_dict, key, handle);
        return Success;

    case MooseEnter:

        available = functions->Enter_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->Enter[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->Enter_dict, key, handle);
        return Success;

    case MooseLeave:

        available = functions->Leave_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->Leave[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->Leave_dict, key, handle);
        return Success;

    default:
        bbAssert(0, "bad widget function type\n");
    }

}

I32 bbMooseFunctions_getInt(bbMooseFunctions* functions,
                                MooseFunctionType fnType, char* key){
    bbDictionary* dict;
    switch (fnType){
    case MooseIsOver:
        dict = functions->IsOver_dict;
        break;
    case MooseEnter:
        dict = functions->Enter_dict;
        break;
    case MooseLeave:
        dict = functions->Leave_dict;
        break;

    default:
        bbAssert(0, "bad widget function type\n");
    }

    bbPool_Handle handle;
    bbDictionary_lookup(dict,key,&handle);
    return handle.u64;
}

bbFlag bbMooseFunctions_getFunction(void** function, bbMooseFunctions* functions,
                                     MooseFunctionType fnType, char* key){
    bbPool_Handle handle;

    switch (fnType){
    case MooseIsOver:
        bbDictionary_lookup(functions->IsOver_dict,key,&handle);
        *function = functions->IsOver[handle.u64];
        return Success;
    default:
        bbAssert(0, "bad widget function type\n");

    }

}