/** This spell is a prototype for widgets that control the casting of spells
*
 *
*/

#include "headers/bbPrintf.h"
#include "headers/bbGeometry.h"
#include "headers/bbWidget.h"
#include "headers/bbGame.h"
#include "headers/bbMap.h"
#include "headers/bbIntTypes.h"
#include "headers/bbCommands.h"

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

	widget->m_String = "Spell";
	widget->m_AnimationInt[0] = 24; // SPELLBAR
	widget->m_Frame[0] = 2;         // PLUS
	widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");


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

    return f_Success;
}

//typedef I32 bbWidget_Mouse(void* void_mouseEvent, void* void_widget);
I32 bbWidgetClick_Spell(void* void_mouseEvent, void* void_widget){

	bbMouseEvent* event = void_mouseEvent;
	bbWidget* widget = void_widget;
	bbScreenCoordsI sc = event->m_ScreenCoords;
	if (event->m_type == f_MouseLeft) {
		bbHere();
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
			return f_Success;
		}
		case c_DeactivateSpell:
		{
			//deactivate this spell
			return f_Success;
		}
		case c_RequestClick:
		{
			//pass request to spellbar
			return f_Success;
		}

		case c_ReturnClick:
		{
			//cast spell  (/ send command to viewport)
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

