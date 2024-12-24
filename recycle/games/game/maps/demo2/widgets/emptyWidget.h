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

/// set the default values and add to tree data structure
I32 bbWidget_empty_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){
    bbPool* pool =  widgets->m_Pool;
    bbDictionary* dict = widgets->m_AddressDict;
    bbWidget* widget;
    I32 flag;
    flag = bbPool_New(&widget, pool, f_PoolNextAvailable);

    for(I32 i = 0; i < subwidgetarraysize; i++){
        widget->m_SubwidgetArray[i] = f_None;
    }
    widget->p_Node.p_Tree.Visible = true;
    widget->p_Node.p_Tree.SubwidgetsVisible = true;

    widget->m_ScreenCoords = sc;
    widget->m_Dimensions.x = f_None;
    widget->m_Dimensions.y = f_None;

    widget->m_String = "Initialised empty widget";
	widget->m_String2 = NULL;

    widget->m_Text = NULL;
    widget->m_TextRows = f_None;
    widget->m_TextRows = f_None;
    widget->m_Code = "007";

    for (I32 i = 0; i < ANIMATIONS_PER_WIDGET; i++){
        widget->m_AnimationInt[i] = f_None;
        widget->m_Angle[i] = 0;
        widget->m_Frame[i] = 0;
        widget->v_DrawFunction[i] = f_None;
        widget->m_AnimationStart[i] = f_None;
    }

    widget->s_State = f_None;
    widget->v_OnCommand = f_None;
    widget->v_OnUpdate = f_None;
    widget->v_OnDelete = f_None;
    widget->v_OnMouse = f_None;
    widget->v_OnTimer = f_None;

    widget->m_CoolDownStart = f_None;
    widget->m_CoolDownEnd = f_None;
    widget->m_RedRect = NULL;
    widget->m_GreenRect = NULL;

    widget->m_ExtraData = NULL;

    bbNode_setParent(widget, parent, pool);

    *reference = widget;
    return f_Success;
}