/**
 * @file
 * @brief Pools pre-allocate space for objects in the game to quickly allocate and de-allocate individual objects
 * objects in pool must have first element
 *
 *	bbPool_data p_PoolData;
 */



#include <inttypes.h>
#include <stdlib.h>
#include "headers/bbPrintf.h"
#include "headers/bbPool.h"
#include "headers/bbFlags.h"
#include "headers/bbIntTypes.h"



///This object contains all the data required to be placed in a pool, but no data of it's own
typedef struct {
	bbPool_data p_Pool;
} bbPool_null;



///Look up object at location Pool[lvl1][lvl2];
I32 bbPool_Lookup2(void** reference, bbPool* Pool, I32 lvl1, I32 lvl2){

	int8_t* array = Pool->m_Objects[lvl1];
	I32 index = lvl2 * Pool->m_SizeOf;
	*reference = &array[index];
	return f_PoolSuccess;
}


///Lookup object at address, ignoring m_Pool_InUse;
I32 bbPool_Lookup_sudo(void** reference, bbPool* Pool, I32 Address){
	// Address in lvl1 of Pool
	int lvl1_Address = Address / Pool->m_Level2;
	// Address in lvl2 of Pool
	int lvl2_Address = Address % Pool->m_Level2;

	void* reference1;

	int return_flag = bbPool_Lookup2(&reference1, Pool, lvl1_Address, lvl2_Address);

	if (return_flag < 0) return return_flag;

    *reference = reference1;

	return f_PoolSuccess;
}


///Lookup object at Address, error if m_Pool_InUse == f_PoolInUse
I32 bbPool_Lookup(void** reference, bbPool* Pool, I32 Address){

    if (Address == f_None) {
        *reference = NULL;
        return f_PoolSuccess;
    }

	bbPool_null* Object;

	I32 return_flag = bbPool_Lookup_sudo(&Object, Pool, Address);

	if (return_flag < 0) return return_flag;

	bbAssert(Object->p_Pool.InUse != f_PoolNotInUse,
			 "Trying to lookup not in use member of pool\n");

	*reference = Object;

	return f_PoolSuccess;
}

I32 bbPool_NewPool(bbPool** reference, I32 map, I32 SizeOf, I32 Level1, I32 Level2){
	bbPool* Pool = malloc(sizeof(bbPool));
	bbAssert(Pool != NULL, "malloc returned null pointer\n");
	Pool->m_Map = map;
	Pool->m_SizeOf = SizeOf;
	Pool->m_Level1 = Level1;
	Pool->m_Level2 = Level2;
	Pool->m_Available.Head = f_PoolNone;
	Pool->m_Available.Tail = f_PoolNone;
	Pool->m_Objects = calloc(Level1, sizeof(void*));
	for (I32 i = 0; i < Level1; i++){
		Pool->m_Objects[i] = NULL;
	}
	*reference = Pool;

	return f_PoolSuccess;
}

I32 bbPool_DeletePool(bbPool* Pool){
	for (I32 i = 0; i < Pool->m_Level1; i++){
		//It's ok to free a NULL pointer
		free(Pool->m_Objects[i]);
	}
	free(Pool);

}
I32 bbPool_ClearPool(bbPool* Pool){

	for (I32 i = 0; i < Pool->m_Level1; i++){
		//It's ok to free a NULL pointer
		free(Pool->m_Objects[i]);
		Pool->m_Objects[i] = NULL;
	}

	Pool->m_Available.Head = f_PoolNone;
	Pool->m_Available.Tail = f_PoolNone;
}

