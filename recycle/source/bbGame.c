#include "headers/bbSystemIncludes.h"
#include "headers/bbGame.h"
#include "headers/bbPrintf.h"
#include "headers/bbIntTypes.h"
#include "headers/bbGraphicsSettings.h"

I32 bbGame_new(bbGame** RBR, char* folderPath){

	bbGame* game = calloc(1, sizeof(bbGame));
	bbAssert(game != NULL, "calloc failed\n");

	game->m_FolderPath = calloc(256, sizeof(char));
	bbAssert(game->m_FolderPath != NULL, "calloc failed\n");
	game->m_GameName = calloc(256, sizeof(char));
	bbAssert(game->m_GameName != NULL, "calloc failed\n");
	strcpy(game->m_FolderPath, folderPath);
	char string[256];
	I32 integer;
	float floatingPoint;

	sprintf(string, "%s/gamedata.txt", folderPath);


	FILE* file = fopen(string, "r");
	bbAssert(file != NULL, "fopen failed\n");

	fscanf(file, "%[^\n]\n", string);
	bbAssert(strcmp(string, "GraphicsSettings:") == 0, "bad gamedata.txt file\n");
	fscanf(file, "Title: \"%[^\"]\"\n", string);
	strcpy(game->m_GameName, string);
	fscanf(file, "Height: %d\n", &integer);
	game->m_Constants.Height = integer;
	fscanf(file, "Width: %d\n", &integer);
	game->m_Constants.Width = integer;
	fscanf(file, "%[^\n]\n", string);
	bbAssert(strcmp(string, "Maps:") == 0, "bad gamedata.txt file\n");

	for(int i = 0; i < N_MAPS; i++){
		strcpy(game->m_MapNames[i], "NULL");
	}

	while(fscanf(file, "%d, %[^\n]\n", &integer, string) == 2){
		strcpy(&game->m_MapNames[integer], string);
	}

	fclose(file);

#ifdef GRAPHICS_LOW
	sprintf(string, "%s/graphics-low.txt", folderPath);
#else
	sprintf(string, "%s/graphics-medium.txt", folderPath);
#endif
	bbGraphicsSettings_new(&game->m_GraphicsSettings, string);
	//bbGraphicsSettings_print(game->m_GraphicsSettings);

	sfVideoMode mode;
	mode.height = game->m_GraphicsSettings->m_Height;
	mode.width = game->m_GraphicsSettings->m_Width;
	mode.bitsPerPixel = 32;

	bbDebug("GameName: %s\n", game->m_GameName);
	sfRenderWindow* window = sfRenderWindow_create(mode, game->m_GameName, sfResize | sfClose, NULL);
    //sfRenderWindow_setFramerateLimit(window, 120);
	sfColor beige = COLOUR_BEIGE;
	sfRenderWindow_clear(window, beige);
	sfRenderWindow_display(window);

	game->m_Window = window;
	*RBR = game;

	return f_Success;
}
