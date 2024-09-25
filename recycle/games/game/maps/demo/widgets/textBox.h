/**
 * @file
 * @brief The functions in this file define the behavior of an object with class bbWidget and type textBox
 *
 */


#include "recycle/headers/bbPrintf.h"
#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbMap.h"
#include "recycle/headers/bbCommands.h"
#include "recycle/headers/bbString.h"
#include "recycle/headers/bbFlags.h"
#include "recycle/headers/bbIntTypes.h"

//typedef I32 bbWidget_Constructor (bbWidget** reference, void* widgets, bbScreenCoordsI screen_coords, bbWidget* parent);
I32 bbWidgetNew_Textbox(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent) {


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;
    I32 map = widgets->m_Pool->m_Map;
    bbWidget *widget;
    I32 flag;
    sfVector2f positionV2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[map]->p_Constants);
    flag = bbPool_New(&widget, pool, f_PoolNextAvailable);
    //TODO value should not be hard coded
    widget->m_String = calloc(1028, sizeof(char));
    bbStr_setStr(widget->m_String, "New Text Box");
    //TODO value should not be hard coded
    widget->m_Text = sfText_create();
    sfText_setPosition(widget->m_Text, positionV2f);
    sfText_setString(widget->m_Text, widget->m_String);

    widget->m_TextColumns =1024;
    widget->m_TextRows = 1024;
    sfText_setFont(widget->m_Text, g_Game->m_Maps[map]->m_Fonts->m_Fonts[0]);
    sfText_setColor(widget->m_Text, sfBlack);
	sfText_setCharacterSize(widget->m_Text, g_Game->m_GraphicsSettings->m_TextSize);



    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");

    widget->v_OnUpdate = f_None;
    widget->v_OnCommand = bbWidgetFunctions_getInt(functions, f_WidgetOnCommand, "textbox");
    widget->v_OnTimer = f_None;
    widget->m_ScreenCoords = sc;

    bbScreenCoordsI SCI;
    //TODO should not be hard coded
    SCI.x = 350 * g_Game->m_Maps[map]->p_Constants.ScreenPPP;
    SCI.y = 350 * g_Game->m_Maps[map]->p_Constants.ScreenPPP;

    widget->m_Dimensions = SCI;

    widget->p_Node.p_Tree.Visible = true;
    widget->p_Node.p_Tree.SubwidgetsVisible = true;

    for (I32 i = 0; i < ANIMATIONS_PER_WIDGET; i++) {
        widget->m_AnimationInt[i] = f_None;
        widget->m_Angle[i] = 0;
        widget->m_Frame[i] = 0;
        widget->v_DrawFunction[i] = f_None;
    }
    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "text");


    bbNode_setParent(widget, parent, pool);

    g_Game->m_Maps[map]->misc.m_ActiveTextbox_deprecated = widget->p_Node.p_Pool.Self;
    *reference = widget;
    return f_Success;
}

//typedef I32 bbWidget_OnCommand (bbWidget* widget, void* data);
I32 bbWidgetCommand_Textbox(bbWidget* widget, void* data){
    bbCommandEmpty* commandEmpty = data;

    switch (commandEmpty->type) {
        case f_CommandPutChar: {
            bbCommandChar *commandPutChar = data;
            bbStr_putChar(widget->m_String, commandPutChar->m_char);
            bbStr_setBounds(widget->m_String, widget->m_TextColumns, widget->m_TextRows);
            sfText_setString(widget->m_Text, widget->m_String);
            break;
        }
        case f_CommandPutStr: {
            bbCommandStr* commandPutStr = data;
            bbStr_putStr(widget->m_String, commandPutStr->m_str);
            bbStr_setBounds(widget->m_String, widget->m_TextColumns, widget->m_TextRows);
            sfText_setString(widget->m_Text, widget->m_String);
            break;
        }
        case f_CommandSetStr: {
            bbCommandStr* commandPutStr = data;
            bbStr_setStr(widget->m_String, commandPutStr->m_str);
            bbStr_setBounds(widget->m_String, widget->m_TextColumns, widget->m_TextRows);
            sfText_setString(widget->m_Text, widget->m_String);
            break;
        }
        case f_CommandSetDim: {

            bbCommand2I* commandSetDim = data;


            widget->m_TextRows = commandSetDim->m_inty;
            widget->m_TextColumns = commandSetDim->m_intx;
            break;
        }
		case c_Clear: {
			bbStr_setStr(widget->m_String, "");
			sfText_setString(widget->m_Text, widget->m_String);
			break;
		}
        default:
        bbDebug("Command not found\n");
    }

}
