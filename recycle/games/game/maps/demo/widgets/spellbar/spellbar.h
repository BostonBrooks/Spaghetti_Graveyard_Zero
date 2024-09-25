/** The spellbar acts an an interface between the current spell,
 * user interface and game
*/

#include "recycle/headers/bbPrintf.h"
#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbMap.h"
#include "recycle/headers/bbIntTypes.h"
#include "recycle/headers/bbCommands.h"

//typedef I32 bbWidget_Constructor (bbWidget** reference, void* widgets, bbScreenCoordsI screen_coords, bbWidget* parent);
I32 bbWidgetNew_Spellbar2(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){
	//construct widget
	bbWidget* widget;
	bbPool* pool = widgets->m_Pool;
	//there will be one key-value pair for each widget
	bbDictionary* dict = widgets->m_AddressDict;
	I32 map = widgets->m_Pool->m_Map;
	I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

	bbWidgetFunctions* functions = widgets->m_Functions;

	widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "spellbar");

	widget->m_String = "Spell Bar";
	widget->m_AnimationInt[0] = 24; // SPELLBAR
	widget->m_Frame[0] = 1;         // SHOWHIDE
	widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");
    widget->v_OnCommand = bbWidgetFunctions_getInt(functions, f_WidgetOnCommand, "spellbar");

	bbScreenCoordsF SCF;
	bbScreenCoordsI SCI;

	float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
	SCF.x = 80 * widgetScale;
	SCF.y = 80 * widgetScale;
	SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
	widget->m_Dimensions = SCI;
	//call constructors for spell buttons

	SCF = bbScreenCoordsI_getF(sc, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
	SCF.x += 80 * widgetScale;
	SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);



	bbWidget* spell;
	I32 type = bbWidgetFunctions_getInt(functions, f_WidgetConstructor, "spell");
	bbWidget_new(&spell, widgets, type, widget->p_Node.p_Pool.Self, SCI);


	bbDebug("spell2->self = %d\n", spell->p_Node.p_Pool.Self);
	bbWidget* spell2;
	SCF.x += 80 * widgetScale;
	SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
	type = bbWidgetFunctions_getInt(functions, f_WidgetConstructor, "spell2");
	bbWidget_new(&spell2, widgets, type, widget->p_Node.p_Pool.Self, SCI);

	bbDebug("spell2->self = %d\n", spell2->p_Node.p_Pool.Self);
	bbCommandEmpty cmd;
	cmd.type = c_SetIdle;
	bbWidget_onCommand(&cmd, widget);
	bbWidget_onCommand(&cmd, spell);
	bbWidget_onCommand(&cmd, spell2);

    *reference = widget;

	return f_Success;
}

//typedef I32 bbWidget_Mouse(void* void_mouseEvent, void* void_widget);
I32 bbWidgetClick_Spellbar(void* void_mouseEvent, void* void_widget){
	// Show/hide spell buttons (may wish to display cooldown bars)
	bbMouseEvent* event = void_mouseEvent;
	bbWidget* widget = void_widget;
	bbScreenCoordsI sc = event->m_ScreenCoords;
	if (event->m_type == f_MouseLeft) {

		if (bbWidget_containsPoint(widget, event->m_ScreenCoords)) {

			bbPrintf("You clicked the spell bar\n");
			bbWidget* prompt = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_Prompt;

			bbCommandStr cmd;
			cmd.type = c_RequestAnswer;
			cmd.m_str = "Did you just click the spellbar?";


			bbWidget_onCommand(&cmd, prompt);

			return f_Break;
		}
		return f_Continue;
	}
	return f_Continue;
}

