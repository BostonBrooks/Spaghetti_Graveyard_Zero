#include "engine/logic/bbFlag.h"
#include "engine/includes/CSFML.h"
#include "engine/user_input/bbInput.h"
#include "engine/logic/bbTerminal.h"


bbFlag bbInput_new(bbInput* input, sfRenderWindow* window, bbMouse* mouse, bbMoose* moose){

    input->mouse = mouse;
    input->moose = moose;

}

bbFlag bbInput_poll(bbInput* input, sfRenderWindow* window){
    sfEvent event;
    sfBool flag;

    input->moose->rightChanged = false;
    input->moose->leftChanged = false;
    while (1) {
        flag = sfRenderWindow_pollEvent(window, &event);
        if (flag == sfFalse) return Continue;
        switch (event.type){
            case sfEvtClosed: return Break;

            case sfEvtMouseMoved:
            case sfEvtMouseButtonPressed:
            case sfEvtMouseButtonReleased:{
                if (input->mouse != NULL)
                {
                    bbMouse_update(input->mouse, &event);
                }
                bbMoose_Event(input->moose, &event);
                continue;
            }


            default:{
                bbDebug("input not recognised\n");
            }

        }

    }
}