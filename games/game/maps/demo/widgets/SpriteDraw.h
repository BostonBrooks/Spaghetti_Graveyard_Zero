#include <inttypes.h>
#include "headers/bbWidget.h"
#include "headers/bbAnimation.h"
#include "headers/bbGame.h"
#include "headers/bbGeometry.h"



int32_t bbWidget_SpriteDraw (bbWidget* widget, int32_t i){

	int32_t map = widget->p_Node.p_Pool.Map;
	bbSprites* sprites = g_Game->m_Maps[map]->m_Sprites;
	int32_t spriteNum = widget->m_AnimationInt[i];
	sfSprite* sprite = sprites->m_Sprites[spriteNum];
    bbScreenCoordsI SCI = widget->m_ScreenCoords;
	sfVector2f position = bbScreenCoordsI_getV2f(SCI, &g_Game->m_Maps[map]->p_Constants);
	sfSprite_setPosition(sprite, position);
	sfRenderWindow_drawSprite(g_Game->m_Window, sprite, NULL);

	return f_Success;
}
