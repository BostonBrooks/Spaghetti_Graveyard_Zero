#ifndef BBGRAPHICSCONSTANTS_H
#define BBGRAPHICSCONSTANTS_H

#include "bbEngineConstants.h"
#include "bbIntTypes.h"


typedef struct {
	char m_GraphicsLevel[KEY_LENGTH];
	I32 m_Width;
	I32 m_Height;
	float m_DrawableScale;
	float m_WidgetScale;
	char m_Layout[KEY_LENGTH];
	char m_ViewportMock[KEY_LENGTH];
	float m_ViewportTop;
	float m_ViewportLeft;
	float m_ViewportWidth;
	float m_ViewportHeight;
	float m_SpellbarLeft;
	float m_SpellbarBottom;
	float m_TextSize;
	int m_TextColumns;
	float m_TextLeft;
	float m_DialogueTop;
	int m_DialogueRows;
	float m_QueryTop;
	float m_InputTop;
} bbGraphicsSettings;

I32 bbGraphicsSettings_new(bbGraphicsSettings** RBR, char* filePath);

I32 bbGraphicsSettings_print(bbGraphicsSettings* settings);
#endif // BBGRAPHICSCONSTANTS_H