#include "bbWidgetFunctions.h"

#include "engine/widgets/bbWidgetFunctions0.h"


bbFlag bbWidgetFunctions_new(bbWidgetFunctions0** self)
{
    bbWidgetFunctions0* functions = calloc(1, sizeof(bbWidgetFunctions0));
    I32 magic_number = 256;


    functions->Constructors = calloc(magic_number, sizeof(bbWidget_Constructor));
    bbDictionary_new(&functions->Constructor_dict, magic_number);
    functions->Constructor_available = 0;

    functions->Update = calloc(magic_number, sizeof(bbWidget_Update));
    bbDictionary_new(&functions->Update_dict, magic_number);
    functions->Update_available = 0;

    functions->Destructors = calloc(magic_number, sizeof(bbWidget_Destructor));
    bbDictionary_new(&functions->Destructor_dict, magic_number);
    functions->Destructor_available = 0;

    functions->OnCommands = calloc(magic_number, sizeof(bbWidget_OnCommand));
    bbDictionary_new(&functions->OnCommand_dict, magic_number);
    functions->OnCommand_dict = 0;

    functions->MouseHandler = calloc(magic_number, sizeof(bbWidget_Mouse));
    bbDictionary_new(&functions->MouseHandler_dict, magic_number);
    functions->MouseHandler_available = 0;

    functions->OnTimers = calloc(magic_number, sizeof(bbWidget_OnTimer));
    bbDictionary_new(&functions->OnTimers_dict, magic_number);
    functions->OnTimers_dict = 0;

    bbWidgetFunctions_populate(&functions);

    *self = functions;
    return Success;
}