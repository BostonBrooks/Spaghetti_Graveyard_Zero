#include "engine/2point5D/bbMapIcon.h"

bbFlag bbMapIcons_new(void** self, I32 squares_i, I32 squares_j){

    bbMapIcons* mapIcons = malloc(sizeof(bbMapIcons)
            + sizeof(bbMapIconSquare)* squares_i *  squares_j);
    bbAssert(mapIcons != NULL, "bad malloc\n");

    bbVPool* pool;

    bbVPool_newBloated(&pool, sizeof(bbMapIcon), 1000, 1000);


    mapIcons->squares_i = squares_i;
    mapIcons->squares_j = squares_j;

    for(I32 i = 0; i < squares_i; i++){
        for(I32 j = 0; j < squares_j; j++){
            I32 n = i + squares_i * j;
            bbMapIconSquare* mapSquare = &mapIcons->squares[n];
            mapSquare->square_i = i;
            mapSquare->square_j = j;
            mapSquare->pool = pool;
            bbList_init(&mapSquare->list, NULL,
                        offsetof(bbMapIcon, listElement),
                        bbMapIcon_compare());
        }
    }
}


I32 bbMapIcon_compare(void* one, void* two){
    bbMapIcon* iconOne = one;
    bbMapIcon* iconTwo = two;

    I32 foo = iconTwo->coords.i - iconOne->coords.i
              -iconTwo->coords.j + iconOne->coords.j;

    return (foo < 0);
}