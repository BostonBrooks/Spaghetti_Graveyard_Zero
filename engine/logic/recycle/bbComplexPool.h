/**
 * @file
 * @brief complex pool is able to expand (to an extent)
 * can detect if an object being accessed has previously been deleted
 *
 */

#ifndef BBCOMPLEXPOOL_H
#define BBCOMPLEXPOOL_H


#include "engine/logic/bbIntTypes.h"
#include "bbPool.h"

typedef struct bbPool_common bbPool_common;

typedef struct {
    U32 collision;
    U32 index;
} bbComplexPool_Handle;

I32 bbComplexPool_newPool(bbPool_common** pool, I32 sizeOf, I32 level1,
        I32 level2);

#endif // BBCOMPLEXPOOL_H