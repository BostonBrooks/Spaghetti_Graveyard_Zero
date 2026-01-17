/**Usual Program Flow:
 *
 *bbSpell_setActive:
 *  notify server (So the player character can show the spell1 in hand)
 *  prompt player to answer maths question
 *
 *bbSpell_ReceiveStr:
 *  player answers maths question,
 *  if correct, spell1 is armed
 *  otherwise, prompt player to enter maths question
 *
 *bbSpell_ReceivedClick:
 *  request launch of spell1 bolt from server
 *  prompt player to answer maths question
*/

#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbSpell.h"

#include "engine/data/bbHome.h"
#include <string.h>

/*
typedef bbFlag bbSpell_Constructor(bbSpell** self, void* spells);
typedef bbFlag bbSpell_Destructor(bbSpell** self, void* spells);
typedef bbFlag bbSpell_SetActive(bbSpell* self, void* spells, bbDummySender* server, U64 gameTime);
typedef bbFlag bbSpell_SetInactive(bbSpell* self, void* spells);
typedef bbFlag bbSpell_ReceiveStr(bbSpell* self, void* spells, char* answer);
typedef bbFlag bbSpell_ReceiveClick(bbSpell* self, void* spells, bbMapCoords MC);
*/

bbFlag bbSpell_Spell3_Constructor(bbSpell** self, void* Spells)
{
    bbSpells* spells = (bbSpells*)Spells;
    bbSpell* spell; bbPool_Handle spellHandle;
    bbVPool_alloc(spells->pool, (void**)&spell);

    bbVPool_reverseLookup(spells->pool, spell, &spellHandle);
    bbDictionary_add(spells->spellCodes, "SPELL3", spellHandle);

    spell->spellIcon = 101+3;

    spell->fTable.Constructor =
            bbSpellFunctions_getInt(&spells->functions,
                                    SpellConstructor, "SPELL3");

    spell->fTable.Destructor =
            bbSpellFunctions_getInt(&spells->functions,
                                    SpellDestructor, "SPELL3");

    spell->fTable.SetActive =
            bbSpellFunctions_getInt(&spells->functions,
                                    SpellSetActive, "SPELL3");

    spell->fTable.SetInactive =
            bbSpellFunctions_getInt(&spells->functions,
                                    SpellSetInactive, "SPELL3");

    spell->fTable.ReceiveStr =
            bbSpellFunctions_getInt(&spells->functions,
                                    SpellReceiveStr, "SPELL3");

    spell->fTable.ReceiveClick =
            bbSpellFunctions_getInt(&spells->functions,
                                    SpellReceiveClick, "SPELL3");

    spell->state = SpellInactive;

    *self = spell;
    return Success;
}

bbFlag bbSpell_Spell3_Destructor(bbSpell** self, void* spells)
{
    return Success;
}
/*
bbFlag bbSpell_Spell3_SetActive(bbSpell* spell, void* Spells, bbDummySender* server, U64 gameTime)
{
    bbHere();
    bbSpells* spells = (bbSpells*)Spells;
    //TODO roll out to calling function
    //bbSpell_setInactive(spells->currentSpell, spells);
    spells->currentSpell = spell;


    //bbPool_Handle icon = spell->spellButton->frames->handle; //error undefined
    bbPool_Handle icon; icon.u64 = spell->spellIcon;
    bbDummySender_setActiveSpell(server, icon, gameTime);

    I32 x = rand() % 20;
    I32 y = 1+rand() % 19;

    char promptStr[64]; bbPool_Handle handle;
    sprintf(promptStr, "what is %d / %d?\n", x*y, y);

    handle.ptr = promptStr;
    bbWidget_onCommand(home.private.widgets.prompt,&home.private.widgets,
                       bbWC_setStr,
                       handle);

    spell->answer = x;
    spell->state = SpellWaitingForAnswer;

    return Success;
}*/
bbFlag bbSpell_Spell3_SetInactive(bbSpell* self, void* spells)
{
    self->state = SpellInactive;
    return Success;
}

bbFlag bbSpell_Spell3_ReceiveStr(bbSpell* spell, void* Spells, char* answer)
{
    if (spell->state != SpellWaitingForAnswer) return Continue;
    bbSpells* spells = (bbSpells*)Spells;

    I32 len = strlen(answer);
    char digits[] = "0123456789";
    I32 int_len = strspn(answer, digits);

    if(len != int_len) return Continue;
    I32 answerInt = atoi(answer);
    if (answerInt != spell->answer) return Continue;

    char promptStr[64]; bbPool_Handle handle;
    sprintf(promptStr, "Correct!\nClick to fire spell3\n");

    handle.ptr = promptStr;
    bbWidget_onCommand(home.private.widgets.prompt,&home.private.widgets,
                       bbWC_setStr,
                       handle);

    spell->state = SpellWaitingForClick;

    return Success;
}

/*
bbFlag bbSpell_Spell3_ReceiveClick(bbSpell* spell, void* Spells, bbMapCoords MC, bbDummySender* server, U64 gameTime)
{
    if (spell->state != SpellWaitingForClick) return Continue;
    bbSpells* spells = (bbSpells*)Spells;
    //bbDummySender_castSpell(server, MC, gameTime);
    I32 x = rand() % 20;
    I32 y = rand() % 20;

    char promptStr[64]; bbPool_Handle handle;
    sprintf(promptStr, "what is %d x %d\n", x, y);

    handle.ptr = promptStr;
    bbWidget_onCommand(home.private.widgets.prompt,&home.private.widgets,
                       bbWC_setStr,
                       handle);

    spell->answer = x * y;
    spell->state = SpellWaitingForAnswer;

    return Success;

}*/