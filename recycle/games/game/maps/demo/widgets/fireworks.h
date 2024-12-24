/**
 * @file
 * @brief The functions in this folder define the behavior of an object with class bbWidget and type fireworks
 */

#include "recycle/headers/bbPrintf.h"
#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbMap.h"
#include "recycle/headers/bbIntTypes.h"

///	Spawn a null widget on selected map at coordinates mc
I32 bbWidgetNew_Fireworks(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){


	bbPool* pool = widgets->m_Pool;
	bbDictionary* dict = widgets->m_AddressDict;

	bbWidget* widget;
	I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");

    widget->m_String = "Fireworks XD";

	bbScreenCoordsF SCF;
	bbScreenCoordsI SCI;
	SCF.x = 40;
	SCF.y = 315;
	SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
	widget->m_ScreenCoords = SCI;

	widget->m_AnimationInt[0] = 23; //Fireworks
	widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "animation");
    widget->m_AnimationStart[0] = 0;

	*reference = widget;

	return f_Success;
}

/// Update widget
I32 bbWidget_fireworks_update(bbWidget* widget){
	return f_Success;
}

/// Send a command to the widget / update widget, etc
I32 bbWidget_fireworks_onCommand(bbWidget* widget, void* command){
	return f_Success;
}

/// Delete widget
I32 bbWidget_fireworks_delete(bbWidget* widget){
	return f_Success;
}

/// Draw widget to screen
I32 bbWidget_fireworks_draw(bbWidget* widget){
	return f_Success;
}
