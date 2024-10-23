#include "engine/logic/recycle/bbFloorDivision.h"
#include "engine/logic/bbFastPool.h"
#include "engine/logic/bbSlowPool.h"
#include "engine/logic/bbFlag.h"
#include "engine/logic/bbIntTypes.h"
#include <stdio.h>

#define bbTestPool_Handle          bbSlowPool_Handle
#define bbTestPool_Header          bbSlowPool_Header
#define bbTestPool_Available       bbSlowPool_Available
#define bbTestPool                 bbSlowPool
#define bbTestPool_HeaderIsNULL(x) bbSlowPool_HeaderIsNULL(x)
#define bbTestPool_newPool         bbSlowPool_newPool
#define bbTestPool_deletePool      bbSlowPool_deletePool
#define bbTestPool_clearPool       bbSlowPool_clearPool
#define bbTestPool_newA            bbSlowPool_newA
#define bbTestPool_newH            bbSlowPool_newH
#define bbTestPool_deleteA         bbSlowPool_deleteA
#define bbTestPool_deleteH         bbSlowPool_deleteH
#define bbTestPool_getAddress      bbSlowPool_getAddress
#define bbTestPool_getHandle       bbSlowPool_getHandle

typedef struct {
    bbTestPool_Header p_Pool;
    I32 m_int;
    char m_string[512];

} bbTestStruct;


int main(void){

    bbTestPool* Pool;
    int flag = bbTestPool_newPool(&Pool, sizeof(bbTestStruct), 11, 7, 0);

    bbTestStruct* testStruct;
    for (I32 i = 1; 1 == 1; i++){
        flag = bbTestPool_newA(Pool, &testStruct);
        bbAssert(flag == f_Success, "pool full\n", i);

        bbPrintf("index = %d\n", testStruct->p_Pool.p_Handle & 0x3FFFFFFF);
    }

}