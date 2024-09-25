/**
 * @file
 * @brief return the first integer not less than a, that is a multiple of b
 **/
#include "engine/logic/bbIntTypes.h"

static U32 bbRoundUp (I32 a, I32 b){
	I32 c = a % b;
	if (c == 0) return a;
	return (a + b - c);
}