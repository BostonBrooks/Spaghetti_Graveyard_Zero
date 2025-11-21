#include "engine/logic/bbFlag.h"
#include "engine/spells/bbSpell.h"



bbFlag bbSpell_new(bbSpell** self, bbSpells* spells, char* key){
    bbSpell_Constructor* function;
    bbSpellFunctions_getFunction((void**)&function, &spells->functions,
                                 SpellConstructor,key);
    return function(self, spells);

}

bbFlag bbSpell_receiveStr(bbSpell* spell, bbSpells* spells,
                          bbPool_Handle str){

    I32 functionInt = spell->fTable.ReceiveStr;
    bbSpell_ReceiveStr* function = spells->functions.ReceiveStr[functionInt];
    return function();
}