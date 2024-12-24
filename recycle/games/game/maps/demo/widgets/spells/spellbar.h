/**
 * @file
 * @brief The functions in this file define the behavior of an object with class bbWidget and type spellBar
 * and its member widgets
 *
 * The bbTree representing the spellBar is structured as such
 *
 *    spellBar
 *      - menuButton
 *      - showHideButton
 *          - plus
 *          - minus
 *          - times
 *          - divide
 *          - determinant
 *          - twoPower
 *          - squared
 *          - piNDigits
 */


#include "recycle/headers/bbPrintf.h"
#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbMap.h"
#include "recycle/headers/bbIntTypes.h"

//typedef I32 bbWidget_Constructor (bbWidget** reference, void* widgets, bbScreenCoordsI screen_coords, bbWidget* parent);


I32 bbWidget_menuButton_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent) {
///	Spawn a null widget on selected map at coordinates mc


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;

    bbWidget *widget;
    I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

    widget->m_String = "Menu / Pause Button";
    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");

    bbScreenCoordsF SCF;
    bbScreenCoordsI SCI;

    float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
    SCF.x = 80 * widgetScale;
    SCF.y = 80 * widgetScale;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_Dimensions = SCI;


    widget->m_AnimationInt[0] = 24; // SPELLBAR
    widget->m_Frame[0] = 0;         // MENU
    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");


    *reference = widget;
    return f_Success;

}

I32 bbWidget_showHideButton_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;

    bbWidget *widget;

    I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

    widget->m_String = "Show / Hide Spell Bar";
    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");

    bbScreenCoordsF SCF;
    bbScreenCoordsI SCI;

    float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
    SCF.x = 80 * widgetScale;
    SCF.y = 80 * widgetScale;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_Dimensions = SCI;

    widget->m_AnimationInt[0] = 24; // SPELLBAR
    widget->m_Frame[0] = 1;         // SHOWHIDE
    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");

    *reference = widget;
    return f_Success;
}

I32 bbWidget_plusButton_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;

    bbWidget *widget;
    I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

    widget->m_String = "Plus";
    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");

    bbScreenCoordsF SCF;
    bbScreenCoordsI SCI;

    float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
    SCF.x = 80 * widgetScale;
    SCF.y = 80 * widgetScale;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_Dimensions = SCI;

    widget->m_AnimationInt[0] = 24; // SPELLBAR
    widget->m_Frame[0] = 2;         // PLUS
    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");



    widget->m_CoolDownStart = -rand() % 512;
    widget->m_CoolDownEnd = rand() % 512;
    //widget->m_GreenRect = sfRectangleShape_create();
    widget->m_RedRect = sfRectangleShape_create();
    sfColor RedHalfAlpha;
    RedHalfAlpha.r = 255;
    RedHalfAlpha.g = 0;
    RedHalfAlpha.b = 0;
    RedHalfAlpha.a = 127;
    sfRectangleShape_setFillColor(widget->m_RedRect, RedHalfAlpha);

    sfVector2f vector2f;
    vector2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setPosition(widget->m_RedRect, vector2f);
    vector2f = bbScreenCoordsI_getV2f(SCI, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setSize(widget->m_RedRect, vector2f);
    widget->v_DrawFunction[1] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "cooldown");

    g_Game->m_Maps[widget->p_Node.p_Pool.Map]->misc.m_ActiveSpell_deprecated = widget->p_Node.p_Pool.Self;

    *reference = widget;
    return f_Success;
}

I32 bbWidget_minusButton_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;

    bbWidget *widget;

    I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

    widget->m_String = "Minus";
    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");

    bbScreenCoordsF SCF;
    bbScreenCoordsI SCI;

    float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
    SCF.x = 80 * widgetScale;
    SCF.y = 80 * widgetScale;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_Dimensions = SCI;
    widget->m_AnimationInt[0] = 24; // SPELLBAR
    widget->m_Frame[0] = 3;         // MINUS
    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");


    widget->m_CoolDownStart = -rand() % 512;
    widget->m_CoolDownEnd = rand() % 512;
    //widget->m_GreenRect = sfRectangleShape_create();
    widget->m_RedRect = sfRectangleShape_create();
    sfColor RedHalfAlpha;
    RedHalfAlpha.r = 255;
    RedHalfAlpha.g = 0;
    RedHalfAlpha.b = 0;
    RedHalfAlpha.a = 127;
    sfRectangleShape_setFillColor(widget->m_RedRect, RedHalfAlpha);

    sfVector2f vector2f;
    vector2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setPosition(widget->m_RedRect, vector2f);
    vector2f = bbScreenCoordsI_getV2f(SCI, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setSize(widget->m_RedRect, vector2f);
    widget->v_DrawFunction[1] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "cooldown");

    *reference = widget;
    return f_Success;
}

