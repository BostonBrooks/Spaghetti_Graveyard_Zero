#include "engine/user_input/bbMouseHandlers.h"

//typedef bbFlag bbMouseHandler(bbMouse* mouse, void* drawable, sfEvent* event);

//typedef bbFlag bbTreeFunction(bbTree* tree, void* node, void* cl);

typedef struct {
    bbMouse* mouse;
    void* drawable;
    sfEvent* event;
    bbMouseHandlers* functions;
} onMouseClosure;


bbFlag bbTree_onMouse(bbTree* tree, void* node, void* cl){
    bbWidget* widget = node;
    onMouseClosure* closure = cl;
    I32 onMouseInt = widget->onMouse->onMouse;
    bbMouseHandler* handler = closure->functions->functions[onMouseInt];

    return handler(closure->mouse, widget, closure->event);

}

bbFlag bbMouseHandler_onMouse(bbMouse* mouse, void* drawable, sfEvent* event){

    bbWidget* widget = drawable;

    if (bbScreenPoints_inScreenPointsRect(mouse->position, widget->rect)){
        bbDebug("mouse over\n");
        return Break;
    }
    return Continue;
}


bbFlag bbMouseHandlers_new(bbMouseHandlers** mouseHandlers){
    int num = 1;
    bbMouseHandlers* functions =
            malloc(sizeof(bbMouseHandlers) + num * sizeof(bbMouseHandler));
    bbAssert(functions!=NULL, "bad malloc");

    bbDictionary_new(&functions->dictionary, nextPrime(num));

    functions->num = num;
    bbPool_Handle handle;

    functions->functions[0] = bbMouseHandler_onMouse;
    handle.u64 = 0;
    bbDictionary_add(functions->dictionary, "ONMOUSE", handle);

    *mouseHandlers = functions;
    return Success;
}