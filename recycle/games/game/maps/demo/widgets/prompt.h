/**
 * @file
 * @brief The functions in this file define the behavior of an object with class bbWidget and type prompt
 * Prompt is the parent of three text boxes, the dialogue, 'prompt' and input
 */

#include <inttypes.h>

#include "recycle/headers/bbPrintf.h"
#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbMap.h"
#include "recycle/headers/bbCommands.h"
#include "recycle/headers/bbString.h"
#include "recycle/headers/bbFlags.h"
#include "recycle/headers/bbIntTypes.h"

#define i_spellbar   0
#define i_dialogue   1
#define i_query      2
#define i_answer     3

//typedef I32 bbWidget_Constructor (bbWidget** reference, void* widgets, bbScreenCoordsI screen_coords, bbWidget* parent);
I32 bbWidgetNew_Prompt(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent) {


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;
    I32 map = widgets->m_Pool->m_Map;
    bbWidget *widget;
    I32 flag;
    sfVector2f positionV2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[map]->p_Constants);
    flag = bbWidget_empty_new(&widget, widgets, sc, parent);


    //TODO widget->m_SubwidgetArray[i_spellbar] = g_Game->m_Maps[map]->misc.m_SpellBar_deprecated; is outdated

        //TODO value should not be hard coded?
    widget->m_String = calloc(1028, sizeof(char));
    bbStr_setStr(widget->m_String, "prompt");
    widget->m_Text = sfText_create();
    sfText_setPosition(widget->m_Text, positionV2f);
    sfText_setString(widget->m_Text, widget->m_String);


    sfText_setFont(widget->m_Text, g_Game->m_Maps[map]->m_Fonts->m_Fonts[0]);
    sfText_setColor(widget->m_Text, sfBlack);



    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");
    widget->v_OnCommand = bbWidgetFunctions_getInt(functions, f_WidgetOnCommand, "prompt");


    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "text");




    I32 type = bbWidgetFunctions_getInt(functions, f_WidgetConstructor, "textbox");

    bbWidget* subWidget;

    bbCommand2I cmd;
    cmd.type = f_CommandSetDim;
    bbScreenCoordsI SCI;

    //Dialogue
    cmd.m_inty = g_Game->m_GraphicsSettings->m_DialogueRows;
    cmd.m_intx = g_Game->m_GraphicsSettings->m_TextColumns;

    SCI.x = g_Game->m_GraphicsSettings->m_TextLeft * g_Game->m_Maps[map]->p_Constants.ScreenPPP;
    SCI.y = g_Game->m_GraphicsSettings->m_DialogueTop * g_Game->m_Maps[map]->p_Constants.ScreenPPP;
    flag = bbWidget_new(&subWidget, g_Game->m_Maps[g_Game->m_CurrentMap]->m_Widgets, type, widget->p_Node.p_Pool.Self, SCI);
    bbAssert(flag == f_Success, "bad flag from bbWidget_new()\n");
    widget->m_SubwidgetArray[i_dialogue] = subWidget->p_Node.p_Pool.Self;
    bbWidget_onCommand(&cmd, subWidget);

    cmd.m_inty = 3;
    cmd.m_intx = g_Game->m_GraphicsSettings->m_TextColumns;

    //Query
    SCI.x = g_Game->m_GraphicsSettings->m_TextLeft * g_Game->m_Maps[map]->p_Constants.ScreenPPP;
    SCI.y = g_Game->m_GraphicsSettings->m_QueryTop * g_Game->m_Maps[map]->p_Constants.ScreenPPP;
    flag = bbWidget_new(&subWidget, g_Game->m_Maps[g_Game->m_CurrentMap]->m_Widgets, type, widget->p_Node.p_Pool.Self, SCI);
    bbAssert(flag == f_Success, "bad flag from bbWidget_new()\n");
    widget->m_SubwidgetArray[i_query] = subWidget->p_Node.p_Pool.Self;
    bbWidget_onCommand(&cmd, subWidget);

    cmd.m_inty = 3;
    cmd.m_intx = g_Game->m_GraphicsSettings->m_TextColumns;

    //input
    SCI.x = g_Game->m_GraphicsSettings->m_TextLeft * g_Game->m_Maps[map]->p_Constants.ScreenPPP;
    SCI.y = g_Game->m_GraphicsSettings->m_InputTop * g_Game->m_Maps[map]->p_Constants.ScreenPPP;
    flag = bbWidget_new(&subWidget, g_Game->m_Maps[g_Game->m_CurrentMap]->m_Widgets, type, widget->p_Node.p_Pool.Self, SCI);
    bbAssert(flag == f_Success, "bad flag from bbWidget_new()\n");
    widget->m_SubwidgetArray[i_answer] = subWidget->p_Node.p_Pool.Self;
    bbWidget_onCommand(&cmd, subWidget);


    g_Game->m_Maps[map]->misc.m_ActiveTextbox_deprecated = widget->p_Node.p_Pool.Self;
    *reference = widget;
    return f_Success;
}
//typedef I32 bbWidget_OnCommand (bbWidget* widget, void* data);
I32 bbWidgetCommand_Prompt(bbWidget* widget, void* data){
    bbCommandEmpty* commandEmpty = data;

    switch (commandEmpty->type) {
/*        case f_CommandPutChar: {
            bbCommandChar *commandPutChar = data;
            bbStr_putChar(widget->m_String, commandPutChar->m_char);
            sfText_setString(widget->m_Text, widget->m_String);


            I32 map = widget->p_Pool.p_Pool.Map;
            I32 widget_int;
            bbPool* pool = g_Game->m_Maps[map]->m_Widgets->m_Pool;
            bbWidget* subWidget;
            bbCommandChar cmd;
            cmd.type = f_CommandPutChar;
            cmd.m_char = commandPutChar->m_char;

            //Dialogue
            widget_int = widget->m_SubwidgetArray[i_dialogue];
            bbPool_Lookup(&subWidget, pool, widget_int);
            bbWidget_onCommand(&cmd, subWidget);

            //Query
            widget_int = widget->m_SubwidgetArray[i_query];
            bbPool_Lookup(&subWidget, pool, widget_int);
            bbWidget_onCommand(&cmd, subWidget);

            //input
            widget_int = widget->m_SubwidgetArray[i_answer];
            bbPool_Lookup(&subWidget, pool, widget_int);
            bbWidget_onCommand(&cmd, subWidget);

            break;
        }
        case f_CommandPutStr: {
            bbCommandPutStr *commandPutStr = data;
            bbStr_putStr(widget->m_String, commandPutStr->m_str);
            sfText_setString(widget->m_Text, widget->m_String);
            break;
        }
        */
        case f_PromptSetQuery: {
            bbCommandStr *commandSetString = data;
            bbStr_setStr(widget->m_String, "");
            sfText_setString(widget->m_Text, widget->m_String);


            I32 map = widget->p_Node.p_Pool.Map;
            I32 widget_int;
            bbPool* pool = g_Game->m_Maps[map]->m_Widgets->m_Pool;
            bbWidget* subWidget;
            bbCommandStr cmd;

            //Query
            cmd.type = f_CommandSetStr;
            cmd.m_str = commandSetString->m_str;
            widget_int = widget->m_SubwidgetArray[i_query];
            bbPool_Lookup(&subWidget, pool, widget_int);
            bbWidget_onCommand(&cmd, subWidget);

            //input
            cmd.m_str = "?:";
            widget_int = widget->m_SubwidgetArray[i_answer];
            bbPool_Lookup(&subWidget, pool, widget_int);
            bbWidget_onCommand(&cmd, subWidget);

            break;
        }
        case f_PromptAddChar:  {
            bbCommandChar *commandPutChar = data;


            I32 map = widget->p_Node.p_Pool.Map;
            I32 widget_int;
            bbPool* pool = g_Game->m_Maps[map]->m_Widgets->m_Pool;
            bbWidget* widget1;
            I32 widgetInt1 = widget->m_SubwidgetArray[i_answer];
            bbPool_Lookup(&widget1, pool, widgetInt1);

            if (commandPutChar->m_char == '\n'){
                bbWidget* widget2;
                I32 widgetInt2 = widget->m_SubwidgetArray[i_dialogue];
                bbPool_Lookup(&widget2, pool, widgetInt2);

                char str[128];
                char promptStr[128];
                bbStr_setStr(promptStr, widget->m_String);
                bbCommandStr cmdStr;

                cmdStr.type = f_CommandPutStr;
                cmdStr.m_str = str;
                //sprintf(str, "\nYou entered %s", widget->m_String);
                //bbWidget_onCommand(&cmdStr, widget2);

                cmdStr.type = f_CommandSetStr;
                cmdStr.m_str = "";
                bbWidget_onCommand(&cmdStr, widget1);

                bbStr_setStr(widget->m_String, "");
                //Send message to spellbar

                bbCommandStr cmdStr2;
                cmdStr2.m_str = promptStr;

                bbWidget* spellbar = g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_SpellBar;

                switch (widget->s_State){
                    case s_WaitingForCode:
                        cmdStr2.type = c_ReturnCode;
                        break;
                    case s_WaitingForAnswer:
                        cmdStr2.type = c_ReturnAnswer;
                        break;
                    default:
                        cmdStr2.type = c_ReturnCode;
                        break;
                }
                bbWidget_onCommand(&cmdStr2, spellbar);
                break;
            } else {
                bbCommandChar cmd;
                cmd.type = f_CommandPutChar;
                cmd.m_char = commandPutChar->m_char;

                //input
                bbWidget_onCommand(&cmd, widget1);

                bbStr_putChar(widget->m_String, commandPutChar->m_char);

                //bbPrintf("Prompt: %s\n", widget->m_String);

                break;
            }
        }
        case f_PromptReturnAnswer: {     //bbCharacter.h requests current answer, sends to spellbar
            bbCommandStr* cmd = data;

            //return answer to caller
            cmd->type = f_PromptReturnAnswer;

            //cmd->str must point to a char buffer
            strcpy(cmd->m_str, widget->m_String);

            //gather data
            I32 map = widget->p_Node.p_Pool.Map;
            I32 widget_int;
            bbPool* pool = g_Game->m_Maps[map]->m_Widgets->m_Pool;
            bbWidget* subWidget;
            bbCommandStr cmd2;

            //reset answer widget
            cmd2.type = f_CommandSetStr;
            cmd2.m_str = "/:";

            widget_int = widget->m_SubwidgetArray[i_answer];
            bbPool_Lookup(&subWidget, pool, widget_int);
            bbWidget_onCommand(&cmd2, subWidget);

            //reset answer stored in prompt
            bbStr_setStr(widget->m_String, "");
            sfText_setString(widget->m_Text, widget->m_String);
            break;
        }
        case f_PromptAddDialogue: {
            bbCommandStr *commandPutStr = data;

            bbCommandStr cmd;
            cmd.type = f_CommandPutStr;
            cmd.m_str = commandPutStr->m_str;

            //gather data
            I32 map = widget->p_Node.p_Pool.Map;
            I32 widget_int;
            bbPool* pool = g_Game->m_Maps[map]->m_Widgets->m_Pool;
            bbWidget* subWidget;
            widget_int = widget->m_SubwidgetArray[i_dialogue];
            bbPool_Lookup(&subWidget, pool, widget_int);
            bbWidget_onCommand(&cmd, subWidget);



            break;
        }
		case c_RequestCode: {


			//set m_String to ""
			widget->m_String[0] = '\0';
			sfText_setString(widget->m_Text, widget->m_String);
			widget->s_State = s_WaitingForCode;

			//set query to "select spell"
			bbCommandStr cmd2;
			cmd2.type = f_CommandSetStr;
			cmd2.m_str = "Select spell";

			//gather data
			I32 map = widget->p_Node.p_Pool.Map;
			I32 widget_int;
			bbPool* pool = g_Game->m_Maps[map]->m_Widgets->m_Pool;

			// Set Question
			bbWidget* subWidget;
			widget_int = widget->m_SubwidgetArray[i_query];
			bbPool_Lookup(&subWidget, pool, widget_int);
			bbWidget_onCommand(&cmd2, subWidget);
			//set input to ""
			bbCommandEmpty cmd3;
			cmd3.type = c_Clear;
			widget_int = widget->m_SubwidgetArray[i_answer];
			bbPool_Lookup(&subWidget, pool, widget_int);
			bbWidget_onCommand(&cmd3, subWidget);

			break;
		}
		case c_RequestClick: {
			//set m_String to ""
			widget->m_String[0] = '\0';
			sfText_setString(widget->m_Text, widget->m_String);
			widget->s_State = s_WaitingForClick;


			//set query to "click to target spell"
			bbCommandStr cmd2;
			cmd2.type = f_CommandSetStr;
			cmd2.m_str = "Click to target spell";

			//gather data
			I32 map = widget->p_Node.p_Pool.Map;
			I32 widget_int;
			bbPool* pool = g_Game->m_Maps[map]->m_Widgets->m_Pool;

			// Set Question
			bbWidget* subWidget;
			widget_int = widget->m_SubwidgetArray[i_query];
			bbPool_Lookup(&subWidget, pool, widget_int);
			bbWidget_onCommand(&cmd2, subWidget);
			//set input to ""
			bbCommandEmpty cmd3;
			cmd3.type = c_Clear;
			widget_int = widget->m_SubwidgetArray[i_answer];
			bbPool_Lookup(&subWidget, pool, widget_int);
			bbWidget_onCommand(&cmd3, subWidget);

			break;
		}
		case c_RequestAnswer: {


			//set m_String to ""
			widget->m_String[0] = '\0';
			sfText_setString(widget->m_Text, widget->m_String);
			widget->s_State = s_WaitingForAnswer;

			bbCommandStr* cmd1 = data;

			bbCommandStr cmd2;
			cmd2.type = f_CommandSetStr;
			cmd2.m_str = cmd1->m_str;

			//gather data
			I32 map = widget->p_Node.p_Pool.Map;
			I32 widget_int;
			bbPool* pool = g_Game->m_Maps[map]->m_Widgets->m_Pool;

			// Set Question
			bbWidget* subWidget;
			widget_int = widget->m_SubwidgetArray[i_query];
			bbPool_Lookup(&subWidget, pool, widget_int);
			bbWidget_onCommand(&cmd2, subWidget);
			bbDebug("request answer %s\n", cmd2.m_str);
			//set input to ""
			bbCommandEmpty cmd3;
			cmd3.type = c_Clear;
			widget_int = widget->m_SubwidgetArray[i_answer];
			bbPool_Lookup(&subWidget, pool, widget_int);
			bbWidget_onCommand(&cmd3, subWidget);

			break;
		}
		case c_SetIdle: {
			//set m_String to ""
			widget->m_String[0] = '\0';
			sfText_setString(widget->m_Text, widget->m_String);
			widget->s_State = s_Idle;

			I32 widget_int;
			I32 map = widget->p_Node.p_Pool.Map;
			bbPool* pool = g_Game->m_Maps[map]->m_Widgets->m_Pool;
			bbCommandEmpty cmd3;
			cmd3.type = c_Clear;
			bbWidget* subWidget;

			widget_int = widget->m_SubwidgetArray[i_query];
			bbPool_Lookup(&subWidget, pool, widget_int);
			bbWidget_onCommand(&cmd3, subWidget);
			widget_int = widget->m_SubwidgetArray[i_answer];
			bbPool_Lookup(&subWidget, pool, widget_int);
			bbWidget_onCommand(&cmd3, subWidget);

			break;
		}
        default:
        bbDebug("Command %d not found\n", commandEmpty->type);
    }

}
