#define BBDEBUG

#include "headers/bbWidget.h"
#include "headers/bbGame.h"
#include "headers/bbPrintf.h"
#include "games/game/maps/demo/widgets/emptyWidget.h"
#include "headers/bbIntTypes.h"
#include "headers/bbCommands.h"

// g_Game->m_Maps[map]->m_Widgets = widgets; OR return by reference?
I32 bbWidgets_new(I32 map){
	bbWidgets* widgets = calloc(1, sizeof(bbWidgets));

	bbPool_NewPool(&widgets->m_Pool, map, sizeof(bbWidget), 100, 100); //todo lvl1 lvl2
	bbDictionary_new(&widgets->m_AddressDict, 777);
	bbDictionary_new(&widgets->m_CodeDict, 666);
	widgets->m_Layout = NULL;
	widgets->m_Prompt = NULL;
	widgets->m_Functions = NULL;

	g_Game->m_Maps[map]->m_Widgets = widgets;
	return f_Success;
}

// Should m_Widgets be an argument?
I32 bbWidget_new(bbWidget** self, bbWidgets* widgets , I32 type, I32 parent, bbScreenCoordsI SCI){
    bbAssert(type >= 0, "Constructor not found\n");

	bbWidget* widget;
    bbWidget* parentWidget;



    bbPool_Lookup(&parentWidget, widgets->m_Pool, parent);
	bbWidget_Constructor* constructor = widgets->m_Functions->Constructors[type];

	I32 flag = constructor(&widget, widgets, SCI, parentWidget);

	*self = widget;
	return flag;
}

//typedef I32 bbTreeFunction (void* reference, void* node);
I32 bbWidget_draw(void* void_unused, void* void_widget){
	bbWidget* widget = void_widget;
	I32 map = widget->p_Node.p_Pool.Map;
	bbWidgetFunctions* functions = g_Game->m_Maps[map]->m_Widgets->m_Functions;
	bbWidget_DrawFunction* drawFunctions = *functions->DrawFunction;

	for (I32 i = 0; i < ANIMATIONS_PER_WIDGET; i++){
		int drawFunction_int = widget->v_DrawFunction[i];
		if (drawFunction_int >= 0) {
			//TODO skins, default drawFunction given by animation or skin
			functions->DrawFunction[drawFunction_int](widget, i);

		}
	}
    return f_Continue;
}
//typedef I32 bbTreeFunction (void* reference, void* node);
I32 bbWidget_mouse(void* void_mouseEvent, void* void_widget){
    bbWidget* widget = void_widget;
    I32 map = widget->p_Node.p_Pool.Map;
    bbWidgetFunctions* functions = g_Game->m_Maps[map]->m_Widgets->m_Functions;

	if (widget->v_OnMouse >= 0) {
		bbWidget_Mouse *mouseFunction = functions->MouseHandler[widget->v_OnMouse];
		return mouseFunction(void_mouseEvent, void_widget);
	}
	return f_Continue;
}



