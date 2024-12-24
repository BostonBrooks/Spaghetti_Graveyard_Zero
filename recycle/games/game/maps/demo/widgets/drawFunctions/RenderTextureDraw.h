#include <inttypes.h>
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbAnimation.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbGeometry.h"

#include "recycle/headers/bbIntTypes.h"

I32 bbWidgetDraw_RenderTexture (bbWidget* widget, I32 i){
	I32 map = widget->p_Node.p_Pool.Map;
	sfRenderTexture_display(widget->m_RenderTexture);
	sfSprite* sprite = widget->m_Sprite;

	bbScreenCoordsI SCI = widget->m_ScreenCoords;
	sfVector2f position = bbScreenCoordsI_getV2f(SCI, &g_Game->m_Maps[map]->p_Constants);
	sfSprite_setPosition(sprite, position);
	sfRenderWindow_drawSprite(g_Game->m_Window, sprite, NULL);

	return f_Success;
}