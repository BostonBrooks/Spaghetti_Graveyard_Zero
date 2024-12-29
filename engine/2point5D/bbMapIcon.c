#include "engine/2point5D/bbMapIcon.h"

bbFlag bbMapIcons_new(void** self, I32 squares_i, I32 squares_j){

    bbMapIcons* mapIcons;
    mapIcons = malloc(sizeof(bbMapIcons) + squares_i * squares_j * sizeof
            (bbList));
    bbAssert(mapIcons != NULL, "bad malloc\n");
    bbVPool* pool;
    bbVPool_newBloated(&pool, sizeof(bbMapIcon), 1000, 1000);

    for (I32 i = 0; i < squares_i * squares_j; i++){
        bbList_init(&mapIcons->list[i], pool, NULL,
                    offsetof(bbMapIcon, listElement),NULL);

    }
    mapIcons->squares_i = squares_i;
    mapIcons->squares_j = squares_j;
    mapIcons->pool = pool;
    *self = mapIcons;
    return Success;
}