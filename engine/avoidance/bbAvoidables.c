#include "engine/avoidance/bbAvoidables.h"
#include "engine/includes/CSFML.h"
#include "engine/geometry/bbViewportCoords.h"

sfCircleShape* avoidableCircle;

bbFlag bbAvoidables_new(void** self, I32 squares_i, I32 squares_j) {

    bbAvoidables* avoidables;
    bbDrawables_newImpl((void**)&avoidables, squares_i, squares_j, sizeof
    (bbAvoidable));

    avoidableCircle = sfCircleShape_create();
    sfColor darkGreen = sfColor_fromRGB(0,104,54);
    sfCircleShape_setFillColor(avoidableCircle, darkGreen);
    sfVector2f scale;
    scale.x = 1.414f;
    scale.y = 0.707f;

    sfCircleShape_setScale(avoidableCircle, scale);
    sfCircleShape_setRadius(avoidableCircle, 10);

    *self = avoidables;
    return Success;
}

bbFlag bbAvoidables_draw(bbAvoidables* avoidables, drawFuncClosure* cl,
                        I32 square_i_min, I32 square_j_min,
                        I32 square_i_max, I32 square_j_max){
    bbNestedList list;
    bbNestedList_init(&list);
    I32 squares_i = avoidables->squares_i;
    I32 squares_j = avoidables->squares_j;

    for (int i = square_i_min; i < square_i_max; ++i) {
        for (int j = square_j_min; j < square_j_max; ++j) {
            I32 n = i + squares_i * j;
            bbNestedList_attach(&list, &avoidables->squares[n].list);
        }

    }

    bbNestedList_map(&list, bbAvoidable_drawFunc, cl);

    //TODO bbNestedList_cleanup;
    return Success;
}

bbFlag bbAvoidable_drawFunc(void* node, void* cl){

    bbAvoidable* avoidable = node;
    drawFuncClosure* foo = cl;
    bbViewport* VP = foo->target;

    sfVector2f position = bbMapCoords_getV2f(avoidable->coords, VP);

    sfRenderTexture* renderTexture = VP->ground.renderTexture;

    sfCircleShape_setPosition(avoidableCircle, position);
    float radius = (float)(avoidable->radius) / POINTS_PER_PIXEL;
    sfVector2f origin;
    origin.x = radius;
    origin.y = radius;
    sfCircleShape_setOrigin(avoidableCircle, origin);
    sfCircleShape_setRadius(avoidableCircle, radius);
    sfRenderTexture_drawCircleShape(renderTexture, avoidableCircle,NULL);

    return Success;
}


bbFlag bbAvoidable_new(bbAvoidable** self, bbAvoidables* avoidables,
                       bbMapCoords MC, I32 radius){
    bbVPool* pool = avoidables->pool;
    bbSquareCoords SC = bbMapCoords_getSquareCoords(MC);
    I32 index = bbDrawables_getSquareIndex(SC.i, SC.j, avoidables->squares_i);
    bbAvoidableSquare avoidableSquare = avoidables->squares[index];

    bbAvoidable* avoidable;
    bbVPool_alloc(pool, (void**)&avoidable);
    avoidable->coords = MC;
    avoidable->radius = radius;

    bbList_sortL(&avoidableSquare.list, avoidable);

    *self = avoidable;
    return Success;
}