#ifndef BBPOOLHANDLE_H
#define BBPOOLHANDLE_H

#include "engine/logic/bbIntTypes.h"

//may want to do a 16:48 split to allow 2^48 indices
typedef struct {
	U32 collision;
	U32 index;
} bbBloatedPool_Handle;

typedef union {
	void* ptr;
	bbBloatedPool_Handle bloated;
	U64 u64;
    I32x2 i32x2;
} bbPool_Handle;


typedef struct{
	bbPool_Handle head;
	bbPool_Handle tail;
}  bbPool_List;

typedef struct{
	bbPool_Handle prev;
	bbPool_Handle next;
}  bbPool_ListElement;
#endif // BBPOOLHANDLE_H