//typedef I32 bbWidget_OnCommand (bbWidget* widget, void* data);
I32 bbWidgetCommand_Spellbar(bbWidget* widget, void* command){

	bbCommandEmpty* commandEmpty = command;

	switch (commandEmpty->type) {
		case c_SetIdle:
		{
			widget->s_State = s_Idle;

			//send command to spell and prompt?
			return f_Success;
		}
		case c_RequestCode:
		{
			widget->s_State = s_WaitingForCode;
			//pass request to prompt
			return f_Success;
		}
		case c_ReturnCode:
		{
            bbCommandStr* cmdStr = command;

			//deactivate current spell

            bbDictionary* codeDict = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_CodeDict;
            bbWidget* prompt = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_Prompt;
            I32 spellInt = bbDictionary_lookup(codeDict, cmdStr->m_str);
            if (spellInt == f_None){

                bbCommandStr cmdStr2;
                cmdStr2.type = f_PromptAddDialogue;
                cmdStr2.m_str = "\nspell code not recognised";
                bbWidget_onCommand(&cmdStr2, prompt);
                bbCommandEmpty cmdEmpty;
                cmdEmpty.type = c_RequestCode;
                bbWidget_onCommand(&cmdEmpty, prompt);
                return f_Success;
			}

			//request activate spell given by code
				//if returns "on cooldown", request code from
				// prompt
            bbWidget* spell;
            bbPool* pool = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_Pool;
            bbPool_Lookup(&spell, pool, spellInt);
            //bbDebug("spell->string = %s\n", spell->m_String);
            bbCommandStr cmdStr3;
            cmdStr3.type = f_PromptAddDialogue;
            char str[128];
            sprintf(str, "\nYou entered the code for %s", spell->m_String);
            cmdStr3.m_str = str;
            bbWidget_onCommand(&cmdStr3, prompt);

			//request new spell

			bbCommandEmpty cmdEmpty;
			cmdEmpty.type = c_ActivateSpell;
			I32 flag = bbWidget_onCommand(&cmdEmpty, spell);
			//bbDebug("flag = %d\n", flag);
			if(flag == f_Success){

				I32 lastSpell = widget->m_SubwidgetArray[0];
				widget->m_SubwidgetArray[0] = spell->p_Node.p_Pool.Self;
				bbWidget* oldSpell;
				if (lastSpell >= 0) {
					bbPool_Lookup(&oldSpell, pool, lastSpell);
					bbCommandEmpty cmdEmpty2;
					cmdEmpty2.type = c_DeactivateSpell;
					bbWidget_onCommand(&cmdEmpty2, oldSpell);
				}
			}

			return f_Success;
		}
		case c_ActivateSpell:
		{
			//activate which spell?
			return f_Success;
		}
		case c_DeactivateSpell:
		{
			//pass command to active spell
			return f_Success;
		}
		case c_RequestClick:
		{
			bbDialog("\nRequested click");

			bbWidget* prompt = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_Prompt;
			bbWidget_onCommand(command, prompt);
			bbWidget* viewport = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_Viewport;
			bbWidget_onCommand(command, viewport);

			widget->s_State = s_WaitingForClick;
			return f_Success;
		}
		case c_ReturnClick:
		{
			if (widget->s_State == s_WaitingForClick){
				bbCommand2I* cmd2I = command;

				I32 spellInt = widget->m_SubwidgetArray[0];
				bbWidget* spell;
				bbPool* pool = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_Pool;
				bbPool_Lookup(&spell, pool, spellInt);

				bbDialog("\ncast %s", spell->m_String);

				bbWidget_onCommand(command, spell);


				/*
				bbCommand3I cmd3I;
				cmd3I.type = c_CastSpell;
				cmd3I.m_intx = cmd2I->m_intx;
				cmd3I.m_inty = cmd2I->m_inty;
				//Sphere
				cmd3I.m_intz = 29;

				bbWidget* viewport = g_Game->m_Maps[g_Game->m_CurrentMap]->m_Widgets->m_Viewport;

				bbWidget_onCommand(&cmd3I, viewport);

				 */
				return f_Success;
			}
			//pass click to active spell
			return f_Success;
		}
		case c_RequestAnswer:
		{
			//pass request to prompt

			bbCommandStr* cmdStr = command;

			bbWidget* prompt = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_Prompt;

			bbWidget_onCommand(cmdStr, prompt);

			//state = waiting for answer?
			return f_Success;
		}
		case c_ReturnAnswer:
		{
			bbCommandStr* cmdStr = command;

			//bfbgfbbPrintf("Answer = %s\n", cmdStr->m_str);

			I32 spellInt  = widget->m_SubwidgetArray[0];
			bbWidget* spell;
			bbPool* pool = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_Pool;
			bbPool_Lookup(&spell, pool, spellInt);
			bbWidget_onCommand(cmdStr, spell);
			//pass answer to active spell
			return f_Success;
		}
		/* //used to pass command from spell to viewport
		case c_CastSpell:
		{

			return f_Success;
		} */
		default:
			bbDebug("command not found\n");
			return f_None;

	}
}

