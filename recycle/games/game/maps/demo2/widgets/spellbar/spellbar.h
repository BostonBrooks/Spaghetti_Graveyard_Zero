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
I32 bbWidgetNew_Spellbar(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){
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



	bbCommandEmpty cmd;
	cmd.type = c_SetIdle;
	bbWidget_onCommand(&cmd, widget);
	bbWidget_onCommand(&cmd, spell);

    *reference = widget;

	return f_Success;
}

//typedef I32 bbWidget_Mouse(void* void_mouseEvent, void* void_widget);
I32 bbWidgetClick_Spellbar(void* void_mouseEvent, void* void_widget){

	return f_Continue;
}

//typedef I32 bbWidget_OnCommand (bbWidget* widget, void* data);
I32 bbWidgetCommand_Spellbar(bbWidget* widget, void* command){

	bbCommandEmpty* commandEmpty = command;

	switch (commandEmpty->type) {
        case c_ReturnCode: {

            //lookup spell, send wakeup message to spell
            return f_None;
        }

        case c_ReturnAnswer: {

            //pass answer to current spell
            return f_None;
        }
        case c_ReturnClick: {

            //pass click to current spell
            return f_None;
        }
        case c_SetCurrentSpell: {

            //spell informs spellbar that it is the current spell
            return f_None;
        }
		default:
			bbDebug("Spellbar: Command %d not found\n", commandEmpty->type);
			return f_None;

	}
}

