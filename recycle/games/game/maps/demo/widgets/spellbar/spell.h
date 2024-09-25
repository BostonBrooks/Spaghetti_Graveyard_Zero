/** This spell is a prototype for widgets that control the casting of spells
*
 *
*/

#include "recycle/headers/bbPrintf.h"
#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbMap.h"
#include "recycle/headers/bbIntTypes.h"
#include "recycle/headers/bbCommands.h"

//typedef I32 bbWidget_Constructor (bbWidget** reference, void* widgets, bbScreenCoordsI screen_coords, bbWidget* parent);
I32 bbWidgetNew_Spell(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){
	//construct widget
	bbWidget* widget;
	bbPool* pool = widgets->m_Pool;
	//there will be one key-value pair for each widget
	bbDictionary* dict = widgets->m_AddressDict;
	I32 map = widgets->m_Pool->m_Map;
	I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

	bbWidgetFunctions* functions = widgets->m_Functions;

	widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "spell");
	widget->v_OnCommand = bbWidgetFunctions_getInt(functions, f_WidgetOnCommand, "spell");
	widget->m_String = "Spell";
	widget->m_String2 = calloc(128, sizeof(char));
	widget->m_AnimationInt[0] = 24; // SPELLBAR
	widget->m_Frame[0] = 2;         // PLUS
	widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");

	widget->m_CoolDownStart = 0;
	widget->m_CoolDownEnd = 3600;

	widget->m_RedRect = sfRectangleShape_create();
	sfColor RedHalfAlpha;
	RedHalfAlpha.r = 255;
	RedHalfAlpha.g = 0;
	RedHalfAlpha.b = 0;
	RedHalfAlpha.a = 127;
	sfRectangleShape_setFillColor(widget->m_RedRect, RedHalfAlpha);

	sfVector2f vector2f;
	vector2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
	sfRectangleShape_setPosition(widget->m_RedRect, vector2f);
	vector2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
	sfRectangleShape_setSize(widget->m_RedRect, vector2f);
	widget->v_DrawFunction[1] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "cooldown");

	bbScreenCoordsF SCF;
	bbScreenCoordsI SCI;

	float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
	SCF.x = 80 * widgetScale;
	SCF.y = 80 * widgetScale;
	SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
	widget->m_Dimensions = SCI;

	//initialise widget

	bbCommandEmpty cmd;
	cmd.type = c_SetIdle;
	bbWidget_onCommand(&cmd, widget);

    bbDictionary* codeDict = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_CodeDict;
    widget->m_Code = "0";
    bbDictionary_add(codeDict, widget->m_Code, widget->p_Node.p_Pool.Self);

	*reference = widget;
    return f_Success;
}
//typedef I32 bbWidget_Constructor (bbWidget** reference, void* widgets, bbScreenCoordsI screen_coords, bbWidget* parent);
I32 bbWidgetNew_Spell2(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){
	//construct widget
	bbWidget* widget;
	bbPool* pool = widgets->m_Pool;
	//there will be one key-value pair for each widget
	bbDictionary* dict = widgets->m_AddressDict;
	I32 map = widgets->m_Pool->m_Map;
	I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

	bbWidgetFunctions* functions = widgets->m_Functions;

	widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "spell");
	widget->v_OnCommand = bbWidgetFunctions_getInt(functions, f_WidgetOnCommand, "spell");
	widget->m_String = "Spell2";
	widget->m_String2 = calloc(128, sizeof(char));
	widget->m_AnimationInt[0] = 24; // SPELLBAR
	widget->m_Frame[0] = 3;         // MINUS?
	widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");

	widget->m_CoolDownStart = 0;
	widget->m_CoolDownEnd = 180;

	widget->m_RedRect = sfRectangleShape_create();
	sfColor RedHalfAlpha;
	RedHalfAlpha.r = 255;
	RedHalfAlpha.g = 0;
	RedHalfAlpha.b = 0;
	RedHalfAlpha.a = 127;
	sfRectangleShape_setFillColor(widget->m_RedRect, RedHalfAlpha);

	sfVector2f vector2f;
	vector2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
	sfRectangleShape_setPosition(widget->m_RedRect, vector2f);
	vector2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
	sfRectangleShape_setSize(widget->m_RedRect, vector2f);
	widget->v_DrawFunction[1] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "cooldown");

	bbScreenCoordsF SCF;
	bbScreenCoordsI SCI;

	float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
	SCF.x = 80 * widgetScale;
	SCF.y = 80 * widgetScale;
	SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
	widget->m_Dimensions = SCI;

	//initialise widget

	bbCommandEmpty cmd;
	cmd.type = c_SetIdle;
	bbWidget_onCommand(&cmd, widget);

	bbDictionary* codeDict = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_CodeDict;
	widget->m_Code = "1";
	bbDictionary_add(codeDict, widget->m_Code, widget->p_Node.p_Pool.Self);

	*reference = widget;
	return f_Success;
}
//typedef I32 bbWidget_Mouse(void* void_mouseEvent, void* void_widget);
I32 bbWidgetClick_Spell(void* void_mouseEvent, void* void_widget){

	bbMouseEvent* event = void_mouseEvent;
	bbWidget* widget = void_widget;
	bbScreenCoordsI sc = event->m_ScreenCoords;
	if (event->m_type == f_MouseLeft) {

		if (bbWidget_containsPoint(widget, event->m_ScreenCoords)) {

			bbPrintf("You clicked the spell\n");
			return f_Break;
		}
		return f_Continue;
	}
	return f_Continue;

	// if not on cooldown,
	  // request activate spell via spellbar

}

