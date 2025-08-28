#include "engine/widgets/bbWidget.h"

bbFlag bbWidgets_new(bbWidgets** self)
{
    bbWidgets* widgets = (bbWidgets*)calloc(1,sizeof(bbWidgets));
    int magic_number = 256;
    bbWidgetPool_new(&widgets->widgets,sizeof(bbWidget), magic_number);
    bbDictionary_new(&widgets->addresses, magic_number);
    bbDictionary_new(&widgets->codes, magic_number);
    widgets->layout = NULL;
    widgets->prompt = NULL;
    widgets->functions = NULL;

    *self = widgets;
    return Success;

}

bbFlag bbWidgetFunctions_new(bbWidgetFunctions** self)
{
    bbWidgetFunctions* functions = (bbWidgetFunctions*)calloc(1,sizeof(bbWidgetFunctions));
    int magic_number = 256;

    functions->constructors = calloc(magic_number,sizeof(bbWidget_Constructor));
    bbDictionary_new(&functions->constructor_dict, magic_number);
    functions->num_constructors = 0;

    functions->updates = calloc(magic_number,sizeof(bbWidget_Update));
    bbDictionary_new(&functions->update_dict, magic_number);
    functions->num_updates = 0;

    functions->destructors = calloc(magic_number,sizeof(bbWidget_Destructor));
    bbDictionary_new(&functions->destructor_dict, magic_number);
    functions->num_destructors = 0;

    functions->onCommands = calloc(magic_number,sizeof(bbWidget_OnCommand));
    bbDictionary_new(&functions->onCommand_dict, magic_number);
    functions->num_onCommands = 0;

    functions->drawFunctions = calloc(magic_number,sizeof(bbWidget_DrawFunction));
    bbDictionary_new(&functions->drawFunction_dict, magic_number);
    functions->num_drawFunctions = 0;

    functions->mouseHandlers = calloc(magic_number,sizeof(bbWidget_Mouse));
    bbDictionary_new(&functions->mouseHandler_dict, magic_number);
    functions->num_mouseHandlers = 0;

    functions->onTimers = calloc(magic_number,sizeof(bbWidget_OnTimer));
    bbDictionary_new(&functions->onTimer_dict, magic_number);
    functions->num_onTimers = 0;

    *self = functions;
    return Success;

}

bbFlag bbWidgetFunctions_add(bbWidgetFunctions* functions, bbWidget_fnType fnType, void* fnPtr, char* key)
{
    int magic_number = 256;
    int available;
    bbPool_Handle address_for_dict;
    switch (fnType)
    {
    case Constructor:
        available = functions->num_constructors++;
        bbAssert(available < magic_number, "Too many constructors\n");
        functions->constructors[available] = fnPtr;
        address_for_dict.u64 = available;
        bbDictionary_add(functions->constructor_dict, key, address_for_dict);
        return Success;


    case Update:
        available = functions->num_updates++;
        bbAssert(available < magic_number, "Too many updators\n");
        functions->updates[available] = fnPtr;
        address_for_dict.u64 = available;
        bbDictionary_add(functions->update_dict, key, address_for_dict);
        return Success;

    case Destructor:
        available = functions->num_destructors++;
        bbAssert(available < magic_number, "Too many detructors\n");
        functions->destructors[available] = fnPtr;
        address_for_dict.u64 = available;
        bbDictionary_add(functions->destructor_dict, key, address_for_dict);
        return Success;

    case OnCommand:
        available = functions->num_onCommands++;
        bbAssert(available < magic_number, "Too many on commands\n");
        functions->onCommands[available] = fnPtr;
        address_for_dict.u64 = available;
        bbDictionary_add(functions->onCommand_dict, key, address_for_dict);
        return Success;

    case DrawFunction:
        available = functions->num_drawFunctions++;
        bbAssert(available < magic_number, "Too many on draw functions\n");
        functions->drawFunctions[available] = fnPtr;
        address_for_dict.u64 = available;
        bbDictionary_add(functions->drawFunction_dict, key, address_for_dict);
        return Success;

    case MouseHandler:
        available = functions->num_mouseHandlers++;
        bbAssert(available < magic_number, "Too many mouse handlers\n");
        functions->mouseHandlers[available] = fnPtr;
        address_for_dict.u64 = available;
        bbDictionary_add(functions->mouseHandler_dict, key, address_for_dict);
        return Success;

    case OnTimer:
        available = functions->num_onTimers++;
        bbAssert(available < magic_number, "Too many mouse handlers\n");
        functions->onTimers[available] = fnPtr;
        address_for_dict.u64 = available;
        bbDictionary_add(functions->onTimer_dict, key, address_for_dict);
        return Success;

    default:
        bbPrintf("Bad flag in bbWidgetFunctions_add\n");
        return None;

    }
}

