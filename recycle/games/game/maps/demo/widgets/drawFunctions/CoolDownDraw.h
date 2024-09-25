#include <inttypes.h>
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbAnimation.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbGeometry.h"



I32 bbWidgetDraw_Cooldown (bbWidget* widget, I32 i){


    sfRectangleShape* rect = widget->m_RedRect;
    bbMap* map = g_Game->m_Maps[widget->p_Node.p_Pool.Map];
    bbMapConstants* constants = &map->p_Constants;

    sfVector2f position = bbScreenCoordsI_getV2f(widget->m_ScreenCoords, constants);
    sfVector2f size = bbScreenCoordsI_getV2f(widget->m_Dimensions, constants);


    float timeRemaining = widget->m_CoolDownEnd - map->misc.m_MapTime;
    if (timeRemaining <= 0) return f_Success;
    float timeDenominator = widget->m_CoolDownEnd - widget->m_CoolDownStart;

    float timeFraction = timeRemaining / timeDenominator;


    sfVector2f rectanglePosition;
    sfVector2f rectangleSize;

    rectanglePosition.x = position.x;
    rectanglePosition.y = position.y + (1-timeFraction) * size.y;
    rectangleSize.x = size.x;
    rectangleSize.y = size.y * timeFraction;


    sfRectangleShape_setPosition(rect,rectanglePosition);
    sfRectangleShape_setSize(rect, rectangleSize);

	sfRenderWindow_drawRectangleShape(g_Game->m_Window, rect, NULL);



	return f_Success;
}
