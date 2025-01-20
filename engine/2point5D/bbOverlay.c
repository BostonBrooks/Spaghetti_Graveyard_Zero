#include "engine/2point5D/bbOverlay.h"
#include "engine/logic/bbString.h"
#include "engine/includes/CSFML.h"
#include "engine/logic/bbListList.h"
#include "engine/2point5D/bbViewportCoords.h"

bbFlag myFunc (bbList* list, void* node, void* cl){
	bbOverlayIcon* overlayIcon = node;
	printf ("label = %s\n", overlayIcon->label);
	return Continue;
}

typedef struct {
    void* graphics;
    void* target;
    I32 GUI_time;
    I32 mapTime;
} drawFuncClosure_overlay;


bbFlag bbOverlay_new(void** self, I32 squares_i, I32 squares_j){

    bbOverlay* overlay = malloc(sizeof(bbOverlay)
								+ sizeof(bbOverlaySquare) * squares_i * squares_j);
    bbAssert(overlay != NULL, "bad malloc\n");

    bbVPool* pool;

    bbVPool_newBloated(&pool, sizeof(bbOverlayIcon), 1000, 1000);


	overlay->squares_i = squares_i;
	overlay->squares_j = squares_j;

	//overlay->font = sfFont_createFromFile("./graphics/Bowman.ttf");
	//bbAssert(overlay->font != NULL, "bad font\n");

    for(I32 i = 0; i < squares_i; i++){
        for(I32 j = 0; j < squares_j; j++){
            I32 n = i + squares_i * j;
            bbOverlaySquare* overlaySquare = &overlay->squares[n];
			overlaySquare->coords.i = i;
			overlaySquare->coords.j = j;
			overlaySquare->coords.k = 0;
			overlaySquare->pool = pool;
			bbList_init(&overlaySquare->list,
						pool,
						NULL,
						offsetof(bbOverlayIcon, listElement),
						bbOverlayIcon_isCloser);

			bbOverlayIcon* overlayIcon;
			bbVPool_alloc(pool, &overlayIcon);
			overlayIcon->coords = bbSquareCoords_getMapCoords(overlaySquare->coords);

			overlayIcon->listElement.prev = pool->null;
			overlayIcon->listElement.next = pool->null;
			bbStr_setStr(overlayIcon->label, "An Icon", KEY_LENGTH);
			overlayIcon->txt = sfText_create();
			//sfText_setFont(overlayIcon->txt, overlay->font);
			sfText_setString(overlayIcon->txt, overlayIcon->label);
			sfText_setCharacterSize(overlayIcon->txt, 50);
			overlayIcon->sprite = 4;
			//should be sortL
			bbList_pushL(&overlaySquare->list, overlayIcon);


			bbVPool_alloc(pool, &overlayIcon);
			overlayIcon->coords = bbSquareCoords_getMapCoords(overlaySquare->coords);
			overlayIcon->listElement.prev = pool->null;
			overlayIcon->listElement.next = pool->null;
			bbStr_setStr(overlayIcon->label, "Another Icon", KEY_LENGTH);
			overlayIcon->txt = sfText_create();
			//sfText_setFont(overlayIcon->txt, overlay->font);
			sfText_setString(overlayIcon->txt, overlayIcon->label);
			sfText_setCharacterSize(overlayIcon->txt, 50);
			overlayIcon->sprite = 4;
			//should be sortL
			bbList_pushL(&overlaySquare->list, overlayIcon);

			bbList_mapL(&overlaySquare->list, myFunc, NULL);
        }
    }
	*self = overlay;
	return Success;
}

bbFlag print_overlayIcon (void* node, void* cl){
	bbOverlayIcon* overlayIcon = node;
    drawFuncClosure_overlay* foo = cl;
	printf("overlay label: %s\n", overlayIcon->label);
    I32 spriteInt = 4;

    bbGraphics* graphics = foo->graphics;
    sfSprite* sprite = graphics->sprites->sprites[spriteInt];

    bbViewport* VP = foo->target;

    sfRenderTexture* renderTexture = VP->overlay.renderTexture;

    sfVector2f V2F = bbMapCoords_getV2f_overlay(overlayIcon->coords, VP);

    bbDebug("V2F.x = %f, V2F.y = %f\n", V2F.x, V2F.y);

    sfSprite_setPosition(sprite, V2F);
    sfRenderTexture_drawSprite(renderTexture, sprite, NULL);

	return Continue;
}

bbFlag bbOverlay_draw(bbOverlay* overlay, bbViewport* viewport, bbGraphics* graphics){

	bbListList list;
	bbListList_init(&list);

	I32 squares_i = overlay->squares_i;
	I32 squares_j = overlay->squares_j;

	for (int i = 0; i < squares_i; ++i) {
		for (int j = 0; j < squares_j; ++j) {
			I32 n = i + squares_i * j;
			bbListList_attach(&list, &overlay->squares[n].list);
		}

	}
    drawFuncClosure_overlay cl;
    cl.graphics = graphics;
    cl.target = viewport;
    cl.mapTime = 696969;
    cl.GUI_time = 69696969;

	bbListList_map(&list, print_overlayIcon, &cl);





}


I32 bbOverlayIcon_isCloser(void* one, void* two){
    bbOverlayIcon* iconOne = one;
    bbOverlayIcon* iconTwo = two;

    I32 foo = iconTwo->coords.i - iconOne->coords.i
              -iconTwo->coords.j + iconOne->coords.j;

    return (foo < 0);
}