/**
 * @file
 * @brief bbDictionary stores a number of key-value pairs for fast lookup.
 * Keys should be up to 32 characters. dictionary can contain up to 10000 members
 */

#ifndef BBDICTIONARY_H
#define BBDICTIONARY_H

#include "engine/logic/bbIntTypes.h"

#define KEY_LENGTH 32

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
	I32 m_Value;

} bbDictionary_entry;

typedef struct {

	I32 m_NumBins;
	bbDictionary_entry* m_Pool[100];
	bbDictionary_bin m_Available;
	bbDictionary_bin m_Bins[];

} bbDictionary;

/// create a new dictionary
I32 bbDictionary_new(bbDictionary** dict, I32 n_bins);
/// delete an existing dictionary
I32 bbDictionary_delete(bbDictionary* dict);
/// add key/value pair to dictionary and overwrite if duplicate
I32 bbDictionary_add(bbDictionary* dict, char* key, int value);
/// remove a key from dictionary
I32 bbDictionary_remove(bbDictionary* dict, char* key);
/// lookup a key in dictionary
I32 bbDictionary_lookup(bbDictionary* dict, char* key);
/// remove all key/value pairs in dictionary
I32 bbDictionary_clear(bbDictionary* dict);
/// print all data in dictionary
I32 bbDictionary_print(bbDictionary* dict);


#endif //BBDICTIONARY_H