bbFlag bbWidgetFunctions_getFunction(void** function, bbWidgetFunctions* functions, bbWidget_fnType type, char* key)
{

    bbPool_Handle address_for_dict;
    int address;
    switch (type)
    {
        case Constructor:
            bbDictionary_lookup(functions->constructor_dict, key, &address_for_dict);
            address = address_for_dict.u64;
            *function = functions->constructors[address];
            return Success;

        case Update:
            bbDictionary_lookup(functions->updates[address], key, &address_for_dict);
            address = address_for_dict.u64;
            *function = functions->updates[address];
            return Success;

        case Destructor:
            bbDictionary_lookup(functions->destructors[address], key, &address_for_dict);
            address = address_for_dict.u64;
            *function = functions->destructors[address];
            return Success;

        case OnCommand:
            bbDictionary_lookup(functions->onCommands[address], key, &address_for_dict);
            address = address_for_dict.u64;
            *function = functions->onCommands[address];
            return Success;

        case DrawFunction:
            bbDictionary_lookup(functions->drawFunctions[address], key, &address_for_dict);
            address = address_for_dict.u64;
            *function = functions->drawFunctions[address];
            return Success;

        case MouseHandler:
            bbDictionary_lookup(functions->mouseHandlers[address], key, &address_for_dict);
            address = address_for_dict.u64;
            *function = functions->mouseHandlers[address];
            return Success;

        case OnTimer:
            bbDictionary_lookup(functions->onTimers[address], key, &address_for_dict);
            address = address_for_dict.u64;
            *function = functions->onTimers[address];
            return Success;

        default:
            bbPrintf("Bad flag in bbWidgetFunctions_getFunction\n");
            return None;

    }
}

bbFlag bbWidgetFunctions_getInt(I32* funcInt, bbWidgetFunctions* functions, bbWidget_fnType fnType, char* key)
{
    bbPool_Handle address_for_dict;
    switch (fnType)
    {
    case Constructor:
        bbDictionary_lookup(functions->constructor_dict, key, &address_for_dict);
        *funcInt = address_for_dict.u64;
        return Success;
    case Update:
        bbDictionary_lookup(functions->update_dict, key, &address_for_dict);
        *funcInt = address_for_dict.u64;
        return Success;
    case Destructor:
        bbDictionary_lookup(functions->destructor_dict, key, &address_for_dict);
        *funcInt = address_for_dict.u64;
        return Success;
    case OnCommand:
        bbDictionary_lookup(functions->onCommand_dict, key, &address_for_dict);
        *funcInt = address_for_dict.u64;
        return Success;
    case DrawFunction:
        bbDictionary_lookup(functions->drawFunction_dict, key, &address_for_dict);
        *funcInt = address_for_dict.u64;
        return Success;

    case MouseHandler:
        bbDictionary_lookup(functions->mouseHandler_dict, key, &address_for_dict);
        *funcInt = address_for_dict.u64;
        return Success;

    case OnTimer:
        bbDictionary_lookup(functions->onTimer_dict, key, &address_for_dict);
        *funcInt = address_for_dict.u64;
        return Success;

    default:
        bbPrintf("bbWidgetFunctions_getInt\n");
        return None;
    }
}

bbFlag bbWidget_draw(bbWidget* widget, bbWidget_drawFuncClosure* cl);
{

    for (I32 i = 0; i < FRAMES_PER_WIDGET; i++)
    {
        bbFrame* frame = &widget->frames[i];
        if (frame->drawfunction < 0 || frame->drawfunction >= cl->functions.num_drawFunctions) continue;
        bbWidget_DrawFunction* function = cl->functions.drawFunctions[frame->drawfunction];
        if ( function == 0) continue;
        function(widget, frame, cl);
    }

    return Success;
}


//bbFlag testFunc(bbTree* tree, void* node, void* cl)
bbFlag bbWidget_drawTree(bbTree* tree, void* node, void* cl){
    bbWidget* widget = node;
    return bbWidget_draw(widget, cl);

}

//bbFlag testFunc(bbTree* tree, void* node, void* cl)
bbFlag bbWidget_mouseTree(bbTree* tree, void* node, void* cl){
    bbWidget* widget = node;
    return bbWidget_mouse(widget, cl);

}