#include "engine/2point5D/bbOverlays.h"
#include "engine/logic/bbString.h"
#include "engine/includes/CSFML.h"
#include "engine/logic/bbNestedList.h"
#include "engine/2point5D/bbViewportCoords.h"

extern sfRenderWindow* testWindow;


bbFlag myFunc (bbList* list, void* node, void* cl){
	bbOverlay* overlayIcon = node;
	printf ("label = %s\n", overlayIcon->label);
	return Continue;
}




bbFlag bbOverlays_new(void** self, bbGraphics* graphics, I32 squares_i, I32
squares_j){

    bbOverlays* overlay = malloc(sizeof(bbOverlays)
                                 + sizeof(bbOverlaySquare) * squares_i * squares_j);
    bbAssert(overlay != NULL, "bad malloc\n");

    bbVPool* pool;

    bbVPool_newBloated(&pool, sizeof(bbOverlay), 1000, 1000);


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
                        offsetof(bbOverlay, listElement),
                        bbOverlay_isCloser);

			bbOverlay* overlayIcon;
			bbVPool_alloc(pool, &overlayIcon);
			overlayIcon->coords = bbSquareCoords_getMapCoords(overlaySquare->coords);
            overlayIcon->coords.i += rand() % (400 * POINTS_PER_PIXEL);
            overlayIcon->coords.j += rand() % (400 * POINTS_PER_PIXEL);

			overlayIcon->listElement.prev = pool->null;
			overlayIcon->listElement.next = pool->null;
			bbStr_setStr(overlayIcon->label, "An Icon", KEY_LENGTH);
			overlayIcon->txt = sfText_create();
			//sfText_setFont(overlayIcon->txt, overlay->font);
			sfText_setString(overlayIcon->txt, overlayIcon->label);
			sfText_setCharacterSize(overlayIcon->txt, 50);
			overlayIcon->sprite = 4;

            bbPool_Handle drawfunctionHandle;

            bbDictionary_lookup(graphics->drawfunctions->dictionary,
                                "OVERLAYTEST",
                                &drawfunctionHandle);

            overlayIcon->frames[0].drawfunction = drawfunctionHandle.u64;

            for (I32 k = 1; k < FRAMES_PER_OVERLAY; k++){
                overlayIcon->frames[k].drawfunction = -1;
            }

			//TODO should be sortL

			bbList_pushL(&overlaySquare->list, overlayIcon);

			bbList_mapL(&overlaySquare->list, myFunc, NULL);
        }
    }
	*self = overlay;
	return Success;
}

bbFlag print_overlayIcon (void* node, void* cl){
	bbOverlay* overlayIcon = node;
    drawFuncClosure* foo = cl;
	printf("overlay label: %s\n", overlayIcon->label);
    I32 spriteInt = 8;

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



I32 bbOverlay_isCloser(void* one, void* two){
    bbOverlay* iconOne = one;
    bbOverlay* iconTwo = two;

    I32 foo = iconTwo->coords.i - iconOne->coords.i
              -iconTwo->coords.j + iconOne->coords.j;

    return (foo > 0);
}

bbFlag bbOverlays_draw(bbOverlays* overlays, drawFuncClosure* cl){
    bbNestedList list;
    bbNestedList_init(&list);
    I32 squares_i = overlays->squares_i;
    I32 squares_j = overlays->squares_j;

    for (int i = 0; i < squares_i; ++i) {
        for (int j = 0; j < squares_j; ++j) {
            I32 n = i + squares_i * j;
            bbNestedList_attach(&list, &overlays->squares[n].list);
        }

    }


    bbNestedList_map(&list, bbOverlay_drawFunc, cl);

    return Success;
}

///typedef bbFlag bbNestedList_mapFunction(void* node, void* cl);
bbFlag bbOverlay_drawFunc(void* node, void* cl){
    return bbOverlay_draw(node, cl);
}

bbFlag bbOverlay_draw(bbOverlay* overlay, drawFuncClosure* cl){
    for (I32 i = 0; i < FRAMES_PER_OVERLAY; i++){
        bbFrame* frame = &overlay->frames[i];



        if (frame->drawfunction >= 0 && frame->drawfunction < 7) {
            bbGraphics* graphics = cl->graphics;
            bbDrawFunction *drawFunction =
                    graphics->drawfunctions->functions[frame->drawfunction];

            drawFunction(overlay, frame, cl);

        }
    }
}