//typedef I32 bbWidget_OnCommand (bbWidget* widget, void* data);
I32 bbWidgetCommand_Spell(bbWidget* widget, void* command){

	bbCommandEmpty* commandEmpty = command;

	switch (commandEmpty->type) {
		case c_SetIdle:
		{
			widget->s_State = s_Idle;

			return f_Success;
		}
		/* spell doesnt get requested to return a code
		case c_RequestCode:
		{

		} */
		/* spell doesnt get codes returned to it
		case c_ReturnCode:
		{

			return f_Success;
		}
		 */
		case c_ActivateSpell:
		{
			//activate this spell or return "on cooldown"

			if (g_Game->m_Maps[g_Game->m_CurrentMap]->misc.m_MapTime < widget->m_CoolDownEnd){
				bbDialog("\nSpell on cooldown");
				return f_None;
			}

			bbWidget* spellbar = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_SpellBar;

			if(widget->p_Node.p_Pool.Self == spellbar->m_SubwidgetArray[0]){
				bbDialog("\nSpell already activated");
				return f_None;
			}

			bbDialog("\nspell activated %s", widget->m_String);

			I32 a, b;

			a = rand() % 12;
			b = rand() % 12;

			sprintf(widget->m_String2, "%d", a*b);

			bbCommandStr cmdStr;
			cmdStr.type = c_RequestAnswer;
			char str[128];
			cmdStr.m_str = str;
			sprintf(str, "What is %d x %d?", a, b);

			bbWidget_onCommand(&cmdStr, spellbar);

			widget->s_State = s_WaitingForAnswer;

			bbDialog("\nShould be waiting for answer");
			return f_Success;
		}
		case c_DeactivateSpell:
		{
			//deactivate this spell
			bbPrintf("spell deactivated\n");
			widget->s_State = s_Idle;
			return f_Success;
		}
		case c_RequestClick:
		{
			//pass request to spellbar
			widget->s_State = s_Idle;
			return f_Success;
		}

		case c_ReturnClick:
		{
			bbDialog("\nCast it into the void!");
			return f_Success;
		}
		/* spell usually sends these type of commands
		case c_RequestAnswer:
		{
			//pass request to spellbar
			return f_Success;
		}
		*/
		case c_ReturnAnswer:
		{
			//check answer and request click
			bbCommandStr* cmdStr = command;
			bbDialog("\nyou entered %s\nanswer = %s", cmdStr->m_str, widget->m_String2);
			bbWidget* spellbar = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_SpellBar;

			if (strcmp(cmdStr->m_str, widget->m_String2) == 0){
				bbDialog("\nYour answer was correct");

				bbCommandEmpty cmdEmpty;
				cmdEmpty.type = c_RequestClick;
				bbWidget_onCommand(&cmdEmpty, spellbar);

				return f_Success;
			}

			I32 a, b;

			a = rand() % 12;
			b = rand() % 12;

			sprintf(widget->m_String2, "%d", a*b);

			bbCommandStr cmdStr2;
			cmdStr2.type = c_RequestAnswer;
			char str[128];
			cmdStr2.m_str = str;
			bbPrintf("What is %d x %d?", a, b);
			sprintf(str, "What is %d x %d?", a, b);


			bbWidget_onCommand(&cmdStr2, spellbar);

			widget->s_State = s_WaitingForAnswer;

			bbDialog("\nShould be waiting for answer");
			return f_Success;
		}

		// spell usually sends these types of command
		/* case c_CastSpell:
		{

			return f_Success;
		} */
		default:
			bbDebug("command not found\n");
			return f_None;

	}
}

