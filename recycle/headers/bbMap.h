/**
 * @file
 * @brief bbMap stores game data pertaining to one map in the game
 */
#ifndef BBMAP_H
#define BBMAP_H

#include "bbSystemIncludes.h"
#include "bbMapConstants.h"
#include "bbTextures.h"
#include "bbSprites.h"
#include "bbAnimation.h"
#include "bbWidget.h"
#include "bbFonts.h"
#include "bbIntTypes.h"
#include "bbList.h"
#include "bbWidgetTimer.h"


typedef struct {
    /// Increased with every update of the map
    I32 m_MapTime;
    I32 m_ActiveTextbox_deprecated;
    I32 m_ActiveSpell_deprecated;
    I32 m_SpellBar_deprecated;
} bbMapState;

typedef struct {

	bbMapConstants p_Constants;

	char* m_path;  //path to map folder

	char m_String[128];
	bbTextures* m_Textures;
	bbSprites* m_Sprites;
	bbAnimations* m_Animations;
    bbFonts* m_Fonts;
	//bbSkins* m_Skins;

	//vtables

	//bbElevations* m_Elevations;
	//bbTerrainSquares* m_Terrain;
	//bbDrawables* m_Drawables;
	//bbActors* m_Actors;
	bbWidgets* m_Widgets;
    bbWidgetTimer* m_WidgetTimer;

	//bbMapCoords m_Viewpoint;
	//I32 m_ViewpointDrawable;

    bbMapState misc;
} bbMap;


I32 bbMap_new(bbMap** self, char* folderPath);

#endif //BBMAP_H
