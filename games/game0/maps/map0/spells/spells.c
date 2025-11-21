#include "engine/logic/bbFlag.h"
#include "engine/spells/bbSpell.h"

bbFlag bbSpell_NULLConstructor(bbSpell** self, bbSpells* spells){
    bbDebug("Execute virtual function\n");

    bbSpell* spell; bbPool_Handle spellHandle;
    bbVPool_alloc(spells->pool, (void**)&spell);

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

bbFlag bbSpell_NULLDestructor(/*args*/){
    bbDebug("Execute virtual function\n");
    return Success;
}

bbFlag bbSpell_NULLSetActive(/*args*/){
    bbDebug("Execute virtual function\n");
    return Success;
}

bbFlag bbSpell_NULLSetInactive(/*args*/){
    bbDebug("Execute virtual function\n");
    return Success;
}

bbFlag bbSpell_NULLReceiveStr(/*args*/){
    bbDebug("Execute virtual function\n");
    return Success;
}

bbFlag bbSpell_NULLReceiveClick(/*args*/){
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
                          bbSpell_NULLConstructor,"NULL");
    bbSpellsFunctions_add(functions, SpellDestructor,
                          bbSpell_NULLDestructor,"NULL");
    bbSpellsFunctions_add(functions, SpellSetActive,
                          bbSpell_NULLSetActive,"NULL");
    bbSpellsFunctions_add(functions, SpellSetInactive,
                          bbSpell_NULLSetInactive,"NULL");
    bbSpellsFunctions_add(functions, SpellReceiveStr,
                          bbSpell_NULLReceiveStr,"NULL");
    bbSpellsFunctions_add(functions, SpellReceiveClick,
                          bbSpell_NULLReceiveClick,"NULL");
    return Success;
}