I32 bbWidgetFunctions_new(I32 map) {
	bbWidgetFunctions *functions = calloc(1, sizeof(bbWidgetFunctions));


	const I32 numConstructors = g_Game->m_Maps[map]->p_Constants.Widget_Constructors;
	functions->Constructors = calloc(numConstructors,
									 sizeof(bbWidget_Constructor));
	bbDictionary_new(&functions->Constructor_dict, numConstructors);
	functions->Constructor_available = 0;

	const I32 numUpdate = g_Game->m_Maps[map]->p_Constants.Widget_Updates;
	functions->Update = calloc(numUpdate,
									 sizeof(bbWidget_Update));
	bbDictionary_new(&functions->Update_dict, numUpdate);
	functions->Update_available = 0;


	const I32 numDestructors = g_Game->m_Maps[map]->p_Constants.Widget_Destructors;
	functions->Destructors = calloc(numDestructors,
									sizeof(bbWidget_Destructor));
	bbDictionary_new(&functions->Destructor_dict, numDestructors);
	functions->Destructor_available = 0;

	const I32 numOnCommands = g_Game->m_Maps[map]->p_Constants.Widget_OnCommands;
	functions->OnCommands = calloc(numOnCommands, sizeof(bbWidget_OnCommand));
	bbDictionary_new(&functions->OnCommand_dict, numOnCommands);
	functions->OnCommand_available = 0;

	const I32 numDrawFunctions = g_Game->m_Maps[map]->p_Constants.Widget_DrawFunctions;
	functions->DrawFunction = calloc(numDrawFunctions,
									  sizeof(bbWidget_DrawFunction));
	bbDictionary_new(&functions->DrawFunction_dict, numDrawFunctions);
	functions->DrawFunction_available = 0;

    const I32 numMouseHandlers = g_Game->m_Maps[map]->p_Constants.Widget_Mouses;
    functions->MouseHandler = calloc(numMouseHandlers,
                                     sizeof(bbWidget_Mouse));
    bbDictionary_new(&functions->MouseHandler_dict, numMouseHandlers);
    functions->MouseHandler_available = 0;

    const I32 numOnTimers = 100; //TODO add to txt file Todo would be faster if hard-coded
    functions->OnTimers = calloc(numOnTimers,
                                     sizeof(bbWidget_OnTimer));
    bbDictionary_new(&functions->OnTimers_dict, numOnTimers);
    functions->OnCommand_available = 0;

	g_Game->m_Maps[map]->m_Widgets->m_Functions = functions;

	return f_Success;
}



I32 bbWidgetFunctions_add(bbWidgetFunctions* WFS, I32 bin, void* fun_ptr, char* key ){
	int available;
	switch (bin) {
		case f_WidgetConstructor:
			available = WFS->Constructor_available++;
			//bbAssert available < MAX
			WFS->Constructors[available] = fun_ptr;
			bbDictionary_add(WFS->Constructor_dict, key, available);
			return f_Success;

		case f_WidgetUpdate:
			available = WFS->Update_available++;
			//bbAssert available < MAX
			WFS->Update[available] = fun_ptr;
			bbDictionary_add(WFS->Update_dict, key, available);
			return f_Success;

		case f_WidgetDestructor:
			available = WFS->Destructor_available++;
			//bbAssert available < MAX
			WFS->Destructors[available] = fun_ptr;
			bbDictionary_add(WFS->Destructor_dict, key, available);
			return f_Success;

		case f_WidgetOnCommand:
			available = WFS->OnCommand_available++;
			//bbAssert available < MAX
			WFS->OnCommands[available] = fun_ptr;
			bbDictionary_add(WFS->OnCommand_dict, key, available);
			return f_Success;

		case f_WidgetDrawFunction:
			available = WFS->DrawFunction_available++;
			//bbAssert available < MAX
			WFS->DrawFunction[available] = fun_ptr;
			bbDictionary_add(WFS->DrawFunction_dict, key, available);
			return f_Success;

        case f_WidgetMouseHandler:
            available = WFS->MouseHandler_available++;
            //bbAssert available < MAX
            WFS->MouseHandler[available] = fun_ptr;
            bbDictionary_add(WFS->MouseHandler_dict, key, available);
            return f_Success;

        case f_WidgetOnTimer:
            available = WFS->OnTimers_available++;
            //bbAssert available < MAX
            WFS->OnTimers[available] = fun_ptr;
            bbDictionary_add(WFS->OnTimers_dict, key, available);
            return f_Success;
		default:
            bbPrintf("Bad flag in bbWidgetFunctions_add\n");
			return f_None;
	}
}

