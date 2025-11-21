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

typedef bbFlag bbSpell_Constructor(/*args*/);
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

typedef struct {
    bbVPool* pool;
    bbDictionary* spellCodes;
    bbSpellFunctions functions;

    bbWidget* command;
} bbSpells;

bbFlag bbSpell_new(/*args*/);

bbFlag bbSpell_setActive (bbPool_Handle spellHandle, bbSpells* spells);
bbFlag bbSpell_setInactive (bbPool_Handle spellHandle, bbSpells* spells);

//receive str from text input
bbFlag bbSpell_receiveStr(bbPool_Handle spellHandle, bbSpells* spells,
                      bbPool_Handle str);

bbFlag bbSpell_receiveClick(bbPool_Handle spellHandle, bbSpells* spells,
                            bbMapCoords coords);

bbFlag bbSpells_init(bbSpells* self);
bbFlag bbSpellsFunctions_add(bbSpellFunctions* functions,
                             bbSpellFunctionType type, void* fnPointer,
                             char* key);
bbFlag bbSpellFunctions_populate(bbSpellFunctions* functions);
I32 bbSpells_getInt(/*args*/);

#endif BBSPELL_H