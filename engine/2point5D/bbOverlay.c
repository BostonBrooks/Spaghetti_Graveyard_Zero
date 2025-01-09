#include "engine/2point5D/bbOverlay.h"
#include "engine/logic/bbString.h"
#include "engine/includes/CSFML.h"

bbFlag bbMapIcons_new(void** self, I32 squares_i, I32 squares_j){

    bbOverLay* mapIcons = malloc(sizeof(bbOverLay)
								 + sizeof(bbOverlaySquare) * squares_i * squares_j);
    bbAssert(mapIcons != NULL, "bad malloc\n");

    bbVPool* pool;

    bbVPool_newBloated(&pool, sizeof(bbOverlayIcon), 1000, 1000);


    mapIcons->squares_i = squares_i;
    mapIcons->squares_j = squares_j;

	mapIcons->font = sfFont_createFromFile("./graphics/Bowman.ttf");
    for(I32 i = 0; i < squares_i; i++){
        for(I32 j = 0; j < squares_j; j++){
            I32 n = i + squares_i * j;
            bbOverlaySquare* mapSquare = &mapIcons->squares[n];
            mapSquare->coords.i = i;
			mapSquare->coords.j = j;
			mapSquare->coords.k = 0;
            mapSquare->pool = pool;
            bbList_init(&mapSquare->list,
						pool,
						NULL,
                        offsetof(bbOverlayIcon, listElement),
                        bbMapIcon_compare);

			bbOverlayIcon* overlayIcon;
			bbVPool_alloc(pool, &overlayIcon);
			overlayIcon->coords = bbSquareCoords_getMapCoords(mapSquare->coords);
			overlayIcon->listElement.prev = pool->null;
			overlayIcon->listElement.next = pool->null;
			bbStr_setStr(overlayIcon->label, "An Icon", KEY_LENGTH);
			overlayIcon->txt = sfText_create();
			sfText_setFont(overlayIcon->txt, mapIcons->font);
			sfText_setString(overlayIcon->txt, overlayIcon->label);
			sfText_setCharacterSize(overlayIcon->txt, 50);
			overlayIcon->sprite = 4;

        }
    }
}



I32 bbMapIcon_compare(void* one, void* two){
    bbOverlayIcon* iconOne = one;
    bbOverlayIcon* iconTwo = two;

    I32 foo = iconTwo->coords.i - iconOne->coords.i
              -iconTwo->coords.j + iconOne->coords.j;

    return (foo < 0);
}