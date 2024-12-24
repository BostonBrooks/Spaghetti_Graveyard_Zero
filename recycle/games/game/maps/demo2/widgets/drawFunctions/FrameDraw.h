///Draw one frame of animation without incrementing the frame number

#include <inttypes.h>
#include "recycle/headers/bbWidget.h"
#include "recycle/headers/bbAnimation.h"
#include "recycle/headers/bbGame.h"
#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbIntTypes.h"



I32 bbWidgetDraw_Frame (bbWidget* widget, I32 i){
	I32 animationInt = widget->m_AnimationInt[i];
	I32 angle = widget->m_Angle[i];
	I32 frame = widget->m_Frame[i];



	I32 map = widget->p_Node.p_Pool.Map;

	bbScreenCoordsI SCI = widget->m_ScreenCoords;
	bbScreenCoordsF SCF = bbScreenCoordsI_getF(SCI, &g_Game->m_Maps[map]->p_Constants);

	bbAnimation* animation = g_Game->m_Maps[map]->m_Animations->m_Animations[animationInt];

	I32 angles = animation->m_Angles;
	I32 frames = animation->m_Frames;


	bbSprites* sprites = animation->m_Sprites;

	I32 spriteInt = frames*angle+frame;

	I32 spriteNum = animation->i_Sprites[spriteInt];

	sfSprite* sprite = sprites->m_Sprites[spriteNum];

	sfVector2f position;
	position.x = SCF.x;
	position.y = SCF.y;

	sfSprite_setPosition(sprite, position);

	sfRenderWindow_drawSprite(g_Game->m_Window, sprite, NULL);



	return f_Success;
}
