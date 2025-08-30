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

    bbHere()
    bbPool_Handle testHandle;
    testHandle.u64 = 117;
    bbDictionary_add(functions->OnCommand_dict,  "TEST", testHandle);
    bbHere()



    functions->OnCommand_dict = 0;

    functions->MouseHandler = calloc(magic_number, sizeof(bbWidget_Mouse));
    bbAssert(functions->MouseHandler != NULL, "bad calloc\n");
    bbDictionary_new(&functions->MouseHandler_dict, magic_number);
    functions->MouseHandler_available = 0;

    functions->OnTimers = calloc(magic_number, sizeof(bbWidget_OnTimer));
    bbAssert(functions->OnTimers != NULL, "bad calloc\n");
    bbDictionary_new(&functions->OnTimers_dict, magic_number);
    functions->OnTimers_dict = 0;



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
bbHere()
        available = functions->Constructor_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->Constructors[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->Constructor_dict, key, handle);
bbHere()
        return Success;

    case WidgetUpdate:
bbHere()
        available = functions->Update_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->Update[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->Update_dict, key, handle);
bbHere()
        return Success;

    case WidgetDestructor:
bbHere()
        available = functions->Destructor_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->Destructors[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->Destructor_dict, key, handle);
bbHere()
        return Success;

    case WidgetOnCommand:
bbHere()
        available = functions->OnCommand_available++;
bbHere()
        bbAssert(available < magic_number, "out of bounds error\n");
bbHere()
        functions->OnCommands[available] = fnPointer;
bbHere()
        handle.u64 = available;
bbHere()
        bbDictionary_add(functions->OnCommand_dict, key, handle);
bbHere()
        return Success;

    case WidgetMouseHandler:
bbHere()
        available = functions->MouseHandler_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->MouseHandler[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->MouseHandler_dict, key, handle);
bbHere()
        return Success;

    case WidgetOnTimer:
bbHere()
        available = functions->OnTimers_available++;
        bbAssert(available < magic_number, "out of bounds error\n");
        functions->OnTimers[available] = fnPointer;
        handle.u64 = available;
        bbDictionary_add(functions->OnTimers_dict, key, handle);
bbHere()
        return Success;


    default:
        bbAssert(0, "bad widget function type\n");
    }

    return Success;
}