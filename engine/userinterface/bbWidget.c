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


#include "engine/graphics/bbGraphicsApp.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/logic/bbTree.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/logic/bbBloatedPool.h"
#include "engine/userinterface/bbWidgetFunctions.h"
#include "engine/viewport/bbViewport.h"

bbFlag bbWidgets_init(bbWidgets* widgets){
	bbVPool_newBloated(&widgets->pool, sizeof(bbWidget), 1024, 1024);
	bbTree_new(&widgets->tree, widgets->pool, offsetof(bbWidget, tree));

	bbDictionary_new(&widgets->dict, nextPrime(256));
    bbWidgetFunctions_new(&widgets->functions);

	bbWidgetFunctions_populate(widgets->functions);
}







//bbFlag testFunc(bbTree* tree, void* node, void* cl)
bbFlag bbWidget_drawFunc(bbTree* tree, void* node, void* cl){
	bbWidget* widget = node;
	return bbWidget_draw(widget, cl);

}

bbFlag bbWidget_draw(bbWidget* widget, drawFuncClosure* cl){
	for (I32 i = 0; i < FRAMES_PER_WIDGET; i++){
		bbFrame* frame = &widget->frames[i];

		bbGraphicsApp* graphics = cl->graphics;
		if (frame->drawfunction >= 0 && frame->drawfunction < graphics->drawfunctions->num) {

			bbDrawFunction *drawFunction =
                    graphics->drawfunctions->functions[frame->drawfunction];

			drawFunction(widget, frame, cl);

		}
	}
}

bbFlag bbWidget_onCommand(bbWidget* widget, bbWidgets* widgets, bbWidgetCommandType type, bbPool_Handle data)
{
	I32 funcInt = widget->ftable.OnCommand;
	if (funcInt < 0) return None;
	bbFlag (*funcPtr)(bbWidget*, bbWidgetCommandType, bbPool_Handle);
	funcPtr = widgets->functions->OnCommands[funcInt];
	return funcPtr(widget, type, data);
}


bbFlag bbWidget_hide(bbWidget* widget, bbWidgets* widgets)
{

	I32 funcInt = widget->ftable.Hide;
	if (funcInt < 0) return None;
	bbHere();
	bbFlag (*funcPtr)(bbWidget* widget, bbWidgets* widgets);
	funcPtr = widgets->functions->Hide[funcInt];
	return funcPtr(widget, widgets);
}
bbFlag bbWidget_unhide(bbWidget* widget, bbWidgets* widgets)
{

	I32 funcInt = widget->ftable.Unhide;
	if (funcInt < 0) return None;
	bbHere();
	bbFlag (*funcPtr)(bbWidget* widget, bbWidgets* widgets);
	funcPtr = widgets->functions->Unhide[funcInt];
	return funcPtr(widget, widgets);
}

bbFlag bbWidget_newEmpty(bbWidget** self, bbWidgets* widgets, bbWidget* parent){
	bbWidget* widget; bbPool_Handle widgetHandle;
	bbVPool_alloc(widgets->pool, (void**) &widget);
	bbVPool_reverseLookup(widgets->pool, widget, &widgetHandle);

	widget->tree.visible = true;
	widget->tree.childrenvisible = true;

	//Every widget is either the root or has a parent? may loosen this restriction later...
	if (parent == NULL){
		widgets->tree->root = widgetHandle;
	} else {
		bbTreeNode_setParent(widgets->tree, widget, parent);
	}

	widget->rect.left = 0;
	widget->rect.top = 0;
	widget->rect.width = 0;
	widget->rect.height = 0;


	widget->mtable.isOver = -1;
	widget->mtable.Enter = -1;
	widget->mtable.Leave = -1;
	widget->mtable.LeftDown = -1;
	widget->mtable.LeftUp = -1;
	widget->mtable.LeftDrag = -1;
	widget->mtable.RightDown = -1;
	widget->mtable.RightUp = -1;
	widget->mtable.RightDrag = -1;
	widget->mtable.Drop = -1;
	widget->mtable.MouseIcon = -1;
	widget->mtable.DragIcon = -1;
	widget->mtable.hover = false;
	widget->mtable.selected = false;

	widget->ftable.Constructor = -1;
	widget->ftable.Update = -1;
	widget->ftable.Destructor = -1;
	widget->ftable.OnCommand = -1;
	widget->ftable.OnTimer = -1;
	widget->ftable.Hide = -1;
	widget->ftable.Unhide = -1;


	for (I32 i = 0; i < FRAMES_PER_WIDGET; i++) {
		widget->frames[i].drawfunction = -1;
	}

	widget->type = bbWidgetType_None;
	widget->state = bbWidgetState_Default;
	widget->isFrozen = false;

	*self = widget;
	return Success;
}

