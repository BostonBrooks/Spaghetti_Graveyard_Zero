///bbSpell receives input from player and sends messages to the server to
/// effect the game world

#ifndef BBSPELL_H
#define BBSPELL_H

#include "engine/logic/bbFlag.h"
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbVPool.h"
#include "engine/logic/bbLeanPool.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbDictionary.h"
#include "engine/widgets/bbWidget.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/spells/bbSpell.h"

typedef enum
{
    SpellConstructor,
    SpellDestructor,
    SpellSetActive,
    SpellSetInactive,
    SpellReceiveStr,
    SpellReceiveClick
} bbSpellFunctionType;

typedef struct {
    I32 Constructor;
    I32 Destructor;
    I32 SetActive;
    I32 SetInactive;
    I32 ReceiveStr;
    I32 ReceiveClick;
} bbSpellFunctionTable;

typedef struct {

    bbSpellFunctionTable fTable;
    I32 answer;
    bbWidget* spellButton;

} bbSpell;

typedef bbFlag bbSpell_Constructor(bbSpell** self, struct bbSpells* spells);
typedef bbFlag bbSpell_Destructor(/*args*/);
typedef bbFlag bbSpell_SetActive(/*args*/);
typedef bbFlag bbSpell_SetInactive(/*args*/);
typedef bbFlag bbSpell_ReceiveStr(/*args*/);
typedef bbFlag bbSpell_ReceiveClick(/*args*/);

typedef struct {
    bbSpell_Constructor** Constructors;
    bbDictionary* Constructor_dict;
    I32 Constructor_available;

    bbSpell_Destructor** Destructors;
    bbDictionary* Destructor_dict;
    I32 Destructor_available;

    bbSpell_SetActive** SetActive;
    bbDictionary* SetActive_dict;
    I32 SetActive_available;

    bbSpell_SetInactive** SetInactive;
    bbDictionary* SetInactive_dict;
    I32 SetInactive_available;

    bbSpell_ReceiveStr** ReceiveStr;
    bbDictionary* ReceiveStr_dict;
    I32 ReceiveStr_available;

    bbSpell_ReceiveClick** ReceiveClick;
    bbDictionary* ReceiveClick_dict;
    I32 ReceiveClick_available;

} bbSpellFunctions;

typedef struct bbSpells{
    bbVPool* pool;
    bbDictionary* spellCodes;
    bbSpellFunctions functions;

    bbWidget* command;
} bbSpells;

bbFlag bbSpell_new(bbSpell** self, bbSpells* Spells, char* key);

bbFlag bbSpell_setActive (bbPool_Handle spellHandle, bbSpells* spells);
bbFlag bbSpell_setInactive (bbPool_Handle spellHandle, bbSpells* spells);

//receive str from text input
bbFlag bbSpell_receiveStr(bbSpell* spell, bbSpells* spells,
                      bbPool_Handle str);

bbFlag bbSpell_receiveClick(bbPool_Handle spellHandle, bbSpells* spells,
                            bbMapCoords coords);

bbFlag bbSpells_init(bbSpells* self);
bbFlag bbSpellsFunctions_add(bbSpellFunctions* functions,
                             bbSpellFunctionType type, void* fnPointer,
                             char* key);
bbFlag bbSpellFunctions_populate(bbSpellFunctions* functions);
I32 bbSpells_getInt(/*args*/);
bbFlag bbSpellFunctions_getFunction(void** function, bbSpellFunctions*
functions, bbSpellFunctionType fnType, char* key);
I32 bbSpellFunctions_getInt(bbSpellFunctions* functions, bbSpellFunctionType
fnType, char* key);

#endif BBSPELL_H