I32 bbWidget_timesButton_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;

    bbWidget *widget;

    I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

    widget->m_String = "Times";
    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");

    bbScreenCoordsF SCF;
    bbScreenCoordsI SCI;

    float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
    SCF.x = 80 * widgetScale;
    SCF.y = 80 * widgetScale;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_Dimensions = SCI;

    widget->m_AnimationInt[0] = 24; // SPELLBAR
    widget->m_Frame[0] = 4;         // TIMES
    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");


    widget->m_CoolDownStart = -rand() % 512;
    widget->m_CoolDownEnd = rand() % 512;
    //widget->m_GreenRect = sfRectangleShape_create();
    widget->m_RedRect = sfRectangleShape_create();
    sfColor RedHalfAlpha;
    RedHalfAlpha.r = 255;
    RedHalfAlpha.g = 0;
    RedHalfAlpha.b = 0;
    RedHalfAlpha.a = 127;
    sfRectangleShape_setFillColor(widget->m_RedRect, RedHalfAlpha);

    sfVector2f vector2f;
    vector2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setPosition(widget->m_RedRect, vector2f);
    vector2f = bbScreenCoordsI_getV2f(SCI, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setSize(widget->m_RedRect, vector2f);
    widget->v_DrawFunction[1] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "cooldown");

    *reference = widget;
    return f_Success;
}

I32 bbWidget_divideButton_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;

    bbWidget *widget;

    I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

    widget->m_String = "Divide";
    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");

    bbScreenCoordsF SCF;
    bbScreenCoordsI SCI;

    float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
    SCF.x = 80 * widgetScale;
    SCF.y = 80 * widgetScale;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_Dimensions = SCI;

    widget->m_AnimationInt[0] = 24; // SPELLBAR
    widget->m_Frame[0] = 5;         // DIVIDE
    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");


    widget->m_CoolDownStart = -rand() % 512;
    widget->m_CoolDownEnd = rand() % 512;
    //widget->m_GreenRect = sfRectangleShape_create();
    widget->m_RedRect = sfRectangleShape_create();
    sfColor RedHalfAlpha;
    RedHalfAlpha.r = 255;
    RedHalfAlpha.g = 0;
    RedHalfAlpha.b = 0;
    RedHalfAlpha.a = 127;
    sfRectangleShape_setFillColor(widget->m_RedRect, RedHalfAlpha);

    sfVector2f vector2f;
    vector2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setPosition(widget->m_RedRect, vector2f);
    vector2f = bbScreenCoordsI_getV2f(SCI, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setSize(widget->m_RedRect, vector2f);
    widget->v_DrawFunction[1] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "cooldown");

    *reference = widget;
    return f_Success;
}

I32 bbWidget_detButton_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;

    bbWidget *widget;

    I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

    widget->m_String = "Determinant";
    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");

    bbScreenCoordsF SCF;
    bbScreenCoordsI SCI;

    float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
    SCF.x = 80 * widgetScale;
    SCF.y = 80 * widgetScale;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_Dimensions = SCI;

    widget->m_AnimationInt[0] = 24; // SPELLBAR
    widget->m_Frame[0] = 6;         // DETERMINANT
    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");


    widget->m_CoolDownStart = -rand() % 512;
    widget->m_CoolDownEnd = rand() % 512;
    //widget->m_GreenRect = sfRectangleShape_create();
    widget->m_RedRect = sfRectangleShape_create();
    sfColor RedHalfAlpha;
    RedHalfAlpha.r = 255;
    RedHalfAlpha.g = 0;
    RedHalfAlpha.b = 0;
    RedHalfAlpha.a = 127;
    sfRectangleShape_setFillColor(widget->m_RedRect, RedHalfAlpha);

    sfVector2f vector2f;
    vector2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setPosition(widget->m_RedRect, vector2f);
    vector2f = bbScreenCoordsI_getV2f(SCI, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setSize(widget->m_RedRect, vector2f);
    widget->v_DrawFunction[1] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "cooldown");

    *reference = widget;
    return f_Success;
}

