/**
 * @file
 * @brief The functions in this file define the behavior of an object with class bbWidget and type Sphere
 * The sphere does nothing, gets spawned on a click to layout
 * Used to show that clicks are landing in the right position
 *
 */


#include "recycle/headers/bbPrintf.h"
#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbMap.h"
#include "recycle/headers/bbIntTypes.h"

//typedef I32 bbWidget_Constructor (bbWidget** reference, void* widgets, bbScreenCoordsI screen_coords, bbWidget* parent);


I32 bbWidgetNew_Sphere(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent) {
///	Spawn a null widget on selected map at coordinates mc


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;

    bbWidget *widget;
    I32 flag =bbWidget_empty_new(&widget, widgets, sc, parent);


    widget->m_String = "nope";
    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");
    widget->v_OnTimer = bbWidgetFunctions_getInt(functions, f_WidgetOnTimer, "sphere");

    widget->m_AnimationInt[0] = 29; // SPHERE
    widget->m_Frame[0] = 0;         // NOT USED
    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "sprite");

    *reference = widget;
    return f_Success;

}
//typedef I32 bbWidget_Mouse(void* void_mouseEvent, void* void_widget);

/// if you click the widget, it will spawn a sphere
I32 bbWidgetClick_Sphere(void* void_mouseEvent, void* void_widget){
    bbMouseEvent* event = void_mouseEvent;
    bbWidget* widget = void_widget;
    bbScreenCoordsI sc = event->m_ScreenCoords;
    if (event->m_type == f_MouseLeft) {

        if (bbWidget_containsPoint(widget, event->m_ScreenCoords)) {
            I32 map = widget->p_Node.p_Pool.Map;
            bbDebug("map = %d\n", map);
            bbWidgetFunctions *functions = g_Game->m_Maps[map]->m_Widgets->m_Functions;

            I32 type = bbWidgetFunctions_getInt(functions, f_WidgetConstructor, "sphere");
            bbDebug("type = %d\n", type);
            bbWidget *newWidget;
            bbWidget_new(&newWidget, g_Game->m_Maps[map]->m_Widgets, type, widget->p_Node.p_Pool.Self, sc);

            bbWidgetTimerNode* node;
            bbWidgetTimerNode_new(&node, g_Game->m_Maps[map]->m_WidgetTimer);

            node->p_Node.Priority = g_Game->m_Maps[map]->misc.m_MapTime + 300;
            node->i_widget = newWidget->p_Node.p_Pool.Self;

            bbWidgetTimer_add(g_Game->m_Maps[map]->m_WidgetTimer, node);

            return f_Break;
        }
        return f_Continue;
    }
    return f_Continue;

}
///functions->OnTimers[TimerFunction_int](widget, void_timerNode)
I32 bbWidget_Sphere_onTimer(bbWidget* widget, void* void_timernode){
    printf("You spawned a sphere 3 seconds ago\n");
}
