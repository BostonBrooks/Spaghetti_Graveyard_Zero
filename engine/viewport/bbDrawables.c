#include "engine/viewport/bbDrawables.h"
#include "engine/logic/bbNestedList.h"

I32 bbDrawables_getIndex(I32 i, I32 j, I32 squares_i){
    return i + squares_i * j;
}

I32 bbDrawable_isCloser(void* one, void* two){
    bbDrawable* iconOne = one;
    bbDrawable* iconTwo = two;

    I32 foo = iconTwo->coords.i - iconOne->coords.i
              -iconTwo->coords.j + iconOne->coords.j;

    return (foo > 0);
}

bbFlag bbDrawables_new(void** self, bbGraphics* graphics, I32 squares_i, I32
squares_j){
    bbDrawables* drawables = malloc(sizeof(bbDrawables) + sizeof
            (bbDrawableSquare)*squares_i*squares_j);
    bbAssert(drawables != NULL, "bad malloc\n");

    bbVPool* pool;

    bbVPool_newBloated(&pool, sizeof(bbDrawable), 1000, 1000);

    drawables->pool = pool;

    bbList_init(&drawables->list, pool,NULL,offsetof(bbDrawable, listElement)
                ,bbDrawable_isCloser);



    drawables->squares_i = squares_i;
    drawables->squares_j = squares_j;

    for (I32 i = 0; i < squares_i;i++){
        for (I32 j = 0; j < squares_j; j++){
            I32 n = bbDrawables_getIndex(i, j, squares_i);
            bbDrawableSquare* drawableSquare = &drawables->squares[n];
            drawableSquare->coords.i = i;
            drawableSquare->coords.j = j;
            drawableSquare->coords.k = 0;

            bbList_init(&drawableSquare->list, pool, NULL,offsetof
            (bbDrawable, listElement),bbDrawable_isCloser);
        }
    }
    *self = drawables;
    return Success;
}

///typedef bbFlag bbNestedList_mapFunction(void* node, void* cl);
bbFlag bbDrawable_drawFunc(void* node, void* cl){
    return bbDrawable_draw(node, cl);
}

bbFlag bbDrawable_draw(bbDrawable* drawable, drawFuncClosure* cl){
    for (I32 i = 0; i < FRAMES_PER_DRAWABLE; i++){
        bbFrame* frame = &drawable->frames[i];

        bbGraphics* graphics = cl->graphics;
/// the 8 in the next line refers to the number of draw functions in bbDrawfunctions
        if (frame->drawfunction >= 0 && frame->drawfunction <
        graphics->drawfunctions->num) {

            bbDrawFunction *drawFunction =
                    graphics->drawfunctions->functions[frame->drawfunction];

            drawFunction(drawable, frame, cl);

        }
    }
}

bbFlag bbDrawables_draw(bbDrawables* drawables, drawFuncClosure* cl,
                        I32 square_i_min, I32 square_j_min,
                        I32 square_i_max, I32 square_j_max){
    bbNestedList* list = &drawables->nestedList;

    //todo roll init out to bbDrawables_new
    bbNestedList_init(list);
    I32 squares_i = drawables->squares_i;
    I32 squares_j = drawables->squares_j;

    for (int i = square_i_min; i < square_i_max; ++i) {
        for (int j = square_j_min; j < square_j_max; ++j) {
            I32 n = bbDrawables_getIndex(i, j, drawables->squares_i);
            bbNestedList_attach(list, &drawables->squares[n].list);
        }

    }


    bbNestedList_map(list, bbDrawable_drawFunc, cl);

    return Success;
}