I32 bbWidget_twoPowerButton_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;

    bbWidget *widget;

    I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

    widget->m_String = "Powers of Two";
    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");

    bbScreenCoordsF SCF;
    bbScreenCoordsI SCI;

    float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
    SCF.x = 80 * widgetScale;
    SCF.y = 80 * widgetScale;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_Dimensions = SCI;

    widget->m_AnimationInt[0] = 24; // SPELLBAR
    widget->m_Frame[0] = 7;         // TWO TO THE POWER
    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");


    widget->m_CoolDownStart = -rand() % 512;
    widget->m_CoolDownEnd = rand() % 512;
    //widget->m_GreenRect = sfRectangleShape_create();
    widget->m_RedRect = sfRectangleShape_create();
    sfColor RedHalfAlpha;
    RedHalfAlpha.r = 255;
    RedHalfAlpha.g = 0;
    RedHalfAlpha.b = 0;
    RedHalfAlpha.a = 127;
    sfRectangleShape_setFillColor(widget->m_RedRect, RedHalfAlpha);

    sfVector2f vector2f;
    vector2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setPosition(widget->m_RedRect, vector2f);
    vector2f = bbScreenCoordsI_getV2f(SCI, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setSize(widget->m_RedRect, vector2f);
    widget->v_DrawFunction[1] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "cooldown");

    *reference = widget;
    return f_Success;
}

