#include "engine/user_input/bbMouseFunctions.h"

#include <stdlib.h>

#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbTerminal.h"


bbFlag bbMouseFunctions_init(bbMouseFunctions* functions)
{
    I32 magic_number = 256;

    functions->IsOver = calloc(magic_number, sizeof(bbMouse_IsOver));
    bbAssert(functions->IsOver != NULL, "bad calloc\n");
    bbDictionary_new(&functions->IsOver_dict, magic_number);
    functions->IsOver_available = 0;


    functions->Enter = calloc(magic_number, sizeof(bbMouse_Enter));
    bbAssert(functions->Enter != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Enter_dict, magic_number);
    functions->Enter_available = 0;


    functions->Leave = calloc(magic_number, sizeof(bbMouse_Leave));
    bbAssert(functions->Leave != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Leave_dict, magic_number);
    functions->Leave_available = 0;


    functions->LeftDown = calloc(magic_number, sizeof(bbMouse_LeftDown ));
    bbAssert(functions->LeftDown != NULL, "bad calloc\n");
    bbDictionary_new(&functions->LeftDown_dict, magic_number);
    functions->LeftDown_available = 0;


    functions->LeftUp = calloc(magic_number, sizeof(bbMouse_LeftUp ));
    bbAssert(functions->LeftUp != NULL, "bad calloc\n");
    bbDictionary_new(&functions->LeftUp_dict, magic_number);
    functions->LeftUp_available = 0;



    return Success;
}

bbFlag bbMouseFunctions_add(bbMouseFunctions* functions, MouseFunctionType fnType, void* fnPointer, char* key )
{


    I32 available;
    bbPool_Handle handle;
    I32 magic_number = 256;
    switch (fnType)
    {
    case MouseIsOver:

        available = functions->IsOver_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->IsOver[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->IsOver_dict, key, handle);
        return Success;

    case MouseEnter:

        available = functions->Enter_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->Enter[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->Enter_dict, key, handle);
        return Success;

    case MouseLeave:

        available = functions->Leave_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->Leave[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->Leave_dict, key, handle);
        return Success;

        case MouseLeftDown:

            available = functions->LeftDown_available++;
            bbAssert(available < magic_number, "out of bounds error\n");
            functions->LeftDown[available] = fnPointer;
            handle.u64 = available;
            bbDictionary_add(functions->LeftDown_dict, key, handle);
            return Success;

        case MouseLeftUp:

            available = functions->LeftUp_available++;
            bbAssert(available < magic_number, "out of bounds error\n");
            functions->LeftUp[available] = fnPointer;
            handle.u64 = available;
            bbDictionary_add(functions->LeftUp_dict, key, handle);
            return Success;

    default:
        bbAssert(0, "bad widget function type\n");
    }

}

I32 bbMouseFunctions_getInt(bbMouseFunctions* functions,
                                MouseFunctionType fnType, char* key){
    bbDictionary* dict;
    switch (fnType){
    case MouseIsOver:
        dict = functions->IsOver_dict;
        break;
    case MouseEnter:
        dict = functions->Enter_dict;
        break;
        case MouseLeave:
            dict = functions->Leave_dict;
            break;
        case MouseLeftDown:
            dict = functions->LeftDown_dict;
            break;
        case MouseLeftUp:
            dict = functions->LeftUp_dict;
            break;

    default:
        bbAssert(0, "bad widget function type\n");
    }

    bbPool_Handle handle;
    bbDictionary_lookup(dict,key,&handle);
    return handle.u64;
}

bbFlag bbMouseFunctions_getFunction(void** function, bbMouseFunctions* functions,
                                     MouseFunctionType fnType, char* key){
    bbPool_Handle handle;

    switch (fnType){
    case MouseIsOver:
        bbDictionary_lookup(functions->IsOver_dict,key,&handle);
        *function = functions->IsOver[handle.u64];
        return Success;
    default:
        bbAssert(0, "bad widget function type\n");

    }

}