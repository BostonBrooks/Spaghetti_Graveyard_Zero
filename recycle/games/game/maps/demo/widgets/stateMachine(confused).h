



#include "recycle/headers/bbPrintf.h"
#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbMap.h"
#include "recycle/headers/bbCommands.h"
#include "recycle/headers/bbString.h"
#include "recycle/headers/bbFlags.h"
#define f_SpellInactive 0  //waiting to be clicked
#define f_SpellCoolDown 1 //waiting for countdown
#define f_SpellPrompt   2  // waiting for user to enter response

//type / to select spell or click spell button
    //current spell becomes inactive,
    //new spell becomes current spell
//if spell is on a cooldown, wait until end of cooldown
//prompt user to answer maths question
//spawn a balloon

//if user presses enter, prompt again



// if at any time the user clicks a spell button, activate this spell

//if the user at any time types /, the spell selector becomes current spell.
    //spell selector waits for user to type a code and hit enter
    //activates new spell
    //if no code entered before hitting enter, activate previous spell



// if a spell is activated, wait for countdown to end
    //prompt user to answer question
    //if answer is correct, spawn balloon, reset countdown/cooldown

I32 bbWidgetCommand_spell(bbWidget* widget, void* data){
    bbCommandEmpty* commandEmpty = data;

    switch (commandEmpty->type) {
        case f_CommandSetActive: {

            if (g_Game->m_Maps[widget->p_Node.p_Pool.Self]->misc.m_MapTime > widget->m_CoolDownEnd){

            }

            break;
        }
        case f_CommandSetInactive: {
            widget->m_State = f_SpellInactive;
            break;
        }
        case f_CommandPutStr: {
            if(widget->m_State == f_SpellPrompt){
                bbCommandPutStr* commandPutStr = data;
                //strcmp(widget->m_ExpectedString, commandPutStr->m_str);

               // if correct spawn balloon
                //self.set_inactive
                //selector.set_active
            }
        }


    }
}