#include "engine/userinterface/bbWidgetFunctions.h"
#include "engine/includes/CSFML.h"
#include <stdlib.h>


bbFlag bbWidgetFunctions_new(bbWidgetFunctions** self)
{
    bbWidgetFunctions* functions = calloc(1, sizeof(bbWidgetFunctions));
    I32 magic_number = nextPrime(256);

//changes made fixed bug?
//functions->Constructors = calloc(magic_number, sizeof(bbWidget_Constructor));
    functions->Constructors = calloc(magic_number, sizeof(U64));
    bbAssert(functions->Constructors != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Constructor_dict, magic_number);
    functions->Constructor_available = 0;

    functions->Constructors2 = calloc(magic_number, sizeof(U64));
    bbAssert(functions->Constructors2 != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Constructor2_dict, magic_number);
    functions->Constructor2_available = 0;

    //functions->Update = calloc(magic_number, sizeof(bbWidget_Update));
    functions->Update = calloc(magic_number, sizeof(U64));
    bbAssert(functions->Update != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Update_dict, magic_number);
    functions->Update_available = 0;

//functions->Destructors = calloc(magic_number, sizeof(bbWidget_Destructor));
    functions->Destructors = calloc(magic_number, sizeof(U64));
    bbAssert(functions->Destructors != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Destructor_dict, magic_number);
    functions->Destructor_available = 0;

    //functions->OnCommands = calloc(magic_number, sizeof(bbWidget_OnCommand));
    functions->OnCommands = calloc(magic_number, sizeof(U64));
    bbAssert(functions->OnCommands != NULL, "bad calloc\n");
    bbDictionary_new(&functions->OnCommand_dict, magic_number);
    functions->OnCommand_available = 0;

    //functions->OnTimers = calloc(magic_number, sizeof(bbWidget_OnTimer));
    functions->OnTimers = calloc(magic_number, sizeof(U64));
    bbAssert(functions->OnTimers != NULL, "bad calloc\n");
    bbDictionary_new(&functions->OnTimers_dict, magic_number);
    functions->OnTimers_available = 0;

    //functions->OnTimers = calloc(magic_number, sizeof(bbWidget_OnTimer));
    functions->Hide = calloc(magic_number, sizeof(U64));
    bbAssert(functions->Hide != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Hide_dict, magic_number);
    functions->Hide_available = 0;

    //functions->OnTimers = calloc(magic_number, sizeof(bbWidget_OnTimer));
    functions->Unhide = calloc(magic_number, sizeof(U64));
    bbAssert(functions->Unhide != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Unhide_dict, magic_number);
    functions->Unhide_available = 0;




    *self = functions;
    return Success;
}


bbFlag bbWidgetFunctions_add(bbWidgetFunctions* functions, bbWidgetFunctionType fnType, void* fnPointer, char* key )
{

    U32 available;
    bbPool_Handle handle;
    I32 magic_number = 256;
    switch (fnType)
    {
    case WidgetConstructor:


        available = functions->Constructor_available++;
        bbAssert(available < magic_number, "out of bounds error\n");

        functions->Constructors[available] = fnPointer;
        handle.u64 = available;

        bbDictionary_add(functions->Constructor_dict, key, handle);

        return Success;

    case WidgetConstructor2:


        available = functions->Constructor2_available++;
        bbAssert(available < magic_number, "out of bounds error\n");

        functions->Constructors2[available] = fnPointer;
        handle.u64 = available;

        bbDictionary_add(functions->Constructor2_dict, key, handle);

        return Success;

    case WidgetUpdate:

        available = functions->Update_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->Update[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->Update_dict, key, handle);
        return Success;

    case WidgetDestructor:

        available = functions->Destructor_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->Destructors[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->Destructor_dict, key, handle);
        return Success;

    case WidgetOnCommand:

        available = functions->OnCommand_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->OnCommands[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->OnCommand_dict, key, handle);
        return Success;


    case WidgetOnTimer:

        available = functions->OnTimers_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->OnTimers[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->OnTimers_dict, key, handle);
        return Success;

    case WidgetHide:

        available = functions->Hide_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->Hide[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->Hide_dict, key, handle);
        return Success;

    case WidgetUnhide:

        available = functions->Unhide_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->Unhide[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->Unhide_dict, key, handle);
        return Success;


    default:
        bbAssert(0, "bad widget function type\n");
    }

    return Success;
}


I32 bbWidgetFunctions_getInt(bbWidgetFunctions* functions,
                             bbWidgetFunctionType fnType, char* key){
    bbDictionary* dict;
    switch (fnType){
    case WidgetConstructor:
        dict = functions->Constructor_dict;
        break;
    case WidgetConstructor2:
        dict = functions->Constructor2_dict;
        break;
        case WidgetUpdate:
            dict = functions->Update_dict;
            break;
        case WidgetDestructor:
            dict = functions->Destructor_dict;
            break;
        case WidgetOnCommand:
            dict = functions->OnCommand_dict;
            break;
        break;
    case WidgetOnTimer:
        dict = functions->OnTimers_dict;
        break;
    case WidgetHide:
        dict = functions->Hide_dict;
        break;
    case WidgetUnhide:
        dict = functions->Unhide_dict;
        break;
    }

    bbPool_Handle handle;
    bbDictionary_lookup(dict,key,&handle);
    return handle.u64;
}

bbFlag bbWidgetFunctions_getFunction(void** function, bbWidgetFunctions* functions,
                                     bbWidgetFunctionType fnType, char* key){
    bbPool_Handle handle;

    switch (fnType){
    case WidgetConstructor:
        bbDictionary_lookup(functions->Constructor_dict,key,&handle);
        *function = functions->Constructors[handle.u64];
        return Success;
    case WidgetConstructor2:
        bbDictionary_lookup(functions->Constructor2_dict,key,&handle);
        *function = functions->Constructors2[handle.u64];
        return Success;
        case WidgetUpdate:
            bbDictionary_lookup(functions->Update_dict,key,&handle);
            *function = functions->Update[handle.u64];
            return Success;
        case WidgetDestructor:
            bbDictionary_lookup(functions->Destructor_dict,key,&handle);
            *function = functions->Destructors[handle.u64];
            return Success;
        case WidgetOnCommand:
            bbDictionary_lookup(functions->OnCommand_dict,key,&handle);
            *function = functions->OnCommands[handle.u64];
        return Success;
    case WidgetHide:
        bbDictionary_lookup(functions->Hide_dict,key,&handle);
        *function = functions->Hide[handle.u64];
        return Success;
    case WidgetUnhide:
        bbDictionary_lookup(functions->Unhide_dict,key,&handle);
        *function = functions->Unhide[handle.u64];
        return Success;
    }
    *function = NULL;
    return None;
}