/**
 * @file
 * @brief The functions in this folder define the behavior of an object with class bbWidget and type prompt
 */

#include "recycle/headers/bbPrintf.h"

#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbMap.h"

I32 bbWidget_Prompt_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, I32 parent){

	bbPool* pool = widgets->m_Pool;

	//TODO make more use of this
	bbDictionary* dict = widgets->m_AddressDict;

	bbWidget* widget;
	I32 flag;
	flag = bbPool_New(&widget, pool, f_PoolNextAvailable);

	widgets->m_TextInput = widget;

	//ignore sc argument
	bbScreenCoordsI SC;
	SC.x = 872 * g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants.ScreenPPP;
	SC.y = 23  * g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants.ScreenPPP;
	widget->m_ScreenCoords = SC;


	SC.x = 386 * g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants.ScreenPPP;
	SC.y = 450  * g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants.ScreenPPP;
	widget->m_Dimensions = SC;

	widget->m_Visible = true;
	widget->m_SubwidgetsVisible = true;

	//widget->m_SpriteInt = f_None;

	for(I32 i = 0; i < ANIMATIONS_PER_WIDGET; i++){
		widget->m_AnimationInt[i] = f_None;
		widget->m_Angle[i] = 0;
		widget->m_Frame[i] = 0;
		widget->m_AnimationDraw[i] = f_None;
	}

	widget->m_String = calloc(1024, sizeof(char));

	strcpy(widget->m_String, "welcome to Jurassic Park");

	widget->m_Text = sfText_create();
	sfText_setString(widget->m_Text, widget->m_String);
	widget->m_Font = sfFont_createFromFile("../games/game/graphics/Bowman.ttf");
	bbAssert(widget->m_Font != NULL, "Could not load font\n");
	sfText_setFont(widget->m_Text, widget->m_Font);
	bbScreenCoordsF SCF = bbScreenCoordsI_getF(widget->m_ScreenCoords, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
	sfVector2f position;
	position.x = SCF.x;
	position.y = SCF.y;
	sfText_setPosition(widget->m_Text, position);
	sfText_setColor(widget->m_Text, sfBlack);

	bbWidgetFunctions* functions = widgets->m_Functions;
	//widget->v_OnDraw = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "prompt");
	widget->v_OnCommand = bbWidgetFunctions_getInt(functions, f_WidgetOnCommand, "prompt");

	bbWidget* parentWidget;
	flag = bbPool_Lookup(&parentWidget, pool, parent);

	//add widget to parentWidget's subwidgets

    bbNode_setParent(widget, parentWidget, pool);
	//////////////////////////////////// TODO

	*reference = widget;

}
I32 bbWidget_Prompt_update(bbWidget* widget);
I32 bbWidget_Prompt_onCommand(bbWidget* widget, I32 command, void* data){

	return f_Success;
}
I32 bbWidget_Prompt_delete(bbWidget* widget);
I32 bbWidget_Prompt_draw(bbWidget* widget){

	sfRenderWindow_drawText(g_Game->m_Window, widget->m_Text, NULL);
	return f_Success;
}
