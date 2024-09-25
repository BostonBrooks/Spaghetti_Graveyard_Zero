#include <inttypes.h>
#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbAnimation.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbCommands.h"
#include "recycle/headers/bbIntTypes.h"

//typedef I32 bbWidget_Mouse(void* void_mouseEvent, void* void_widget);

/// if you click the widget, it will printf some text
I32 bbWidgetClick_Text(void* void_mouseEvent, void* void_widget){
/*    bbMouseEvent* event = void_mouseEvent;
    bbWidget* widget = void_widget;

    if (event->m_type == f_MouseLeft) {
        if (bbWidget_containsPoint(widget, event->m_ScreenCoords)) {
            char string[512];
            I32 promptInt = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->misc.m_ActiveTextbox_deprecated;
            bbPool* pool = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_Pool;
            bbWidget* promptWidget;
            bbPool_Lookup(&promptWidget, pool, promptInt);
            I32 dialogueInt = promptWidget->m_SubwidgetArray[0];
            bbWidget* dialogueWidget;
            bbPool_Lookup(&dialogueWidget, pool, dialogueInt);
            sprintf(string,"\nYou clicked %s", widget->m_String);

            bbCommandStr cmd;
            cmd.type = f_CommandPutStr;
            cmd.m_str = string;
            bbWidget_onCommand(&cmd, dialogueWidget);

            g_Game->m_Maps[widget->p_Node.p_Pool.Map]->misc.m_ActiveSpell_deprecated = widget->p_Node.p_Pool.Self;

            return f_Break;
        }
    }
    return f_Continue;
*/
}
