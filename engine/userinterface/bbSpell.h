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
#include "engine/userinterface/bbWidget.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/userinterface/bbSpell.h"

typedef enum
{
    SpellConstructor,
    SpellDestructor,
    SpellSetActive,
    SpellSetInactive,
    SpellReceiveStr,
    SpellReceiveClick
} bbSpellFunctionType;

typedef enum
{
    SpellInactive,
    SpellWaitingForAnswer,
    SpellWaitingForClick,
} bbSpellState;

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
    bbSpellState state;
    bbWidget* spellButton;
    I32 spellIcon;

} bbSpell;

typedef bbFlag bbSpell_Constructor(bbSpell** self, void* spells);
typedef bbFlag bbSpell_Destructor(bbSpell** self, void* spells);
//typedef bbFlag bbSpell_SetActive(bbSpell* spell, void* Spells, bbDummySender* server, U64 gameTime);
typedef bbFlag bbSpell_SetActive(bbSpell* spell, void* Spells, U64 gameTime);
typedef bbFlag bbSpell_SetInactive(bbSpell** self, void* spells);
typedef bbFlag bbSpell_ReceiveStr(bbSpell* self, void* spells, char* answer);
//typedef bbFlag bbSpell_ReceiveClick(bbSpell* spell, void* Spells, bbMapCoords MC, bbDummySender* server, U64 gameTime);
typedef bbFlag bbSpell_ReceiveClick(bbSpell* spell, void* Spells, bbMapCoords MC, U64 gameTime);

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
    bbSpell* currentSpell;
    bbWidget* command;
} bbSpells;

bbFlag bbSpell_new(bbSpell** self, bbSpells* Spells, char* key);

//bbFlag bbSpell_setActive (bbSpell* self, void* spells, bbDummySender* server, U64 gameTime);
bbFlag bbSpell_setInactive (bbSpell* spell, bbSpells* spells);
//bbFlag bbSpell_setActive_Key(char* Key, void* Spells, bbDummySender* server,U64 gameTime);

//receive str from text input
bbFlag bbSpell_receiveStr(bbSpell* spell, void* spells, char* str);

//bbFlag bbSpell_receiveClick(bbSpell* spell, void* Spells, bbMapCoords MC, bbDummySender* server, U64 gameTime);

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

#endif //BBSPELL_H