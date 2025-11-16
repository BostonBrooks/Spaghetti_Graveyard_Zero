#include "engine/logic/bbFlag.h"
#include "engine/includes/CSFML.h"
#include "engine/user_input/bbInput.h"
#include "engine/logic/bbTerminal.h"
#include "engine/dumbserver/bbDumbServer.h"


extern bbDumbServer *testServer;
extern U64 testMapTime;

bbFlag bbInput_new(bbInput* input, sfRenderWindow* window, bbMouse*
mouse, bbWidgets* widgets){

    input->mouse = mouse;
    input->widgets = widgets;

    char* keymap;

    keymap = input->keymap_lowercase;
    for (int i = 0; i < sfKeyCount; i++)
    {
        keymap[i] = 0;
    }

    keymap[sfKeyA] = 'a';
    keymap[sfKeyB] = 'b';
    keymap[sfKeyC] = 'c';
    keymap[sfKeyD] = 'd';
    keymap[sfKeyE] = 'e';
    keymap[sfKeyF] = 'f';
    keymap[sfKeyG] = 'g';
    keymap[sfKeyH] = 'h';
    keymap[sfKeyI] = 'i';
    keymap[sfKeyJ] = 'j';
    keymap[sfKeyK] = 'k';
    keymap[sfKeyL] = 'l';
    keymap[sfKeyM] = 'm';
    keymap[sfKeyN] = 'n';
    keymap[sfKeyO] = 'o';
    keymap[sfKeyP] = 'p';
    keymap[sfKeyQ] = 'q';
    keymap[sfKeyR] = 'r';
    keymap[sfKeyS] = 's';
    keymap[sfKeyT] = 't';
    keymap[sfKeyU] = 'u';
    keymap[sfKeyV] = 'v';
    keymap[sfKeyW] = 'w';
    keymap[sfKeyX] = 'x';
    keymap[sfKeyY] = 'y';
    keymap[sfKeyZ] = 'z';

    keymap = input->keymap_uppercase;
    for (int i = 0; i < sfKeyCount; i++)
    {
        keymap[i] = 0;
    }

    keymap[sfKeyA] = 'A';
    keymap[sfKeyB] = 'B';
    keymap[sfKeyC] = 'C';
    keymap[sfKeyD] = 'D';
    keymap[sfKeyE] = 'E';
    keymap[sfKeyF] = 'F';
    keymap[sfKeyG] = 'G';
    keymap[sfKeyH] = 'H';
    keymap[sfKeyI] = 'I';
    keymap[sfKeyJ] = 'J';
    keymap[sfKeyK] = 'K';
    keymap[sfKeyL] = 'L';
    keymap[sfKeyM] = 'M';
    keymap[sfKeyN] = 'N';
    keymap[sfKeyO] = 'O';
    keymap[sfKeyP] = 'P';
    keymap[sfKeyQ] = 'Q';
    keymap[sfKeyR] = 'R';
    keymap[sfKeyS] = 'S';
    keymap[sfKeyT] = 'T';
    keymap[sfKeyU] = 'U';
    keymap[sfKeyV] = 'V';
    keymap[sfKeyW] = 'W';
    keymap[sfKeyX] = 'X';
    keymap[sfKeyY] = 'Y';
    keymap[sfKeyZ] = 'Z';

    return Success;
}

bbFlag bbInput_poll(bbInput* input, sfRenderWindow* window){
    sfEvent event;
    sfBool flag;

    input->mouse->rightChanged = false;
    input->mouse->leftChanged = false;
    while (1) {
        flag = sfRenderWindow_pollEvent(window, &event);
        if (flag == sfFalse) return Continue;
        switch (event.type)
        {
        case sfEvtClosed: return Break;

        case sfEvtMouseMoved:
        case sfEvtMouseButtonPressed:
        case sfEvtMouseButtonReleased:{

            bbMouse_Event(input->mouse, &event);
            break;
        }

        case sfEvtKeyPressed:{

            bbWidgets* widgets = input->widgets;
            bbWidget* widget = widgets->command;

            sfKeyCode keyCode = event.key.code;
            char key;
                if (event.key.shift == sfTrue)
                {
                    key = input->keymap_uppercase[keyCode];
                    if (key != 0)
                    {
                        bbWidget_onCommand(widget,widgets, bbWC_putChar, &key);
                    }
                } else {
                    key = input->keymap_lowercase[keyCode];
                    if (key != 0)
                    {
                        bbWidget_onCommand(widget,widgets, bbWC_putChar, &key);
                    }
                }

                //special character
            if (key == 0)
            {
                if (keyCode == sfKeyReturn)
                {
                    bbWidget_onCommand(widgets->prompt,widgets, bbWC_putStr, widgets->command->typeData.textBox.string);
                    bbDumbServer_netSend(testServer, widgets->command->typeData.textBox.string, testMapTime);
                    bbWidget_onCommand(widgets->command, widgets,bbWC_setStr, "");
                }
            }

            break;
        }
        case sfEvtKeyReleased:
        case sfEvtTextEntered:
            break;
        default:{
            bbDebug("input not recognised\n");
        }

        }

    }
}