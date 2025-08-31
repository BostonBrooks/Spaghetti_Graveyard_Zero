#include "bbWidgetFunctions.h"
#include "engine/includes/CSFML.h"
#include "engine/widgets/bbWidgetFunctions.h"
#include <stdlib.h>


bbFlag bbWidgetFunctions_new(bbWidgetFunctions0** self)
{
    bbWidgetFunctions0* functions = calloc(1, sizeof(bbWidgetFunctions0));
    I32 magic_number = 256;


    functions->Constructors = calloc(magic_number, sizeof(bbWidget_Constructor));
    bbAssert(functions->Constructors != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Constructor_dict, magic_number);
    functions->Constructor_available = 0;

    functions->Update = calloc(magic_number, sizeof(bbWidget_Update));
    bbAssert(functions->Update != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Update_dict, magic_number);
    functions->Update_available = 0;

    functions->Destructors = calloc(magic_number, sizeof(bbWidget_Destructor));
    bbAssert(functions->Destructors != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Destructor_dict, magic_number);
    functions->Destructor_available = 0;

    functions->OnCommands = calloc(magic_number, sizeof(bbWidget_OnCommand));
    bbAssert(functions->OnCommands != NULL, "bad calloc\n");
    bbDictionary_new(&functions->OnCommand_dict, magic_number);
    functions->OnCommand_available = 0;

    functions->MouseHandler = calloc(magic_number, sizeof(bbWidget_Mouse));
    bbAssert(functions->MouseHandler != NULL, "bad calloc\n");
    bbDictionary_new(&functions->MouseHandler_dict, magic_number);
    functions->MouseHandler_available = 0;

    functions->OnTimers = calloc(magic_number, sizeof(bbWidget_OnTimer));
    bbAssert(functions->OnTimers != NULL, "bad calloc\n");
    bbDictionary_new(&functions->OnTimers_dict, magic_number);
    functions->OnTimers_available = 0;



    bbWidgetFunctions_populate(functions);

    *self = functions;
    return Success;
}


bbFlag bbWidgetFunctions_add(bbWidgetFunctions0* functions, WidgetFunctionType fnType, void* fnPointer, char* key )
{


    I32 available;
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
            bbDebug("dict.bins = %d, key = %s\n",
                    functions->OnCommand_dict->m_NumBins, key);
        bbDictionary_add(functions->OnCommand_dict, key, handle);
        return Success;

    case WidgetMouseHandler:

        available = functions->MouseHandler_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->MouseHandler[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->MouseHandler_dict, key, handle);
        return Success;

    case WidgetOnTimer:

        available = functions->OnTimers_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->OnTimers[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->OnTimers_dict, key, handle);
        return Success;


    default:
        bbAssert(0, "bad widget function type\n");
    }

    return Success;
}


I32 bbWidgetFunctions_getInt(bbWidgetFunctions0* functions,
                                WidgetFunctionType fnType, char* key){
    bbDictionary* dict;
    switch (fnType){
        case WidgetConstructor:
            dict = functions->Constructor_dict;
            break;
        case WidgetUpdate:
            dict = functions->Constructor_dict;
            break;
        case WidgetDestructor:
            dict = functions->Constructor_dict;
            break;
        case WidgetOnCommand:
            dict = functions->Constructor_dict;
            break;
        case WidgetMouseHandler:
            dict = functions->Constructor_dict;
            break;
        case WidgetOnTimer:
            dict = functions->Constructor_dict;
            break;
    }

    bbPool_Handle handle;
    bbDictionary_lookup(dict,key,&handle);
    return handle.u64;
}

bbFlag bbWidgetFunctions_getFunction(void** function, bbWidgetFunctions0* functions,
                                     WidgetFunctionType fnType, char* key){
    bbPool_Handle handle;

    switch (fnType){
        case WidgetConstructor:
            bbDictionary_lookup(functions->Constructor_dict,key,&handle);
            *function = functions->Constructors[handle.u64];
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
        case WidgetMouseHandler:
            bbDictionary_lookup(functions->MouseHandler_dict,key,&handle);
            *function = functions->MouseHandler[handle.u64];
            return Success;
        case WidgetOnTimer:
            bbDictionary_lookup(functions->OnTimers_dict,key,&handle);
            *function = functions->OnTimers[handle.u64];
            return Success;
    }

}