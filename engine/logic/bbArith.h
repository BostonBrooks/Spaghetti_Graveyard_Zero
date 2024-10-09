/**
 * @file
 * @brief We assume built in integer arithmetic rounds to zero
 * Define new arithmetic that rounds toward -infinity
 * -for now, we use 32 bit integers...
 */
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbTerminal.h"

static I32 bbArith_max (I32 x, I32 y){
    return x > y ? x : y;
}
static I32 bbArith_min (I32 x, I32 y){
    return x > y ? y : x;
}
static I32 bbArith_div (I32 x, I32 y){
    bbAssert(y != 0, "divide by zero\n");
    if ((x < 0 &&  y > 0) || (x > 0 && y < 0) && x%y != 0)
        return x/y - 1;
    return x/y;
}
static I32 bbArith_mod (I32 x, I32 y){
    return x - y* bbArith_div(x, y);
}
static I32 bbArith_ceiling (I32 x, I32 y){
    return bbArith_div(x, y);
}
static I32 bbArith_floor (I32 x, I32 y){
    return bbArith_div(x, y) + (x%y != 0);
}
static I32 bbArith_roundUp (I32 x, I32 y){
    return x >= 0 ? ((x + y - 1) / y) * y : (x / y) * y;
}

static I32 bbArith_roundDown (I32 x, I32 y){
    return x >= 0 ? (x / y) * y : ((x - y + 1) / y) * y;
}

static I64 bbArith_max64 (I64 x, I64 y){
    return x > y ? x : y;
}
static I64 bbArith_min64 (I64 x, I64 y){
    return x > y ? y : x;
}
static I64 bbArith_div64 (I64 x, I64 y){
    bbAssert(y != 0, "divide by zero\n");
    if ((x < 0 &&  y > 0) || (x > 0 && y < 0) && x%y != 0)
        return x/y - 1;
    return x/y;
}
static I64 bbArith_mod64 (I64 x, I64 y){
    return x - y* bbArith_div(x, y);
}
static I64 bbArith_ceiling64 (I64 x, I64 y){
    return bbArith_div(x, y);
}
static I64 bbArith_floor64 (I64 x, I64 y){
    return bbArith_div(x, y) + (x%y != 0);
}
static I64 bbArith_roundUp64 (I64 x, I64 y){
    return x >= 0 ? ((x + y - 1) / y) * y : (x / y) * y;
}

static I64 bbArith_roundDown64 (I64 x, I64 y){
    return x >= 0 ? (x / y) * y : ((x - y + 1) / y) * y;
}