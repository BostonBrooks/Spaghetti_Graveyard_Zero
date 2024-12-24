#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbIntTypes.h"

///include files containing widget functions, later these will be stored in a Dynamic Linked Library
#include "recycle/games/game/maps/demo2/widgets/drawFunctions/AnimationDraw.h"
#include "recycle/games/game/maps/demo2/widgets/drawFunctions/FrameDraw.h"
#include "recycle/games/game/maps/demo2/widgets/drawFunctions/SpriteDraw.h"
#include "recycle/games/game/maps/demo2/widgets/drawFunctions/CoolDownDraw.h"
#include "recycle/games/game/maps/demo2/widgets/drawFunctions/RenderTextureDraw.h"
#include "fireworks.h"
#include "layout.h"
#include "viewport.h"
#include "MouseClickText.h"
#include "recycle/games/game/maps/demo2/widgets/drawFunctions/TextDraw.h"
#include "sphere.h"
#include "textBox.h"
#include "prompt.h"
#include "recycle/games/game/maps/demo2/widgets/spellbar/spellbar.h"
#include "recycle/games/game/maps/demo2/widgets/spellbar/spell.h"



I32 bbWidgetFunctions_populate(I32 map){


    bbWidgetFunctions* functions = g_Game->m_Maps[map]->m_Widgets->m_Functions;

	//typedef I32 bbWidget_Constructor (bbWidget** reference, void* widgets, bbScreenCoordsI screen_coords, bbWidget* parent);
	bbWidgetFunctions_add(functions, f_WidgetDrawFunction, bbWidgetDraw_Animation, "animation");
    bbWidgetFunctions_add(functions, f_WidgetDrawFunction, bbWidgetDraw_Frame, "frame");
    bbWidgetFunctions_add(functions, f_WidgetDrawFunction, bbWidgetDraw_Sprite, "sprite");
    bbWidgetFunctions_add(functions, f_WidgetDrawFunction, bbWidgetDraw_Cooldown, "cooldown");
	bbWidgetFunctions_add(functions, f_WidgetDrawFunction, bbWidgetDraw_Text, "text");
	bbWidgetFunctions_add(functions, f_WidgetDrawFunction,
						  bbWidgetDraw_RenderTexture, "rendertexture");

//typedef I32 bbWidget_Constructor (bbWidget** reference, void* widgets, bbScreenCoordsI screen_coords, bbWidget* parent);
    bbWidgetFunctions_add(functions, f_WidgetConstructor, bbWidgetNew_Fireworks, "fireworks");
    bbWidgetFunctions_add(functions, f_WidgetConstructor, bbWidgetNew_Textbox, "textbox");
    bbWidgetFunctions_add(functions, f_WidgetConstructor, bbWidgetNew_Layout, "layout");
    bbWidgetFunctions_add(functions, f_WidgetConstructor, bbWidgetNew_Viewport, "viewport");
    bbWidgetFunctions_add(functions, f_WidgetConstructor, bbWidgetNew_Sphere, "sphere");
  //  bbWidgetFunctions_add(functions, f_WidgetConstructor, bbWidgetNew_Spellbar, "spellBar");
    bbWidgetFunctions_add(functions, f_WidgetConstructor, bbWidgetNew_Prompt, "prompt");
	bbWidgetFunctions_add(functions, f_WidgetConstructor, bbWidgetNew_Spellbar, "spellbar");
	bbWidgetFunctions_add(functions, f_WidgetConstructor, bbWidgetNew_Spell, "spell");

	//typedef I32 bbWidget_Mouse(void* void_mouseEvent, void* void_widget);
    bbWidgetFunctions_add(functions, f_WidgetMouseHandler, bbWidgetClick_Text, "clickText");
    bbWidgetFunctions_add(functions, f_WidgetMouseHandler, bbWidgetClick_Sphere, "clickSphere");
	bbWidgetFunctions_add(functions, f_WidgetMouseHandler, bbWidgetClick_Layout, "layout");
	bbWidgetFunctions_add(functions, f_WidgetMouseHandler, bbWidgetClick_Spell, "spell");
	bbWidgetFunctions_add(functions, f_WidgetMouseHandler, bbWidgetClick_Spellbar, "spellbar");
	bbWidgetFunctions_add(functions, f_WidgetMouseHandler,
						  bbWidgetClick_Viewport, "viewport");

	//typedef I32 bbWidget_OnCommand (bbWidget* widget, void* data);
    bbWidgetFunctions_add(functions, f_WidgetOnCommand, bbWidgetCommand_Textbox, "textbox");
    bbWidgetFunctions_add(functions, f_WidgetOnCommand, bbWidgetCommand_Prompt, "prompt");
	bbWidgetFunctions_add(functions, f_WidgetOnCommand, bbWidgetCommand_Spellbar, "spellbar");
	bbWidgetFunctions_add(functions, f_WidgetOnCommand, bbWidgetCommand_Spell, "spell");
	bbWidgetFunctions_add(functions, f_WidgetOnCommand, bbWidgetCommand_Viewport, "viewport");

	//typedef I32 bbWidget_OnTimer (bbWidget* widget, void* void_timerNode);
    bbWidgetFunctions_add(functions, f_WidgetOnTimer, bbWidget_Sphere_onTimer, "sphere");

	return f_Success;
}

