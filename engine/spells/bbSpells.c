#include "engine/spells/bbSpell.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbTerminal.h"

bbFlag bbSpells_new(bbSpells** self){
    I32 magic_number = 256;

    bbSpells* spells = calloc(1, sizeof(bbSpells));

    bbSpellFunctions* functions = &spells->functions;
    //sizeof (bbSpell_Constructor)?
    functions->Constructors = calloc(magic_number, sizeof(U64));
    bbAssert(functions->Constructors != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Constructor_dict, magic_number);
    functions->Constructor_available = 0;

    //sizeof (bbSpell_SetActive)?
    functions->SetActive = calloc(magic_number, sizeof(U64));
    bbAssert(functions->SetActive != NULL, "bad calloc\n");
    bbDictionary_new(&functions->SetActive_dict, magic_number);
    functions->SetActive_available = 0;

    //sizeof (bbSpell_SetInactive)?
    functions->SetInactive = calloc(magic_number, sizeof(U64));
    bbAssert(functions->SetInactive != NULL, "bad calloc\n");
    bbDictionary_new(&functions->SetInactive_dict, magic_number);
    functions->SetInactive_available = 0;

    //sizeof (bbSpell_ReceiveStr)?
    functions->ReceiveStr = calloc(magic_number, sizeof(U64));
    bbAssert(functions->ReceiveStr != NULL, "bad calloc\n");
    bbDictionary_new(&functions->ReceiveStr_dict, magic_number);
    functions->ReceiveStr_available = 0;

    //sizeof (bbSpell_ReceiveClick)?
    functions->ReceiveClick = calloc(magic_number, sizeof(U64));
    bbAssert(functions->ReceiveClick != NULL, "bad calloc\n");
    bbDictionary_new(&functions->ReceiveClick_dict, magic_number);
    functions->ReceiveClick_available = 0;

    bbSpells_populate(spells);
    *self = spells;

    return Success;
}