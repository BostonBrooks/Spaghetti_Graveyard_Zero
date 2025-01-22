/**
 * the first element of bbWidget gives its place in a tree data structure
 * widgets are drawn to the screen by doing a descending search of the tree
 * clicks are detected by doing an ascending search of the tree
 *
 * widgets themselves are drawn to the screen much like how drawables are drawn
 * to the viewport, they share the same bbSprites, bbAnimations and bbCompositions
 * widgets have a separate clock for calculating framerates so that widgets can
 * be animated while the game is paused
 **/


#include "engine/graphics/bbGraphics.h"
#include "engine/widgets/bbWidget.h"
#include "engine/logic/bbTree.h"
#include "engine/geometry/bbCoordinates.h"

bbFlag bbWidgets_init(bbWidgets* widgets){
	bbVPool_newBloated(&widgets->pool, sizeof(bbWidget), 1024, 1024);
	bbTree_new(&widgets->tree, widgets->pool, offsetof(bbWidget, tree));


}



//bbFlag testFunc(bbTree* tree, void* node, void* cl)
//TODO - massage bbWidget_draw so it looks like testfunc


bbFlag bbWidget_drawFunc(bbTree* tree, void* node, void* cl){
	bbWidget* widget = node;
	return bbWidget_draw(widget, cl);

}

bbFlag bbWidget_draw(bbWidget* widget, drawFuncClosure* cl){
	for (I32 i = 0; i < FRAMES_PER_WIDGET; i++){
		bbFrame* frame = &widget->frames[i];

        //bbDebug("frame->drawfunction = %d\n", frame->drawfunction);
		if (frame->drawfunction >= 0 && frame->drawfunction < 6) {
            bbGraphics* graphics = cl->graphics;
			bbDrawFunction *drawFunction =
                    graphics->drawfunctions->functions[frame->drawfunction];

			drawFunction(widget, frame, cl);

		}
	}
}

bbFlag bbWidget_newLayout(bbWidget** self, bbGraphics* graphics, bbWidgets* widgets, bbWidget* parent){

	bbWidget* widget;

	bbWidget_newEmpty(&widget, widgets, parent);

	bbScreenPointsRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.width = 720 * 8;
	rect.height = 480 * 8;

	widget->rect = rect;

	bbPool_Handle drawfunctionHandle;
	bbDictionary_lookup(graphics->drawfunctions->dictionary, "SPRITE", &drawfunctionHandle);

	widget->frames[0].drawfunction = drawfunctionHandle.u64;

	bbDictionary_lookup(graphics->sprites->dictionary,
						"LAYOUT_480", &widget->frames[0].handle);

    //bbDebug("LAYOUT_480 = %d\n", widget->frames[0].handle.u64);
	widget->frames[0].offset.x = 0;
	widget->frames[0].offset.y = 0;




	for (I32 i = 1; i < FRAMES_PER_WIDGET; i++) {
	    widget->frames[i].drawfunction = -1;
	}

	*self = widget;
}

bbFlag bbWidget_newEmpty(bbWidget** self, bbWidgets* widgets, bbWidget* parent){
	bbWidget* widget; bbPool_Handle widgetHandle;
	bbVPool_alloc(widgets->pool, &widget);
	bbVPool_reverseLookup(widgets->pool, widget, &widgetHandle);
	if (parent == NULL){
		widgets->tree->root = widgetHandle;
	} else {
        bbTreeNode_setParent(widgets->tree, widget, parent);
	}

	for (I32 i = 0; i < FRAMES_PER_WIDGET; i++) {
		widget->frames[i].drawfunction = -1;
	}
	*self = widget;
	return Success;
}

bbFlag bbWidget_newMockViewport(bbWidget** self, bbGraphics* graphics, bbWidgets* widgets, bbWidget* parent){
	bbWidget* widget;

	bbWidget_newEmpty(&widget, widgets, parent);

	bbScreenPointsRect rect;
	rect.left = 12 * POINTS_PER_PIXEL;
	rect.top = 12 * POINTS_PER_PIXEL;
	rect.width = 466 * POINTS_PER_PIXEL;
	rect.height = 456 * POINTS_PER_PIXEL;

	widget->rect = rect;

	bbPool_Handle drawfunctionHandle;
	bbDictionary_lookup(graphics->drawfunctions->dictionary, "SPRITE", &drawfunctionHandle);

	widget->frames[0].drawfunction = drawfunctionHandle.u64;

	bbDictionary_lookup(graphics->sprites->dictionary,
						"VIEWPORT_480", &widget->frames[0].handle);

	widget->frames[0].offset.x = 0;
	widget->frames[0].offset.y = 0;
	widget->frames[0].framerate = 1.0;

	widget->frames[0].type = Sprite;


	for (I32 i = 1; i < FRAMES_PER_WIDGET; i++) {
		widget->frames[i].drawfunction = -1;
	}

	*self = widget;
}

bbFlag bbWidget_newViewport(bbWidget** self, bbGraphics* graphics,
                            bbWidgets* widgets, bbWidget* parent,
                            void* viewport){

    bbWidget* widget;
    bbWidget_newEmpty(&widget, widgets, parent);
    widget->extra_data = viewport;

    bbScreenPointsRect rect;
    rect.left = 12 * POINTS_PER_PIXEL;
    rect.top = 12 * POINTS_PER_PIXEL;
    rect.width = 466 * POINTS_PER_PIXEL;
    rect.height = 456 * POINTS_PER_PIXEL;

    widget->rect = rect;

    bbPool_Handle drawfunctionHandle;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "VIEWPORT",
                        &drawfunctionHandle);

    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    for (I32 i = 1; i < FRAMES_PER_WIDGET; i++) {
        widget->frames[i].drawfunction = -1;
    }
}

bbFlag bbWidgets_draw(bbWidgets* widgets, void* cl) {

    bbTree* tree = widgets->tree;
    bbVPool* pool = tree->pool;
    void* root;
    bbVPool_lookup(pool, &root, tree->root);
    return bbTree_descendingMap(tree, root, bbWidget_drawFunc, cl);
}