#include <stdlib.h>
#include <string.h>
#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbTerminal.h"
#include "engine/logic/bbScatter.h"
#include "engine/logic/bbPoolHandle.h"

I32 hash(unsigned char *str, I32 n_bins)
{

    U32 hash_value = 5381;
    U32 next;
	I32 i = 0;
	I32 c = str[i];

	while (c != '\0' && c!= '\n') {

        U32 d = scatter[c];
		hash_value = hash_value * 33 + d;
		i++;
		c = str[i];

	}

	hash_value %= n_bins;
	return hash_value;
}

bbFlag bbDictionary_new (bbDictionary** self, I32 n_bins){
	bbDictionary* dict = malloc(sizeof(bbDictionary) + n_bins * sizeof(bbDictionary_bin)); //sizeof (bbDictionary) + 2*sizeof (int) * NUM_BINS;?
	assert( dict!= NULL);
	dict->m_NumBins = n_bins;
	dict->m_Available.Head = f_None;
	dict->m_Available.Tail = f_None;

	for(I32 i = 0; i < n_bins; i++){
		dict->m_Bins[i].Head = f_None;
		dict->m_Bins[i].Tail = f_None;
	}

	for (I32 i = 0; i < 100; i++){
		dict->m_Pool[i] = NULL;
	}

	*self = dict;

	return Success;
}

bbFlag bbDictionary_delete(bbDictionary* dict){
	for (I32 i = 0; i < 100; i++){
		if (dict->m_Pool[i] != NULL) free (dict->m_Pool[i]);
	}
	free(dict);
    return Success;
}

bbFlag bbDictionary_increase(bbDictionary* dict){
	I32 i = 0;
	while (i < 100 && dict->m_Pool[i] != NULL) {
		i++;
	}
	if (i == 100) {
		return Full;
	}

	bbDictionary_entry* entry = calloc(100, sizeof(bbDictionary_entry));
	bbAssert(entry != NULL, "malloc failed\n");
	dict->m_Pool[i] = entry;


	if (dict->m_Available.Head == f_None){
		bbAssert(dict->m_Available.Tail == f_None, "Head/Tail mismatch\n");

		for (I32 l = 0; l < 100; l++){
			dict->m_Pool[i][l].m_Self = i * 100 + l;
			dict->m_Pool[i][l].m_Prev = i * 100 + l - 1;
			dict->m_Pool[i][l].m_Next = i * 100 + l + 1;
			dict->m_Pool[i][l].m_InUse = 0;

		}


		dict->m_Pool[i][0].m_Prev = f_None;
		dict->m_Pool[i][100 - 1].m_Next = f_None;

		dict->m_Available.Head = i * 100;
		dict->m_Available.Tail = (i+1) * 100 - 1;

		return Success;
	}

	bbAssert(0==1, "increasing non-empty pool\n");
}

bbDictionary_entry* bbDictionary_indexLookup(bbDictionary* dict, I32 index){
	I32 level1 = index / 100;
	I32 level2 = index % 100;
	bbDictionary_entry* entry = &dict->m_Pool[level1][level2];
	assert (entry != NULL);
	return entry;
}

I32 bbDictionary_lookupIndex(bbDictionary* dict, char* key){
	I32 hash_value = hash(key, dict->m_NumBins);
	bbDictionary_entry* entry;
	I32 index = dict->m_Bins[hash_value].Head;

	while (index != f_None) {
		entry = bbDictionary_indexLookup(dict, index);
		if(strcmp(key, entry->m_Key) == 0) return index;
		index = entry->m_Next;
	}

	return f_None;
}

bbFlag bbDictionary_lookup(bbDictionary* dict, char* key, bbPool_Handle* value){
	I32 index = bbDictionary_lookupIndex(dict, key);
	if (index == f_None) {
        value->u64 = 0;
		//bbDebug("key not found: %s\n", key);
        return None;
    }
	bbDictionary_entry* entry = bbDictionary_indexLookup(dict, index);
	*value = entry->m_Value;



	return Success;
}

/// get an unused entry from pool
bbDictionary_entry* grab_entry (bbDictionary* dict){
	int* Head = &dict->m_Available.Head;
	int* Tail = &dict->m_Available.Tail;


	if (*Head == f_None){
		bbAssert(*Tail == f_None, "Head/Tail mismatch\n");

		bbDictionary_increase(dict);


	}


	if (*Head == *Tail){
		bbDictionary_entry* entry = bbDictionary_indexLookup(dict, *Head);
		*Head = f_None;
		*Tail = f_None;

		entry->m_Next = f_None;
		entry->m_Prev = f_None;
		entry->m_InUse = 1;

		return entry;
	}

	bbDictionary_entry* entry = bbDictionary_indexLookup(dict, *Head);
	*Head = entry->m_Next;
	bbDictionary_entry* next_entry = bbDictionary_indexLookup(dict, entry->m_Next);
	next_entry->m_Prev = f_None;

	entry->m_Next = f_None;
	entry->m_Prev = f_None;
	entry->m_InUse = 1;

	return entry;
}

bbFlag bbDictionary_add(bbDictionary* dict, char* key, bbPool_Handle value){
	I32 index = bbDictionary_lookupIndex(dict, key);
	if (index != f_None) {
		bbDictionary_entry* entry = bbDictionary_indexLookup(dict, index);
		entry->m_Value = value;
		return Success;
	}

	//create new entry
	I32 hash_value = hash(key, dict->m_NumBins);
	int* head = &dict->m_Bins[hash_value].Head;
	int* tail = &dict->m_Bins[hash_value].Tail;
	bbDictionary_entry* entry = grab_entry(dict);
	entry->m_InUse = 1;
	strcpy(entry->m_Key, key);
	entry->m_Value = value;

	//Insert into empty bin;
	if (*head == f_None){
		bbAssert(*tail == f_None, "Head/Tail mismatch\n");

		*head = entry->m_Self;
		*tail = entry->m_Self;
		entry->m_Next = f_None;
		entry->m_Prev = f_None;

		return Success;
	}
	//*head != f_None
	bbAssert(*tail != f_None, "Head/Tail mismatch\n");

	//Insert into non-empty bin, (after *tail)

	bbDictionary_entry* tail_entry = bbDictionary_indexLookup(dict, dict->m_Bins[hash_value].Tail);
	tail_entry->m_Next = entry->m_Self;

	entry->m_Prev = *tail;
	entry->m_Next = f_None;
	*tail = entry->m_Self;


	return Success;
}

bbFlag bbDictionary_print(bbDictionary* dict){

	printf("Bin #:\tDict_Self,\tDict_Prev,\tDict_Next,\tDict_In_Use,\tkey,\tvalue\n");
	for (I32 i = 0; i < dict->m_NumBins; i++){
		I32 index = dict->m_Bins[i].Head;
		while (index != f_None){
			bbDictionary_entry* entry = bbDictionary_indexLookup(dict, index);

			printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%s\t\t%d\n",
				   i,
				   entry->m_Self,
				   entry->m_Prev,
				   entry->m_Next,
				   entry->m_InUse,
				   entry->m_Key,
				   entry->m_Value);

			index = entry->m_Next;
		}
	}
	printf("\n");
	return Success;

}