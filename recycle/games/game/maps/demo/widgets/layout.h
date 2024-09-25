/**
 * @file
 * @brief The functions in this folder define the behavior of an object with class bbWidget and type NULL
 */
#define BBDEBUG

#include "recycle/headers/bbPrintf.h"

#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbMap.h"
#include "recycle/headers/bbWidgetTimer.h"

///	Spawn a null widget on selected map at coordinates mc
I32 bbWidgetNew_Layout(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){



    bbWidget* widget;
    bbWidget_empty_new(&widget, widgets, sc, NULL);

    bbPrintf("widget -> map = %d\n", widget->p_Node.p_Pool.Map);

    I32 flag;
    widget->m_String = "Layout / Root Widget";

    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "layout");


    bbScreenCoordsF SCF;
    bbScreenCoordsI SCI;

    SCF.x = 0;
    SCF.y = 0;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_ScreenCoords = SCI;

    SCF.x = g_Game->m_GraphicsSettings->m_Width;
    SCF.y = g_Game->m_GraphicsSettings->m_Height;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_Dimensions = SCI;


    widget->m_AnimationInt[0] = bbSprites_lookupInt(g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Sprites,
													g_Game->m_GraphicsSettings->m_Layout);
    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "sprite");


    *reference = widget;
    return f_Success;
}

/// Update widget
I32 bbWidget_Layout_update(bbWidget* widget){}

/// Send a command to the widget / update widget, etc
I32 bbWidget_Layout_onCommand(bbWidget* widget, void* command){}

/// Delete widget
I32 bbWidget_Layout_delete(bbWidget* widget){}

/// Draw widget to screen
I32 bbWidget_Layout_draw(bbWidget* widget){}


/// if you click the layout, nothing happens
I32 bbWidgetClick_Layout(void* void_mouseEvent, void* void_widget){
    bbMouseEvent* event = void_mouseEvent;
    if (event->m_type ==  f_MouseLeft) {
        bbPrintf("You clicked nothing\n");
    }
    return f_Break;

}
