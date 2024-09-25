#include "headers/bbCharacter.h"
#include "headers/bbWidget.h"
#include "headers/bbGame.h"
#include "headers/bbCommands.h"
#include "headers/bbIntTypes.h"

I32 Event_inputChar(char character, I32 map){

    bbWidget* prompt = g_Game->m_Maps[map]->m_Widgets->m_Prompt;
/*
    bbWidget* spellbar = g_Game->m_Maps[map]->m_Widgets->m_SpellBar;
    if (character == '/') {

        bbCommandStr cmd;
        cmd.type = f_PromptSetQuery;
        cmd.m_str = "Did you just type \'/\'?";
        bbWidget_onCommand(&cmd, prompt);

        bbCommandEmpty cmd2;
        cmd2.type = f_SpellEscape;

        bbWidget_onCommand(&cmd2, spellbar);

        return f_Success;
    }

    if(character == '\n'){
        bbCommandStr cmd;
        char buffer[128];
        cmd.type = f_PromptReturnAnswer;
        cmd.m_str = buffer;
        bbWidget_onCommand(&cmd, prompt);

        printf("You entered %s\n", cmd.m_str);

        bbCommandStr cmd2;
        cmd2.type = f_SpellAnswer;
        cmd2.m_str = buffer;

        bbWidget_onCommand(&cmd2, spellbar);

        bbCommandStr cmd3;
        cmd3.type = f_PromptSetQuery;
        cmd3.m_str = "waka waka waka waka waka waka?";
        bbWidget_onCommand(&cmd3, prompt);

        bbCommandStr cmd4;
        char buffer2[128];
        sprintf(buffer2, "\n you entered %s", cmd.m_str);
        cmd4.type = f_PromptAddDialogue;
        cmd4.m_str = buffer2;
        bbWidget_onCommand(&cmd4, prompt);



        return f_Success;


    }
*/
    bbCommandChar cmd2;
    cmd2.type = f_PromptAddChar;
    cmd2.m_char= character;
    bbWidget_onCommand(&cmd2, prompt);

    return f_Success;

}
