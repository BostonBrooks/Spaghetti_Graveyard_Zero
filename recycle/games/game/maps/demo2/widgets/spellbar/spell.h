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

//typedef I32 bbWidget_Mouse(void* void_mouseEvent, void* void_widget);
I32 bbWidgetClick_Spell(void* void_mouseEvent, void* void_widget){


	return f_Continue;

	// if not on cooldown,
	  // request activate spell via spellbar

}

//typedef I32 bbWidget_OnCommand (bbWidget* widget, void* data);
I32 bbWidgetCommand_Spell(bbWidget* widget, void* command){

	bbCommandEmpty* commandEmpty = command;

	switch (commandEmpty->type) {

        case c_SetCurrentSpell: {

            //if the spell is available, message spellbar to set current spell
            //request answer from prompt
            return f_None;
        }
        case c_ReturnAnswer: {

            //if answer is correct, request click vie prompt
            //request click from viewport

            //else ask new question
        }
        case c_ReturnClick: {
            //if spell is ready, send message to viewport to cast spell
        }
		default:
			bbDebug("spell: Command %d not found\n", commandEmpty->type);
			return f_None;

	}
}

