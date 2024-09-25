/**
 * @file bbGame
* @brief bbGame is the root of all data stored by the game.
 *
*/
#ifndef BBGAME_H
#define BBGAME_H

#include "bbSystemIncludes.h"
#include "bbEngineConstants.h"
#include "bbGameConstants.h"
#include "bbMap.h"
#include "bbGraphicsSettings.h"

#include "bbIntTypes.h"


typedef struct {
	bbGameConstants m_Constants;
	sfRenderWindow* m_Window;
	//bbViewport* m_Viewport; //viewport is a bbWidget
	I32 m_CurrentMap;
	char m_MapNames[N_MAPS][256];
	I32 m_GlobalTime;
	///data for the game can be stored in any location in the file system
	char* m_FolderPath;
	char* m_GameName;

	bbGraphicsSettings* m_GraphicsSettings;
	bbMap* m_Maps[N_MAPS];

} bbGame;

extern bbGame* g_Game;


I32 bbGame_new(bbGame** self, char* folder_path);

#endif //BBGAME_H