#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbPrime.h"

#ifndef BBDRAWFUNCTIONS_H
#define BBDRAWFUNCTIONS_H

typedef bbFlag bbDrawFunction(void* drawable, void* frameDescriptor, void* cl);

typedef struct {
    void* graphics;
    void* target;
    I32 GUI_time;
    I32 mapTime;
} drawFuncClosure;

typedef struct {
	I32 num;
	bbDictionary* dictionary;
	bbDrawFunction* functions[];
} bbDrawfunctions;

bbFlag bbDrawfunctions_new(bbDrawfunctions** drawfunctions);


#endif // BBDRAWFUNCTIONS_H