#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbSpell.h"



bbFlag bbSpell_new(bbSpell** self, bbSpells* spells, char* key){
    bbSpell_Constructor* function;
    bbSpellFunctions_getFunction((void**)&function, &spells->functions,
                                 SpellConstructor,key);
    return function(self, (void*)spells);

}

bbFlag bbSpell_setInactive (bbSpell* spell, bbSpells* spells)
{
    //TODO
    bbHere();
    return Success;
}

/*
bbFlag bbSpell_setActive(bbSpell* spell, void* Spells, bbDummySender* server, U64 gameTime)
{

    bbSpells* spells = (bbSpells*)Spells;
    I32 functionInt = spell->fTable.SetActive;
    bbSpell_SetActive* function = spells->functions.SetActive[functionInt];
    return function(spell, (void*)spells, server, gameTime);
}*/

/*
bbFlag bbSpell_setActive_Key(char* Key, void* Spells, bbDummySender* server,
                             U64 gameTime){
    bbDebug("Set active spell: %s\n", Key);
    bbSpells* spells = (bbSpells*)Spells;
    bbPool_Handle handle;
    bbFlag flag = bbDictionary_lookup(spells->spellCodes, Key, &handle);

    if (flag == None) {
        bbDebug("Spell not available\n");
        return Continue;
    }
    bbSpell* spell;
    bbVPool_lookup(spells->pool, (void**)&spell, handle);
    bbSpell_setActive(spell, Spells, server, gameTime);

    return Success;
}

*/
bbFlag bbSpell_receiveStr(bbSpell* spell, void* Spells, char* answer)
{
    bbSpells* spells = (bbSpells*)Spells;
    I32 functionInt = spell->fTable.ReceiveStr;
    bbSpell_ReceiveStr* function = spells->functions.ReceiveStr[functionInt];
    return function(spell,Spells, answer);
}
/*
bbFlag bbSpell_receiveClick(bbSpell* spell, void* Spells, bbMapCoords MC, bbDummySender* server, U64 gameTime)
{
    bbSpells* spells = (bbSpells*)Spells;
    I32 functionInt = spell->fTable.ReceiveClick;
    bbSpell_ReceiveClick* function = spells->functions.ReceiveClick[functionInt];
    return function(spell, Spells, MC, server, gameTime);
}
*/