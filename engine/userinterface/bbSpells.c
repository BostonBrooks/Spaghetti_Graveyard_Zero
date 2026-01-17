#include "engine/logic/bbBloatedPool.h"
#include "engine/userinterface/bbSpell.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbTerminal.h"

bbFlag bbSpells_init(bbSpells* spells){
    I32 magic_number = nextPrime(256);

    bbVPool_newBloated(&spells->pool, sizeof(bbSpell), 1024, 1024);

    bbDictionary_new(&spells->spellCodes, magic_number);
    bbSpellFunctions* functions = &spells->functions;
    //sizeof (bbSpell_Constructor)?
    functions->Constructors = calloc(magic_number, sizeof(U64));
    bbAssert(functions->Constructors != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Constructor_dict, magic_number);
    functions->Constructor_available = 0;


    functions->Destructors = calloc(magic_number, sizeof(U64));
    bbAssert(functions->Destructors != NULL, "bad calloc\n");
    bbDictionary_new(&functions->Destructor_dict, magic_number);
    functions->Destructor_available = 0;

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
    I32 max_spells = 256;
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
            //functions->SetActive[available] = fnPointer;
            handle.u64 = 0; //available;
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
            //functions->ReceiveClick[available] = fnPointer;
            handle.u64 = 0;  //available;
            bbDictionary_add(functions->ReceiveClick_dict,key,handle);
            return Success;



    }
}


/*
SpellConstructor,
SpellDestructor,
SpellSetActive,
SpellSetInactive,
SpellReceiveStr,
SpellReceiveClick
*/

I32 bbSpellFunctions_getInt(bbSpellFunctions* functions, bbSpellFunctionType
fnType, char* key){
    bbDictionary* dict;
    switch (fnType){
        case SpellConstructor:
            dict = functions->Constructor_dict;
            break;
        case SpellDestructor:
            dict = functions->Destructor_dict;
            break;
        case SpellSetActive:
            dict = functions->SetActive_dict;
            break;
        case SpellSetInactive:
            dict = functions->SetInactive_dict;
            break;
        case SpellReceiveStr:
            dict = functions->ReceiveStr_dict;
            break;
        case SpellReceiveClick:
            dict = functions->ReceiveClick_dict;
            break;
    }

    bbPool_Handle handle;
    bbDictionary_lookup(dict,key,&handle);
    return handle.u64;
}

bbFlag bbSpellFunctions_getFunction(void** function, bbSpellFunctions*
functions, bbSpellFunctionType fnType, char* key){
    bbPool_Handle handle;

    switch (fnType){
        case SpellConstructor:
            bbDictionary_lookup(functions->Constructor_dict,key,&handle);
            *function = functions->Constructors[handle.u64];
            return Success;
        case SpellDestructor:
            bbDictionary_lookup(functions->Destructor_dict,key,&handle);
            *function = functions->Destructors[handle.u64];
            return Success;
        case SpellSetActive:
            bbDictionary_lookup(functions->SetActive_dict,key,&handle);
            *function = NULL; //functions->SetActive[handle.u64];
            return Success;
        case SpellSetInactive:
            bbDictionary_lookup(functions->SetInactive_dict,key,&handle);
            *function = functions->SetInactive[handle.u64];
            return Success;
        case SpellReceiveStr:
            bbDictionary_lookup(functions->ReceiveStr_dict,key,&handle);
            *function = functions->ReceiveStr[handle.u64];
            return Success;
        case SpellReceiveClick:
            bbDictionary_lookup(functions->ReceiveClick_dict,key,&handle);
            *function = NULL; //functions->ReceiveClick[handle.u64];
            return Success;
    }

}