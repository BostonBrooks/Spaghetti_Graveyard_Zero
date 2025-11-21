#include "engine/spells/bbSpell.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbTerminal.h"

bbFlag bbSpells_init(bbSpells* spells){
    I32 magic_number = 256;

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

    bbSpellFunctions_populate(&spells->functions);


    return Success;
}
/*
SpellConstructor,
SpellDestructor,
SpellSetActive,
SpellSetInactive,
SpellReceiveStr,
SpellReceiveClick
*/
bbFlag bbSpellsFunctions_add(bbSpellFunctions* functions, bbSpellFunctionType
type, void* fnPointer, char* key)
{
    U32 available;
    bbPool_Handle handle;
    I32 max_spells;
    switch (type)
    {
        case SpellConstructor:
            available = functions->Constructor_available++;
            bbAssert(available<max_spells, "out of bounds error\n");
            functions->Constructors[available] = fnPointer;
            handle.u64 = available;
            bbDictionary_add(functions->Constructor_dict,key,handle);
            return Success;

        case SpellDestructor:
            available = functions->Destructor_available++;
            bbAssert(available<max_spells, "out of bounds error\n");
            functions->Destructors[available] = fnPointer;
            handle.u64 = available;
            bbDictionary_add(functions->Destructor_dict,key,handle);
            return Success;

        case SpellSetActive:
            available = functions->SetActive_available++;
            bbAssert(available<max_spells, "out of bounds error\n");
            functions->SetActive[available] = fnPointer;
            handle.u64 = available;
            bbDictionary_add(functions->SetActive_dict,key,handle);
            return Success;

        case SpellSetInactive:
            available = functions->SetInactive_available++;
            bbAssert(available<max_spells, "out of bounds error\n");
            functions->SetInactive[available] = fnPointer;
            handle.u64 = available;
            bbDictionary_add(functions->SetInactive_dict,key,handle);
            return Success;

        case SpellReceiveStr:
            available = functions->ReceiveStr_available++;
            bbAssert(available<max_spells, "out of bounds error\n");
            functions->ReceiveStr[available] = fnPointer;
            handle.u64 = available;
            bbDictionary_add(functions->ReceiveStr_dict,key,handle);
            return Success;

        case SpellReceiveClick:
            available = functions->ReceiveClick_available++;
            bbAssert(available<max_spells, "out of bounds error\n");
            functions->ReceiveClick[available] = fnPointer;
            handle.u64 = available;
            bbDictionary_add(functions->ReceiveClick_dict,key,handle);
            return Success;



    }
}