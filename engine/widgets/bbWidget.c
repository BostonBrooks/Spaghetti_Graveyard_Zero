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
#include "engine/widgets/bbWidgetFunctions.h"

bbFlag bbWidgets_init(bbWidgets* widgets){
	bbVPool_newBloated(&widgets->pool, sizeof(bbWidget), 1024, 1024);
	bbTree_new(&widgets->tree, widgets->pool, offsetof(bbWidget, tree));

    bbWidgetFunctions_new(&widgets->functions);

	bbWidgetFunctions_populate(widgets->functions);
}



//bbFlag testFunc(bbTree* tree, void* node, void* cl)
bbFlag bbWidget_mouseFunc(bbTree* tree, void* node, void* cl){

	bbWidget* widget = node;
	mouseActionClosure* closure = cl;
	return bbWidget_mouse(widget, closure->event, closure->functions0);
}

bbFlag bbWidget_mouse(bbWidget* widget, bbMouseEvent* mouseEvent,
                      bbWidgetFunctions0* functions){

	I32 mouseInt = widget->ftable.MouseHandler;


	bbWidget_Mouse* func = functions->MouseHandler[mouseInt];
    bbAssert(func != NULL, "Bad bbWidget_Mouse* func\n");
	return func(widget,mouseEvent);

	return Continue;
}

//bbFlag testFunc(bbTree* tree, void* node, void* cl)
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
	bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSPRITE", &drawfunctionHandle);

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

    return Success;
}

bbFlag bbWidget_newEmpty(bbWidget** self, bbWidgets* widgets, bbWidget* parent){
	bbWidget* widget; bbPool_Handle widgetHandle;
	bbVPool_alloc(widgets->pool, (void**) &widget);
	bbVPool_reverseLookup(widgets->pool, widget, &widgetHandle);

	widget->tree.visible = true;
	widget->tree.childrenvisible = true;

	widget->onMouse.onMouse = 0;

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
	bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSPRITE", &drawfunctionHandle);

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

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETVIEWPORT",
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
    return bbTree_descendingMapVisible(tree, root, bbWidget_drawFunc, cl);
}

//in the following function, cl contains fields such as mouse coordinates, mouse action
bbFlag bbWidgets_onMouse(bbWidgets* widgets, void* cl) {

	bbTree* tree = widgets->tree;
	bbVPool* pool = tree->pool;
	void* root;
	bbVPool_lookup(pool, &root, tree->root);
	return bbTree_ascendingMapVisible(tree, root, bbWidget_mouseFunc, cl);
}

bbFlag bbWidget_constructor(bbWidget** self, bbWidgets* widgets, bbGraphics* graphics,
	bbScreenPoints location, bbWidget* parent, char* key)
{
	bbWidget_Constructor* function;
	bbWidgetFunctions_getFunction((void**)&function,widgets->functions,WidgetConstructor, key);
	bbWidget* widget;
	function(&widget, graphics,widgets,location, parent);

    *self = widget;
	return Success;
}
