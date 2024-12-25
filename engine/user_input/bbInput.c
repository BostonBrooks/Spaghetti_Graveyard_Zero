#include "engine/logic/bbFlag.h"
#include "engine/includes/CSFML.h"
#include "engine/user_input/bbInput.h"
#include "engine/logic/bbTerminal.h"

bbFlag bbInput_new(bbInput* input, sfRenderWindow* window, bbMouse* mouse){

    input->mouse = mouse;

}

bbFlag bbInput_poll(bbInput* input, sfRenderWindow* window){
    sfEvent event;
    sfBool flag;

    while (1) {
        flag = sfRenderWindow_pollEvent(window, &event);
        if (flag == sfFalse) return Continue;
        switch (event.type){
            case sfEvtClosed: return Break;

            case sfEvtMouseMoved:{
                bbMouse_update(input->mouse, &event);
                break;
            }
            default:{
                bbDebug("input not recognised\n");
            }
        }

    }
}