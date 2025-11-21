#include "engine/logic/bbFlag.h"
#include "engine/spells/bbSpell.h"



bbFlag bbSpell_new(bbSpell** self, bbSpells* spells, char* key){
    bbSpell_Constructor* function;
    bbSpellFunctions_getFunction((void**)&function, &spells->functions,
                                 SpellConstructor,key);
    return function(self, spells);

}