I32 bbWidget_squaredButton_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;

    bbWidget *widget;
    I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

    widget->m_String = "Square";
    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");

    bbScreenCoordsF SCF;
    bbScreenCoordsI SCI;

    float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
    SCF.x = 80 * widgetScale;
    SCF.y = 80 * widgetScale;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_Dimensions = SCI;

    widget->m_AnimationInt[0] = 24; // SPELLBAR
    widget->m_Frame[0] = 8;         // SQUARED
    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");


    widget->m_CoolDownStart = -rand() % 512;
    widget->m_CoolDownEnd = rand() % 512;
    //widget->m_GreenRect = sfRectangleShape_create();
    widget->m_RedRect = sfRectangleShape_create();
    sfColor RedHalfAlpha;
    RedHalfAlpha.r = 255;
    RedHalfAlpha.g = 0;
    RedHalfAlpha.b = 0;
    RedHalfAlpha.a = 127;
    sfRectangleShape_setFillColor(widget->m_RedRect, RedHalfAlpha);

    sfVector2f vector2f;
    vector2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setPosition(widget->m_RedRect, vector2f);
    vector2f = bbScreenCoordsI_getV2f(SCI, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setSize(widget->m_RedRect, vector2f);
    widget->v_DrawFunction[1] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "cooldown");

    *reference = widget;
    return f_Success;
}
I32 bbWidget_piNDigitsButton_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;

    bbWidget *widget;
    I32 flag = bbWidget_empty_new(&widget, widgets, sc, parent);

    widget->m_String = "N digits of Pi";
    bbWidgetFunctions* functions = widgets->m_Functions;
    widget->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");

    bbScreenCoordsF SCF;
    bbScreenCoordsI SCI;

    float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
    SCF.x = 80 * widgetScale;
    SCF.y = 80 * widgetScale;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    widget->m_Dimensions = SCI;

    widget->m_AnimationInt[0] = 24; // SPELLBAR
    widget->m_Frame[0] = 9;         // N DIGITS OF PI
    widget->v_DrawFunction[0] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "frame");


    widget->m_CoolDownStart = -rand() % 512;
    widget->m_CoolDownEnd = rand() % 512;
    //widget->m_GreenRect = sfRectangleShape_create();
    widget->m_RedRect = sfRectangleShape_create();
    sfColor RedHalfAlpha;
    RedHalfAlpha.r = 255;
    RedHalfAlpha.g = 0;
    RedHalfAlpha.b = 0;
    RedHalfAlpha.a = 127;
    sfRectangleShape_setFillColor(widget->m_RedRect, RedHalfAlpha);

    sfVector2f vector2f;
    vector2f = bbScreenCoordsI_getV2f(sc, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setPosition(widget->m_RedRect, vector2f);
    vector2f = bbScreenCoordsI_getV2f(SCI, &g_Game->m_Maps[widget->p_Node.p_Pool.Map]->p_Constants);
    sfRectangleShape_setSize(widget->m_RedRect, vector2f);
    widget->v_DrawFunction[1] = bbWidgetFunctions_getInt(functions, f_WidgetDrawFunction, "cooldown");

    *reference = widget;
    return f_Success;
}
I32 bbWidgetNew_Spellbar(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI sc, bbWidget* parent){

    bbWidget* spellBar;
    bbWidget* menuButton;
    bbWidget* showHideButton;
    bbWidget* plusButton;
    bbWidget* minusButton;
    bbWidget* timesButton;
    bbWidget* divideButton;
    bbWidget* detButton;
    bbWidget* twoPowerButton;
    bbWidget* squaredButton;
    bbWidget* piNDigitsButton;


    bbPool *pool = widgets->m_Pool;
    bbDictionary *dict = widgets->m_AddressDict;
    I32 map = widgets->m_Pool->m_Map;


    I32 flag = bbWidget_empty_new(&spellBar, widgets, sc, parent);

    bbWidgetFunctions* functions = widgets->m_Functions;
    spellBar->v_OnMouse = bbWidgetFunctions_getInt(functions, f_WidgetMouseHandler, "clickText");
    spellBar->m_String = "Spell Bar";
    bbScreenCoordsF SCF;
    bbScreenCoordsI SCI;

    float widgetScale = g_Game->m_GraphicsSettings->m_WidgetScale;
    SCF.x = 10 * 80 * widgetScale;
    SCF.y = 80 * widgetScale;
    SCI = bbScreenCoordsF_getI(SCF, &g_Game->m_Maps[spellBar->p_Node.p_Pool.Map]->p_Constants);
    spellBar->m_Dimensions = SCI;


    bbWidget_menuButton_new(&menuButton, widgets, sc, spellBar);
    sc.x += 80 * g_Game->m_Maps[map]->p_Constants.ScreenPPP * widgetScale;
    bbWidget_showHideButton_new(&showHideButton, widgets, sc, spellBar);
    sc.x += 80 * g_Game->m_Maps[map]->p_Constants.ScreenPPP * widgetScale;
    bbWidget_plusButton_new(&plusButton, widgets, sc, showHideButton);
    sc.x += 80 * g_Game->m_Maps[map]->p_Constants.ScreenPPP * widgetScale;
    bbWidget_minusButton_new(&minusButton, widgets, sc, showHideButton);
    sc.x += 80 * g_Game->m_Maps[map]->p_Constants.ScreenPPP * widgetScale;
    bbWidget_timesButton_new(&timesButton, widgets, sc, showHideButton);
    sc.x += 80 * g_Game->m_Maps[map]->p_Constants.ScreenPPP * widgetScale;
    bbWidget_divideButton_new(&divideButton, widgets, sc, showHideButton);
    sc.x += 80 * g_Game->m_Maps[map]->p_Constants.ScreenPPP * widgetScale;
    bbWidget_detButton_new(&detButton, widgets, sc, showHideButton);
    sc.x += 80 * g_Game->m_Maps[map]->p_Constants.ScreenPPP * widgetScale;
    bbWidget_twoPowerButton_new(&twoPowerButton, widgets, sc, showHideButton);
    sc.x += 80 * g_Game->m_Maps[map]->p_Constants.ScreenPPP * widgetScale;
    bbWidget_squaredButton_new(&squaredButton, widgets, sc, showHideButton);
    sc.x += 80 * g_Game->m_Maps[map]->p_Constants.ScreenPPP * widgetScale;
    bbWidget_piNDigitsButton_new(&piNDigitsButton, widgets, sc, showHideButton);

    *reference = spellBar;

    return f_Success;



}
