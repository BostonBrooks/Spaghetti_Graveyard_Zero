#include "engine/logic/bbFloorDivision.h"
#include "engine/logic/bbFastPool.h"
#include "engine/logic/bbFlags.h"
#include "engine/logic/bbIntTypes.h"
#include <stdio.h>

#define bbTestPool_Handle          bbFastPool_Handle
#define bbTestPool_Header          bbFastPool_Header
#define bbTestPool_Available       bbFastPool_Available
#define bbTestPool                 bbFastPool
#define bbTestPool_HeaderIsNULL(x) bbFastPool_HeaderIsNULL(x)
#define bbTestPool_newPool         bbFastPool_newPool
#define bbTestPool_deletePool      bbFastPool_deletePool
#define bbTestPool_clearPool       bbFastPool_clearPool
#define bbTestPool_newA            bbFastPool_newA
#define bbTestPool_newH            bbFastPool_newH
#define bbTestPool_deleteA         bbFastPool_deleteA
#define bbTestPool_deleteH         bbFastPool_deleteH
#define bbTestPool_getAddress      bbFastPool_getAddress
#define bbTestPool_getHandle       bbFastPool_getHandle

typedef struct {
    bbFastPool_Header p_Pool;
    I32 m_int;
    char m_string[512];

} bbTestStruct;


int main(void){

    bbTestPool* Pool;
    int flag = bbTestPool_newPool(&Pool, sizeof(bbTestStruct), 209600, 0, 0);

    bbTestStruct* testStruct;
    for (I32 i = 1; 1 == 1; i++){
        flag = bbFastPool_newA(Pool, &testStruct);
        bbAssert(flag == f_Success, "pool full\n", i);

        bbPrintf("i = %d\n", i);
    }

}