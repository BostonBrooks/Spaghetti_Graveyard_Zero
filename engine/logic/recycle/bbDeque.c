#include "bbDeque.h"

I32 bbDeque_newPool(bbDeque* deque, I32 sizeOf, I32 level1, I32 level2){
    bbSlowPool_newPool(&deque->p_pool, sizeOf,level1,level2);
}