I32 bbPool_IncreasePool(bbPool* Pool, I32 Level1_Address){


	bbAssert(Level1_Address == f_PoolNextAvailable, "Feature not implemented\n");
	I32 i = 0;
	//Find next available / NULL entry in level1 of the pool
	if(Level1_Address == f_PoolNextAvailable){
		while (i < Pool->m_Level1 && Pool->m_Objects[i] != NULL){
			i++;
		}
		if(i == Pool->m_Level1){
			bbWarning(1==0, "level1 pool full\n");
			return f_PoolLvl1Full;
		}
	} else {
		i = Level1_Address;
		if (Pool->m_Objects[i] != NULL){
			bbWarning(1==0, "lvl 1 already initialised?\n");
			return f_PoolLvl1AlreadyInitialised;
		}
	}
	void* lvl2pool = calloc(Pool->m_Level2, Pool->m_SizeOf);
	bbWarning(lvl2pool != NULL, "calloc failed\n");
	if (lvl2pool == NULL) return f_PoolMallocFailed;
	Pool->m_Objects[i] = lvl2pool;
	if (Pool->m_Available.Head == -1){
		bbAssert(Pool->m_Available.Tail == -1, "Head/Tail mismatch\n");


		for (I32 j = 0; j < Pool->m_Level2; j++) {

			bbPool_null *Object;
			I32 flag = bbPool_Lookup2(&Object, Pool, i, j);

			Object->p_Pool.Self = i * Pool->m_Level2 + j;
			Object->p_Pool.Prev = i * Pool->m_Level2 + j - 1;
			Object->p_Pool.Next = i * Pool->m_Level2 + j + 1;
			Object->p_Pool.InUse = f_PoolNotInUse;
			Object->p_Pool.Map = Pool->m_Map;
		}
		bbPool_null* Object;
		I32 flag = bbPool_Lookup2(&Object, Pool, i, 0);
		Object->p_Pool.Prev = f_PoolNone;
		flag =  bbPool_Lookup2(&Object, Pool, i, Pool->m_Level2 -1);
		Object->p_Pool.Next = f_PoolNone;

		Pool->m_Available.Head = i * Pool->m_Level2;
		Pool->m_Available.Tail = (i+1) * Pool->m_Level2 - 1;

		//Level1_Address >= 0, try to initiate lvl2 pool at location Level1_Address >= 0
	} else {
		bbAssert(0==1, "inreasing a non-empty pool is not yet supported\n");
	}
}

I32 bbPool_New(void** RBR, bbPool* Pool, I32 address){
	bbAssert(address == f_PoolNextAvailable, "Feature not implemented\n");

	if(Pool->m_Available.Head == f_PoolNone){
		bbAssert(Pool->m_Available.Tail == f_PoolNone, "Head/Tail mismatch\n");
		bbPool_IncreasePool(Pool, f_PoolNextAvailable);
	}

	address = Pool->m_Available.Head;

	bbPool_null* Object;
	I32 flag = bbPool_Lookup_sudo(&Object, Pool, address);

	Pool->m_Available.Head = Object->p_Pool.Next;
	if (Pool->m_Available.Head == f_PoolNone){
		Pool->m_Available.Tail = f_PoolNone;
	} else {
		/* No more m_InUse
		bbPool_null* Head;
		flag = bbPool_Lookup_sudo(&Head, Pool, Pool->m_InUse.Head);
		Head->p_Pool.Prev = f_PoolNone;
		 */
	}

    Object->p_Pool.InUse = f_PoolInUse;
	Object->p_Pool.Prev = f_PoolNone;
	Object->p_Pool.Next = f_PoolNone;

	/* No more m_InUse
	if (Pool->m_InUse.Head == f_PoolNone){
		bbAssert(Pool->m_InUse.Head == f_PoolNone, "Head/Tail mismatch\n");
		Pool->m_InUse.Head = address;
		Pool->m_InUse.Tail = address;
		Object->p_Pool.Prev = f_PoolNone;
		Object->p_Pool.Next = f_PoolNone;
		*RBR = Object;
		return f_PoolSuccess;
	}

	bbPool_null* Tail;
	flag = bbPool_Lookup(&Tail, Pool, Pool->m_InUse.Tail);
	Tail->p_Pool.Next = address;
	Object->p_Pool.Prev = Pool->m_InUse.Tail;
	Object->p_Pool.Next = f_PoolNone;
	Pool->m_InUse.Tail = address;
	 */
	*RBR = Object;

	return f_PoolSuccess;

}
/**  place onject in available list
 * new objects are taken from head (may wish to sort available objects)
 * so I guess its best to return them to head
 * remove from any list before deleting (assert prev, next == -1)
 */

I32 bbPool_Delete(bbPool* Pool, I32 address){
    bbPool_null* Object, *Prev, *Next;
    bbPool_Lookup(&Object, Pool, address);

    I32 i_Prev = Object->p_Pool.Prev;
    I32 i_Next = Object->p_Pool.Next;

	bbAssert(i_Next == f_PoolNone && i_Prev == f_PoolNone,
			 "trying to delete object in an existing list\n");


    Object->p_Pool.InUse = f_PoolNotInUse;
    // Add object to head of list;

    bbPool_Lookup_sudo(&Next, Pool, Pool->m_Available.Head);
    Object->p_Pool.Next = Pool->m_Available.Head;
    Pool->m_Available.Head = Object->p_Pool.Self;
    Next->p_Pool.Prev = Object->p_Pool.Self;
    Object->p_Pool.Prev = f_None;


}