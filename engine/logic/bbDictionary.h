/**
 * @file
 * @brief bbDictionary stores a number of key-value pairs for fast lookup.
 * Keys should be up to 32 characters. dictionary can contain up to 10000 members
 */

#ifndef BBDICTIONARY_H
#define BBDICTIONARY_H

#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbPoolHandle.h"
#include "engine/logic/bbFlag.h"
#include "games/game0/bbConstants.h"


typedef struct {
	I32 Head;
	I32 Tail;
} bbDictionary_bin;

typedef struct {

	I32 m_Self;
	I32 m_Prev;
	I32 m_Next;
	I32 m_InUse;

	char m_Key[KEY_LENGTH];
	bbPool_Handle m_Value;

} bbDictionary_entry;

typedef struct {

	I32 m_NumBins;
	bbDictionary_entry* m_Pool[100];
	bbDictionary_bin m_Available;
	bbDictionary_bin m_Bins[];

} bbDictionary;

/// create a new dictionary
bbFlag bbDictionary_new(bbDictionary** dict, I32 n_bins);
/// delete an existing dictionary
bbFlag bbDictionary_delete(bbDictionary* dict);
/// add key/value pair to dictionary and overwrite if duplicate
bbFlag bbDictionary_add(bbDictionary* dict, char* key, bbPool_Handle value);
/// remove a key from dictionary
bbFlag bbDictionary_remove(bbDictionary* dict, char* key);
/// get value from key
bbFlag bbDictionary_lookup(bbDictionary* dict, char* key, bbPool_Handle* value);

/// remove all key/value pairs in dictionary
bbFlag bbDictionary_clear(bbDictionary* dict);
/// print all data in dictionary
bbFlag bbDictionary_print(bbDictionary* dict);


#endif //BBDICTIONARY_H
