/**
 * the first element of bbWodget gives its place in a tree data structure
 * wodgets are drawn to the screen by doing a descending search of the tree
 * clicks are detected by doing an ascending search of the tree
 *
 * wodgets themselves are drawn to the screen much like how drawables are drawn
 * to the viewport, they share the same bbSprites, bbAnimations and bbCompositions
 * wodgets have a separate clock for calculating framerates so that wodgets can
 * be animated while the game is paused
 **/


#include "engine/graphics/bbGraphics.h"
#include "engine/wodgets/bbWodget.h"
#include "engine/logic/bbTree.h"
#include "engine/geometry/bbCoordinates.h"

bbFlag bbWodgets_init(bbWodgets* wodgets){
	bbVPool_newBloated(&wodgets->pool, sizeof(bbWodget), 1024, 1024);
	bbTree_new(&wodgets->tree, wodgets->pool, offsetof(bbWodget, tree));


}



//bbFlag testFunc(bbTree* tree, void* node, void* cl)
bbFlag bbWodget_mouseFunc(bbTree* tree, void* node, void* cl){
	bbWodget* wodget = node;
	mouseActionClosure* closure = cl;
	return bbWodget_mouse(wodget, closure->event, closure->functions);
}

bbFlag bbWodget_mouse(bbWodget* wodget, bbMouseEvent* mouseEvent, bbWodgetFunctions* functions){
	I32 mouseInt = wodget->onMouse.onMouse;

	bbWodget_Mouse* func = functions->Mouse[mouseInt];

	return func(mouseEvent, wodget);

	bbHere();
	return Continue;
}

//bbFlag testFunc(bbTree* tree, void* node, void* cl)
bbFlag bbWodget_drawFunc(bbTree* tree, void* node, void* cl){
	bbWodget* wodget = node;
	return bbWodget_draw(wodget, cl);

}

bbFlag bbWodget_draw(bbWodget* wodget, drawFuncClosure* cl){
	for (I32 i = 0; i < FRAMES_PER_WODGET; i++){
		bbFrame* frame = &wodget->frames[i];

        //bbDebug("frame->drawfunction = %d\n", frame->drawfunction);
		if (frame->drawfunction >= 0 && frame->drawfunction < 6) {
            bbGraphics* graphics = cl->graphics;
			bbDrawFunction *drawFunction =
                    graphics->drawfunctions->functions[frame->drawfunction];

			drawFunction(wodget, frame, cl);

		}
	}
}

bbFlag bbWodget_newLayout(bbWodget** self, bbGraphics* graphics, bbWodgets* wodgets, bbWodget* parent){

	bbWodget* wodget;

	bbWodget_newEmpty(&wodget, wodgets, parent);

	bbScreenPointsRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.width = 720 * 8;
	rect.height = 480 * 8;

	wodget->rect = rect;

	bbPool_Handle drawfunctionHandle;
	bbDictionary_lookup(graphics->drawfunctions->dictionary, "WODGETSPRITE", &drawfunctionHandle);

	wodget->frames[0].drawfunction = drawfunctionHandle.u64;

	bbDictionary_lookup(graphics->sprites->dictionary,
						"LAYOUT_480", &wodget->frames[0].handle);

    //bbDebug("LAYOUT_480 = %d\n", wodget->frames[0].handle.u64);
	wodget->frames[0].offset.x = 0;
	wodget->frames[0].offset.y = 0;




	for (I32 i = 1; i < FRAMES_PER_WODGET; i++) {
	    wodget->frames[i].drawfunction = -1;
	}

	*self = wodget;
}

bbFlag bbWodget_newEmpty(bbWodget** self, bbWodgets* wodgets, bbWodget* parent){
	bbWodget* wodget; bbPool_Handle wodgetHandle;
	bbVPool_alloc(wodgets->pool, &wodget);
	bbVPool_reverseLookup(wodgets->pool, wodget, &wodgetHandle);

	wodget->tree.visible = true;
	wodget->tree.childrenvisible = true;

	wodget->onMouse.onMouse = 0;

	if (parent == NULL){
		wodgets->tree->root = wodgetHandle;
	} else {
        bbTreeNode_setParent(wodgets->tree, wodget, parent);
	}

	for (I32 i = 0; i < FRAMES_PER_WODGET; i++) {
		wodget->frames[i].drawfunction = -1;
	}
	*self = wodget;
	return Success;
}

bbFlag bbWodget_newMockViewport(bbWodget** self, bbGraphics* graphics, bbWodgets* wodgets, bbWodget* parent){
	bbWodget* wodget;

	bbWodget_newEmpty(&wodget, wodgets, parent);

	bbScreenPointsRect rect;
	rect.left = 12 * POINTS_PER_PIXEL;
	rect.top = 12 * POINTS_PER_PIXEL;
	rect.width = 466 * POINTS_PER_PIXEL;
	rect.height = 456 * POINTS_PER_PIXEL;

	wodget->rect = rect;

	bbPool_Handle drawfunctionHandle;
	bbDictionary_lookup(graphics->drawfunctions->dictionary, "WODGETSPRITE", &drawfunctionHandle);

	wodget->frames[0].drawfunction = drawfunctionHandle.u64;

	bbDictionary_lookup(graphics->sprites->dictionary,
						"VIEWPORT_480", &wodget->frames[0].handle);

	wodget->frames[0].offset.x = 0;
	wodget->frames[0].offset.y = 0;
	wodget->frames[0].framerate = 1.0;

	wodget->frames[0].type = Sprite;


	for (I32 i = 1; i < FRAMES_PER_WODGET; i++) {
		wodget->frames[i].drawfunction = -1;
	}

	*self = wodget;
}

bbFlag bbWodget_newViewport(bbWodget** self, bbGraphics* graphics,
                            bbWodgets* wodgets, bbWodget* parent,
                            void* viewport){

    bbWodget* wodget;
    bbWodget_newEmpty(&wodget, wodgets, parent);
    wodget->extra_data = viewport;

    bbScreenPointsRect rect;
    rect.left = 12 * POINTS_PER_PIXEL;
    rect.top = 12 * POINTS_PER_PIXEL;
    rect.width = 466 * POINTS_PER_PIXEL;
    rect.height = 456 * POINTS_PER_PIXEL;

    wodget->rect = rect;

    bbPool_Handle drawfunctionHandle;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WODGETVIEWPORT",
                        &drawfunctionHandle);

    wodget->frames[0].drawfunction = drawfunctionHandle.u64;

    for (I32 i = 1; i < FRAMES_PER_WODGET; i++) {
        wodget->frames[i].drawfunction = -1;
    }
}

bbFlag bbWodgets_draw(bbWodgets* wodgets, void* cl) {

    bbTree* tree = wodgets->tree;
    bbVPool* pool = tree->pool;
    void* root;
    bbVPool_lookup(pool, &root, tree->root);
    return bbTree_descendingMapVisible(tree, root, bbWodget_drawFunc, cl);
}

//in the following function, cl contains fields such as mouse coordinates, mouse action
bbFlag bbWodgets_onMouse(bbWodgets* wodgets, void* cl) {
	bbTree* tree = wodgets->tree;
	bbVPool* pool = tree->pool;
	void* root;
	bbVPool_lookup(pool, &root, tree->root);
	return bbTree_ascendingMapVisible(tree, root, bbWodget_mouseFunc, cl);
}
