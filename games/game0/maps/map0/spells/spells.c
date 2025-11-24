#include "engine/logic/bbFlag.h"
#include "engine/spells/bbSpell.h"
#include "games/game0/maps/map0/spells/spell1.h"

bbFlag bbSpell_NULL_Constructor(bbSpell** self, bbSpells* spells){
    bbDebug("Execute virtual function\n");

    bbSpell* spell; bbPool_Handle spellHandle;
    bbVPool_alloc(spells->pool, (void**)&spell);

    spell->spellIcon = 102;

    spell->fTable.Constructor =
            bbSpellFunctions_getInt(&spells->functions,
                                    SpellConstructor, "NULL");

    spell->fTable.Destructor =
            bbSpellFunctions_getInt(&spells->functions,
                                    SpellDestructor, "NULL");

    spell->fTable.SetActive =
            bbSpellFunctions_getInt(&spells->functions,
                                    SpellSetActive, "NULL");

    spell->fTable.SetInactive =
            bbSpellFunctions_getInt(&spells->functions,
                                    SpellSetInactive, "NULL");

    spell->fTable.ReceiveStr =
            bbSpellFunctions_getInt(&spells->functions,
                                    SpellReceiveStr, "NULL");

    spell->fTable.ReceiveClick =
            bbSpellFunctions_getInt(&spells->functions,
                                    SpellReceiveClick, "NULL");

    *self = spell;
    return Success;
}

bbFlag bbSpell_NULL_Destructor(/*args*/){
    bbDebug("Execute virtual function\n");
    return Success;
}

bbFlag bbSpell_NULL_SetActive(/*args*/){
    bbDebug("Execute virtual function\n");
    return Success;
}

bbFlag bbSpell_NULL_SetInactive(/*args*/){
    bbDebug("Execute virtual function\n");
    return Success;
}

bbFlag bbSpell_NULL_ReceiveStr(/*args*/){
    bbDebug("Execute virtual function\n");
    return Success;
}

bbFlag bbSpell_NULL_ReceiveClick(/*args*/){
    bbDebug("Execute virtual function\n");
    return Success;
}
/*
 *     SpellConstructor,
    SpellDestructor,
    SpellSetActive,
    SpellSetInactive,
    SpellReceiveStr,
    SpellReceiveClick
 */


bbFlag bbSpellFunctions_populate(bbSpellFunctions* functions){

    bbSpellsFunctions_add(functions, SpellConstructor,
                          bbSpell_NULL_Constructor,"NULL");
    bbSpellsFunctions_add(functions, SpellDestructor,
                          bbSpell_NULL_Destructor,"NULL");
    bbSpellsFunctions_add(functions, SpellSetActive,
                          bbSpell_NULL_SetActive,"NULL");
    bbSpellsFunctions_add(functions, SpellSetInactive,
                          bbSpell_NULL_SetInactive,"NULL");
    bbSpellsFunctions_add(functions, SpellReceiveStr,
                          bbSpell_NULL_ReceiveStr,"NULL");
    bbSpellsFunctions_add(functions, SpellReceiveClick,
                          bbSpell_NULL_ReceiveClick,"NULL");

    bbSpellsFunctions_add(functions, SpellConstructor,
                      bbSpell_Crossbow_Constructor,"CROSSBOW");
    bbSpellsFunctions_add(functions, SpellDestructor,
                          bbSpell_Crossbow_Destructor,"CROSSBOW");
    bbSpellsFunctions_add(functions, SpellSetActive,
                          bbSpell_Crossbow_SetActive,"CROSSBOW");
    bbSpellsFunctions_add(functions, SpellSetInactive,
                          bbSpell_Crossbow_SetInactive,"CROSSBOW");
    bbSpellsFunctions_add(functions, SpellReceiveStr,
                          bbSpell_Crossbow_ReceiveStr,"CROSSBOW");
    bbSpellsFunctions_add(functions, SpellReceiveClick,
                          bbSpell_Crossbow_ReceiveClick,"CROSSBOW");
    return Success;
}