bbFlag bbWidget_newLayout(bbWidget** self, bbGraphicsApp* graphics, bbWidgets* widgets, bbWidget* parent){

	bbWidget* widget;

	bbWidget_newEmpty(&widget, widgets, parent);

	bbScreenPointsRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.width = 720 * SCREEN_PPP;
	rect.height = 480 * SCREEN_PPP;

	widget->rect = rect;

	bbPool_Handle drawfunctionHandle;
	bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETSPRITE", &drawfunctionHandle);

	widget->frames[0].drawfunction = drawfunctionHandle.u64;

	bbDictionary_lookup(graphics->sprites->dictionary,
						"LAYOUT_480", &widget->frames[0].handle);

    //bbDebug("LAYOUT_480 = %d\n", widget->frames[0].handle.u64);
	widget->frames[0].offset.x = 0;
	widget->frames[0].offset.y = 0;



	int funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                       MouseIsOver, "ALWAYS");
	bbDebug("funcInt = %d\n", funcInt);
	widget->mtable.isOver = funcInt;

    widget->mtable.Enter = -1;
    widget->mtable.Leave = -1;
    widget->mtable.LeftDown = -1;
    widget->mtable.LeftUp = -1;

    widget->mtable.LeftDrag = -1;

    widget->mtable.MouseIcon = 91;
    widget->mtable.DragIcon = -1;

	for (I32 i = 1; i < FRAMES_PER_WIDGET; i++) {
	    widget->frames[i].drawfunction = -1;
	}

	bbPool_Handle handle;
	bbVPool_reverseLookup(widgets->pool, widget, &handle);
	bbDictionary_add(widgets->dict, "LAYOUT", handle);

	*self = widget;

    return Success;
}



bbFlag bbWidget_newViewport(bbWidget** self, bbGraphicsApp* graphics,
                            bbWidgets* widgets, bbWidget* parent,
                            void* viewport){

    bbWidget* widget;
    bbWidget_newEmpty(&widget, widgets, parent);
    widget->extra_data = viewport;

    bbViewport* viewport1 = viewport;
    viewport1->widget = widget;


    bbScreenPointsRect rect;
    rect.left = 12 * POINTS_PER_PIXEL;
    rect.top = 12 * POINTS_PER_PIXEL;
    rect.width = 466 * POINTS_PER_PIXEL;
    rect.height = 456 * POINTS_PER_PIXEL;


	int funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
                                          MouseIsOver,
                                      "VIEWPORT");
	widget->mtable.isOver = funcInt;

	funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,
										  MouseLeftDown,
									  "VIEWPORT");
	widget->mtable.LeftDown = funcInt;

	widget->mtable.MouseIcon = 85;
    widget->mtable.DragIcon = -1;

    widget->mtable.Enter = -1;
    widget->mtable.Leave = -1;
    widget->mtable.LeftUp = -1;
    widget->mtable.LeftDrag = -1;

    widget->rect = rect;

    bbPool_Handle drawfunctionHandle;

    bbDictionary_lookup(graphics->drawfunctions->dictionary, "WIDGETVIEWPORT",
                        &drawfunctionHandle);

    widget->frames[0].drawfunction = drawfunctionHandle.u64;

    for (I32 i = 1; i < FRAMES_PER_WIDGET; i++) {
        widget->frames[i].drawfunction = -1;
    }

	bbPool_Handle handle;
	bbVPool_reverseLookup(widgets->pool, widget, &handle);
	bbDictionary_add(widgets->dict, "VIEWPORT", handle);


    *self = widget;

    return Success;

}

bbFlag bbWidgets_draw(bbWidgets* widgets, void* cl) {

    bbTree* tree = widgets->tree;
    bbVPool* pool = tree->pool;
    void* root;
    bbVPool_lookup(pool, &root, tree->root);
    return bbTree_descendingMapVisible(tree, root, bbWidget_drawFunc, cl);
}



bbFlag bbWidget_constructor(bbWidget** self, bbWidgets* widgets, bbGraphicsApp* graphics,
	bbScreenPoints location, bbWidget* parent, char* key)
{
	bbWidget_Constructor* function;
	bbWidgetFunctions_getFunction((void**)&function,widgets->functions,WidgetConstructor, key);
	bbWidget* widget;
	function(&widget, graphics,widgets,location, parent);

    *self = widget;
	return Success;
}
