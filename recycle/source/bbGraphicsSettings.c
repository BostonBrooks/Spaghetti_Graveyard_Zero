#include "headers/bbGraphicsSettings.h"
#include "headers/bbSystemIncludes.h"

I32 bbGraphicsSettings_new(bbGraphicsSettings** RBR, char* filePath){


	bbGraphicsSettings* settings = calloc(1, sizeof(bbGraphicsSettings));
	bbAssert(settings != NULL, "calloc failed\n");

	FILE* file = fopen(filePath, "r");
	bbAssert(file != NULL, "fopen failed\n");


	fscanf(file, "%s%*[^\n]\n", settings->m_GraphicsLevel);
	fscanf(file, "Width: %d\n", &settings->m_Width);
	fscanf(file, "Height: %d\n", &settings->m_Height);
	fscanf(file, "Drawable Scale: %f\n", &settings->m_DrawableScale);
	fscanf(file, "Widget Scale: %f\n", &settings->m_WidgetScale);
	fscanf(file, "Layout: %s\n", settings->m_Layout);
	fscanf(file, "Viewport.mock: %s\n", settings->m_ViewportMock);
	fscanf(file, "Viewport.top: %f\n", &settings->m_ViewportTop);
	fscanf(file, "Viewport.left: %f\n", &settings->m_ViewportLeft);
	fscanf(file, "Viewport.width: %f\n", &settings->m_ViewportWidth);
	fscanf(file, "Viewport.height: %f\n", &settings->m_ViewportHeight);
	fscanf(file, "Spellbar.left: %f\n", &settings->m_SpellbarLeft);
	fscanf(file, "Spellbar.bottom: %f\n", &settings->m_SpellbarBottom);
	fscanf(file, "Text.size: %f\n", &settings->m_TextSize);
	fscanf(file, "Text.columns: %d\n", &settings->m_TextColumns);
	fscanf(file, "Text.left: %f\n", &settings->m_TextLeft);
	fscanf(file, "Dialogue.top: %f\n", &settings->m_DialogueTop);
	fscanf(file, "Dialogue.rows: %d\n", &settings->m_DialogueRows);
	fscanf(file, "Query.top: %f\n", &settings->m_QueryTop);
	fscanf(file, "Input.top: %f\n", &settings->m_InputTop);

	*RBR = settings;

	return f_Success;
}

I32 bbGraphicsSettings_print(bbGraphicsSettings* settings){

	bbPrintf("%s definition settings\n", settings->m_GraphicsLevel);
	bbPrintf("Width: %d\n", settings->m_Width);
	bbPrintf("Height: %d\n", settings->m_Height);
	bbPrintf("Screen Scale: %f\n", settings->m_DrawableScale);
	bbPrintf("Widget Scale: %f\n", settings->m_WidgetScale);
	bbPrintf("Layout: %s\n", settings->m_Layout);
	bbPrintf("ViewportMock: %s\n", settings->m_ViewportMock);
	bbPrintf("ViewportTop: %f\n", settings->m_ViewportTop);
	bbPrintf("ViewportLeft: %f\n", settings->m_ViewportLeft);
	bbPrintf("ViewportWidth: %f\n", settings->m_ViewportWidth);
	bbPrintf("ViewportHeight: %f\n", settings->m_ViewportHeight);
	bbPrintf("SpellbarLeft: %f\n", settings->m_SpellbarLeft);
	bbPrintf("SpellbarBottom: %f\n", settings->m_SpellbarBottom);
	bbPrintf("TextSize: %f\n", settings->m_TextSize);
	bbPrintf("TextColumns: %d\n", settings->m_TextColumns);
	bbPrintf("TextLeft: %f\n", settings->m_TextLeft);
	bbPrintf("Dialogue.top: %f\n", settings->m_DialogueTop);
	bbPrintf("DialogueRows: %d\n", settings->m_DialogueRows);
	bbPrintf("Query.top: %f\n", settings->m_QueryTop);
	bbPrintf("InputTop: %f\n", settings->m_InputTop);

	return f_Success;
}