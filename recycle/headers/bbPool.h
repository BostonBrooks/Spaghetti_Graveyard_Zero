/**
 * @file
 * @brief Pools pre-allocate space for objects in the game to quickly allocate and de-allocate individual objects
 *
 * The first element of an object in a pool must be "bbPool_data p_PoolData;"
 */

#ifndef BBPOOL_H
#define BBPOOL_H

#include <inttypes.h>
#include <stdlib.h>
#include "bbPrintf.h"
#include "bbIntTypes.h"


/** @name Pool Error Codes
 * Stuff for passing flags around when using pools
 **/
///@{
#define f_PoolSuccess                    0
#define f_PoolNone                      -1
#define f_PoolInUse                     -2
#define f_PoolNotInUse                  -3
#define f_PoolLvl1NotInitialised        -4
#define f_PoolLvl1AlreadyInitialised    -5
#define f_PoolLvl1OutOfBounds           -6
#define f_PoolMallocFailed              -7
#define f_PoolFull                      -8
#define f_PoolLvl1Full                  -9
#define f_PoolNextAvailable            -10
///@}


typedef struct {
	I32 Self;
	I32 Prev;
	I32 Next;

	//InUse == f_PoolNotInUse or InUse!= f_PoolNotInUse, can be used as an array index in an array of linked lists
	I32 InUse;
	I32 Map;
	I32 Priority;
} bbPool_data;

typedef struct {
	I32 Head;
	I32 Tail;
} bbPool_bin;

typedef struct {
	I32 m_Map;
	I32 m_SizeOf;
	bbPool_bin m_Available;
	bbPool_bin m_InUse; //In use drawables can be in any queue in bbQueue
	I32 m_Level1;
	I32 m_Level2;
	void** m_Objects;
} bbPool;


///Look up object at location Pool[lvl1][lvl2];
I32 bbPool_Lookup2(void** RBR, bbPool* Pool, I32 lvl1, I32 lvl2);


///Lookup object at address, ignoring m_Pool_InUse;
I32 bbPool_Lookup_sudo(void** RBR, bbPool* Pool, I32 Address);


///Lookup object at Address, error if m_Pool_InUse == f_PoolInUse
I32 bbPool_Lookup(void** RBR, bbPool* Pool, I32 Address);

///Create an new pool with object's size = Sizeof
I32 bbPool_NewPool(bbPool** RBR, I32 map, I32 SizeOf, I32 Level1, I32 Level2);

///Delete entire pool
I32 bbPool_DeletePool(bbPool* Pool);

///Delete contents of pool, but keep empty pool
I32 bbPool_ClearPool(bbPool* Pool);

/// Allocate data in pool
I32 bbPool_IncreasePool(bbPool* Pool, I32 Level1_Address);

///Create object in pool
I32 bbPool_New(void** RBR, bbPool* Pool, I32 address);

///Remove object from pool
I32 bbPool_Delete(bbPool* Pool, I32 address);

#endif //BBPOOL_H