I32 bbWidgetFunctions_getFunction(void** function, bbWidgetFunctions* WFS, I32 bin, char* key){
	I32 intAddress;
	switch (bin) {
		case f_WidgetConstructor:
			intAddress = bbDictionary_lookup(WFS->Constructor_dict, key);
			*function = WFS->Constructors[intAddress];
			return f_Success;

		case f_WidgetUpdate:
			intAddress = bbDictionary_lookup(WFS->Update_dict, key);
			*function = WFS->Update[intAddress];
			return f_Success;

		case f_WidgetDestructor:
			intAddress = bbDictionary_lookup(WFS->Destructor_dict, key);
			*function = WFS->Destructors[intAddress];
			return f_Success;

		case f_WidgetOnCommand:
			intAddress = bbDictionary_lookup(WFS->OnCommand_dict, key);
			*function = WFS->OnCommands[intAddress];
			return f_Success;

		case f_WidgetDrawFunction:
			intAddress = bbDictionary_lookup(WFS->DrawFunction_dict, key);
			*function = WFS->DrawFunction[intAddress];
			return f_Success;

        case f_WidgetMouseHandler:
            intAddress = bbDictionary_lookup(WFS->MouseHandler_dict, key);
            *function = WFS->MouseHandler[intAddress];
            return f_Success;

        case f_WidgetOnTimer:
            intAddress = bbDictionary_lookup(WFS->OnTimers_dict, key);
            *function = WFS->OnTimers[intAddress];
            return f_Success;
        default:
			return f_None;
	}
}
I32 bbWidgetFunctions_getInt(bbWidgetFunctions* WFS, I32 bin, char* key){
	I32 intAddress;
	switch (bin) {
		case f_WidgetConstructor:
			intAddress = bbDictionary_lookup(WFS->Constructor_dict, key);
			return intAddress;

		case f_WidgetUpdate:
			intAddress = bbDictionary_lookup(WFS->Update_dict, key);
			return intAddress;
		case f_WidgetDestructor:
			intAddress = bbDictionary_lookup(WFS->Destructor_dict, key);
			return intAddress;

		case f_WidgetOnCommand:
			intAddress = bbDictionary_lookup(WFS->OnCommand_dict, key);
			return intAddress;

		case f_WidgetDrawFunction:
			intAddress = bbDictionary_lookup(WFS->DrawFunction_dict, key);
			return intAddress;

        case f_WidgetMouseHandler:
            intAddress = bbDictionary_lookup(WFS->MouseHandler_dict, key);
            return intAddress;

        case f_WidgetOnTimer:
            intAddress = bbDictionary_lookup(WFS->OnTimers_dict, key);
            return intAddress;
        default:
			return f_None;
	}
}

I32 bbWidget_onCommand(void* command, void* void_widget){

    bbWidget* widget = void_widget;

    I32 map = widget->p_Node.p_Pool.Map;

    //bbWarning(widget != g_Game->m_Maps[map]->m_Widgets->m_SpellBar, "command sent to spellbar\n");
    bbWidgetFunctions* functions = g_Game->m_Maps[map]->m_Widgets->m_Functions;
    I32 commandFunction_int = widget->v_OnCommand;

        if (commandFunction_int >= 0) {
            return functions->OnCommands[commandFunction_int](widget, command);

        } else {
            bbDebug("widget %s has no command handler\n", widget->m_String);
			return f_None;
        }

    return f_Continue;
}
I32 bbWidget_onUpdate(void* command, void* void_widget){

    bbWidget* widget = void_widget;
    I32 map = widget->p_Node.p_Pool.Map;
    bbWidgetFunctions* functions = g_Game->m_Maps[map]->m_Widgets->m_Functions;
    I32 updateFunction_int = widget->v_OnUpdate;

    if (updateFunction_int >= 0) {

        functions->Update[updateFunction_int](widget, command);

    }

    return f_Continue;
}
I32 bbWidget_onTimer(void* void_timerNode, void* void_widget){

    bbWidget* widget = void_widget;
    I32 map = widget->p_Node.p_Pool.Map;
    bbWidgetFunctions* functions = g_Game->m_Maps[map]->m_Widgets->m_Functions;
    I32 TimerFunction_int = widget->v_OnTimer;

    if (TimerFunction_int >= 0) {
        functions->OnTimers[TimerFunction_int](widget, void_timerNode);

    }

    return f_Continue;
}


void bbDialog(const char* format, ...){
	I32 map = g_Game->m_CurrentMap;
	bbWidget* prompt = g_Game->m_Maps[map]->m_Widgets->m_Prompt;
	char str[128];
	bbCommandStr cmdStr;
	cmdStr.type = f_PromptAddDialogue;
	cmdStr.m_str = str;
	va_list args;
	va_start(args, format);
	vsprintf(cmdStr.m_str, format, args);
	va_end (args);

	bbWidget_onCommand(&cmdStr, prompt);

}