#include "engine/2point5D/bbMapIcon.h"
#include "engine/logic/bbString.h"
#include "engine/includes/CSFML.h"

bbFlag bbMapIcons_new(void** self, I32 squares_i, I32 squares_j){

    bbMapIcons* mapIcons = malloc(sizeof(bbMapIcons)
            + sizeof(bbMapIconSquare)* squares_i *  squares_j);
    bbAssert(mapIcons != NULL, "bad malloc\n");

    bbVPool* pool;

    bbVPool_newBloated(&pool, sizeof(bbMapIcon), 1000, 1000);


    mapIcons->squares_i = squares_i;
    mapIcons->squares_j = squares_j;

	mapIcons->font = sfFont_createFromFile("./graphics/Bowman.ttf");
    for(I32 i = 0; i < squares_i; i++){
        for(I32 j = 0; j < squares_j; j++){
            I32 n = i + squares_i * j;
            bbMapIconSquare* mapSquare = &mapIcons->squares[n];
            mapSquare->coords.i = i;
			mapSquare->coords.j = j;
			mapSquare->coords.k = 0;
            mapSquare->pool = pool;
            bbList_init(&mapSquare->list, NULL,
                        offsetof(bbMapIcon, listElement),
                        bbMapIcon_compare());

			bbMapIcon* mapIcon;
			bbVPool_alloc(pool, &mapIcon);
			mapIcon->coords = bbSquareCoords_getMapCoords(mapSquare->coords);
			mapIcon->listElement.prev = pool->null;
			mapIcon->listElement.next = pool->null;
			bbStr_setStr(mapIcon->label, "An Icon", KEY_LENGTH);
			mapIcon->txt = sfText_create();
			sfText_setFont(mapIcon->txt, mapIcons->font);
			sfText_setString(mapIcon->txt, mapIcon->label);
			sfText_setCharacterSize(mapIcon->txt, 50);
			mapIcon->sprite = 4;

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