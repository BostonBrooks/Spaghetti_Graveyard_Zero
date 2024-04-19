#include <inttypes.h>
#include "headers/bbWidget.h"
#include "headers/bbAnimation.h"
#include "headers/bbGame.h"
#include "headers/bbGeometry.h"
#include "headers/bbIntTypes.h"



I32 bbWidgetDraw_Text (bbWidget* widget, I32 i){

    I32 map = widget->p_Node.p_Pool.Map;

    bbScreenCoordsI SCI = widget->m_ScreenCoords;
    sfVector2f positionV2f = bbScreenCoordsI_getV2f(SCI, &g_Game->m_Maps[map]->p_Constants);

    sfText_setPosition(widget->m_Text, positionV2f);

    sfRenderWindow_drawText(g_Game->m_Window, widget->m_Text, NULL);

    return f_Success;
}
