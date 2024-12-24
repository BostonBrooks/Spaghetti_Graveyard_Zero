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
#include "recycle/headers/bbCommands.h"

///	Spawn a null widget on selected map at coordinates mc
I32 bbWidgetNew_Viewport(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){



    bbWidget* widget;
    bbWidget_empty_new(&widget, widgets, sc, parent);

    bbPrintf("viewport -> map = %d\n", widget->p_Node.p_Pool.Map);

    I32 flag;
    widget->m_String = "Mock Viewport";

    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "viewport");
	widget->v_OnCommand = bbWidgetFunctions_getInt(functions, f_WidgetOnCommand, "viewport");


    bbScreenCoordsF SCF;
    bbScreenCoordsI SCI;

    SCF.x = g_Game->m_GraphicsSettings->m_ViewportLeft;
    SCF.y = g_Game->m_GraphicsSettings->m_ViewportTop;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_ScreenCoords = SCI;

    SCF.x = g_Game->m_GraphicsSettings->m_ViewportWidth;
    SCF.y = g_Game->m_GraphicsSettings->m_ViewportHeight;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_Dimensions = SCI;


    widget->m_AnimationInt[0] = bbSprites_lookupInt(g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Sprites,
													g_Game->m_GraphicsSettings->m_ViewportMock); // VIEWPORT

	widget->m_RenderTexture = sfRenderTexture_create(g_Game->m_GraphicsSettings->m_ViewportWidth, g_Game->m_GraphicsSettings->m_ViewportHeight, sfFalse);
	I32 map = widget->p_Node.p_Pool.Map;
	bbSprites* sprites = g_Game->m_Maps[map]->m_Sprites;
	I32 spriteNum = widget->m_AnimationInt[0];
	sfSprite* sprite = sprites->m_Sprites[spriteNum];

	sfRenderTexture_drawSprite(widget->m_RenderTexture, sprite,NULL);
	sfRenderTexture_display(widget->m_RenderTexture );

	widget->m_Sprite = sfSprite_create();
	sfSprite_setTexture(widget->m_Sprite, sfRenderTexture_getTexture(widget->m_RenderTexture), sfTrue);

    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "rendertexture");

	g_Game->m_Maps[widget->p_Node.p_Pool.Map]->m_Widgets->m_Viewport = widget;

    *reference = widget;
    return f_Success;
}

/// Update widget
I32 bbWidget_Viewport_update(bbWidget* widget){}

/// Send a command to the widget / update widget, etc
I32 bbWidgetCommand_Viewport(bbWidget* widget, void* command){
	bbCommandEmpty* commandEmpty = command;

	switch (commandEmpty->type){

        case c_RequestClick: {

            widget->s_State = s_WaitingForClick;
            bbDebug("click viewport\n");
            return f_Success;
        }
        case c_CastSpell: {

            //spell sends message to viewport
            bbDebug("cast spell\n")
            return f_Success;
        }
		default:
			bbDebug("Viewport: Command %d not found\n", commandEmpty->type);
			return f_None;
	}

}

//typedef I32 bbWidget_Mouse(void* void_mouseEvent, void* void_widget);
I32 bbWidgetClick_Viewport(void* void_mouseEvent, void* void_widget){
	bbMouseEvent* event = void_mouseEvent;
	bbWidget* widget = void_widget;
	bbScreenCoordsI sc = event->m_ScreenCoords;

	if (! bbWidget_containsPoint(widget, event->m_ScreenCoords)) return f_Continue;
	if (event->m_type != f_MouseLeft) return f_Continue;
	if( widget->s_State != s_WaitingForClick){
		bbDialog("\nviewport clicked, ignored");
		return f_Break;
	}

	bbDialog("\nviewport clicked, send message to spellbar");

    bbCommand2I cmd;
    cmd.type = c_ReturnClick;
    //viewport coords? What about map coords or target drawable?
    cmd.m_intx = event->m_ScreenCoords.x - widget->m_ScreenCoords.x;
    cmd.m_inty = event->m_ScreenCoords.y - widget->m_ScreenCoords.y;

    I32 map = widget->p_Node.p_Pool.Map;

    bbWidget* spellbar = g_Game->m_Maps[map]->m_Widgets->m_SpellBar;

    bbWidget_onCommand(&cmd, spellbar);
    widget->s_State = s_Idle;
}


/// Delete widget
I32 bbWidgetDelete_Viewport(bbWidget* widget){}

/// Draw widget to screen
I32 bbWidgetDraw_Viewport(bbWidget* widget){}


