#include "headers/bbGeometry.h"
#include "headers/bbGame.h"
#include "headers/bbWidget.h"
#include "headers/bbIntTypes.h"


bbScreenCoordsF bbScreenCoordsI_getF(bbScreenCoordsI SCI, bbMapConstants* constants){
	bbScreenCoordsF SCF;
	SCF.x = (float)SCI.x / (float)constants->ScreenPPP;
	SCF.y = (float)SCI.y / (float)constants->ScreenPPP;
	return SCF;
}
bbScreenCoordsI bbScreenCoordsF_getI(bbScreenCoordsF SCF, bbMapConstants* constants){
	bbScreenCoordsI SCI;
	SCI.x = SCF.x * constants->ScreenPPP;
	SCI.y = SCF.y * constants->ScreenPPP;
	return SCI;
}

sfVector2f bbScreenCoordsI_getV2f(bbScreenCoordsI SCI, bbMapConstants* constants){
    sfVector2f SCF;
    SCF.x = (float)SCI.x / (float)constants->ScreenPPP;
    SCF.y = (float)SCI.y / (float)constants->ScreenPPP;
    return SCF;
}

bool bbWidget_containsPoint(void* void_widget, bbScreenCoordsI SCI){
    //assuming origin is top left, dimensions are positive
    bbWidget* widget = void_widget;
    int top = widget->m_ScreenCoords.y;
    int bottom = widget->m_ScreenCoords.y + widget->m_Dimensions.y;
    int left = widget->m_ScreenCoords.x;
    int right = widget->m_ScreenCoords.x + widget->m_Dimensions.x;

    if (SCI.y < top) return false;
    if (SCI.y > bottom) return false;
    if (SCI.x < left) return false;
    if (SCI.x > right) return false;

    return true;
}