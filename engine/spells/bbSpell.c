#include "engine/logic/bbFlag.h"
#include "engine/spells/bbSpell.h"



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

bbFlag bbSpell_setActive(bbSpell* spell, void* Spells, bbDumbServer* server, U64 gameTime)
{
    bbSpells* spells = (bbSpells*)Spells;
    I32 functionInt = spell->fTable.SetActive;
    bbSpell_SetActive* function = spells->functions.SetActive[functionInt];
    return function(spell, (void*)spells, Spells, gameTime);
}



bbFlag bbSpell_receiveStr(bbSpell* spell, void* Spells, char* answer)
{
    bbSpells* spells = (bbSpells*)Spells;
    I32 functionInt = spell->fTable.ReceiveStr;
    bbSpell_ReceiveStr* function = spells->functions.ReceiveStr[functionInt];
    return function(spell,Spells, answer);
}

bbFlag bbSpell_receiveClick(bbSpell* spell, void* Spells, bbMapCoords MC, bbDumbServer* server, U64 gameTime)
{
    bbSpells* spells = (bbSpells*)Spells;
    I32 functionInt = spell->fTable.ReceiveClick;
    bbSpell_ReceiveClick* function = spells->functions.ReceiveClick[functionInt];
    return function(spell, Spells, MC, server, gameTime);
}