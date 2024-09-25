#include "headers/bbSystemIncludes.h"
#include "headers/bbGame.h"
#include "headers/bbPrintf.h"
#include "headers/bbMap.h"
#include "headers/bbIntTypes.h"

I32 bbMap_new(bbMap** self, char* folderPath){

	bbMap* map = calloc(1, sizeof(bbMap));
	bbAssert(map != NULL, "calloc() failed\n");
	strcpy(&map->m_path, folderPath);
	char string[256]; I32 integer; float floatingPoint;
	sprintf(string, "%s/mapdata.txt", folderPath);
	FILE* file = fopen(string, "r");
	bbAssert(file != NULL, "fopen failed\n");
	fscanf(file, "%[^\n]\n", string);
	bbAssert(strcmp(string, "Map Data:") == 0, "bad mapdata.txt file\n");
	fscanf(file, "MapName: \"%[^\"]\"\n", string);
	strcpy(map->m_String, string);
	sprintf(string, "%s: %s", g_Game->m_GameName, map->m_String);
	//Why does this line take so long to take effect?
	sfRenderWindow_setTitle(g_Game->m_Window, string);



	fscanf(file, "DrawableScale: %f\n", &floatingPoint);
	map->p_Constants.DrawableScale = floatingPoint;
	fscanf(file, "WidgetScale: %f\n", &floatingPoint);
	map->p_Constants.WidgetScale = floatingPoint;
	fscanf(file, "ElevationScale: %d\n", &integer);
	map->p_Constants.ElevationScale = integer;
	fscanf(file, "MaxPixelValue: %d\n", &integer);
	map->p_Constants.MaxPixelValue = integer;
	fscanf(file, "PointsPerPixel: %d\n", &integer);
	map->p_Constants.PointsPerPixel = integer;
	fscanf(file, "PixelsPerTile: %d\n", &integer);
	map->p_Constants.PixelsPerTile = integer;
	fscanf(file, "TilesPerSquare: %d\n", &integer);
	map->p_Constants.TilesPerSquare = integer;
	fscanf(file, "SquaresPerMapI: %d\n", &integer);
	map->p_Constants.SquaresPerMapI = integer;
	fscanf(file, "SquaresPerMapJ: %d\n", &integer);
	map->p_Constants.SquaresPerMapJ = integer;
	fscanf(file, "ScreenPointsPerPixel: %d\n", &integer);
	map->p_Constants.ScreenPPP = integer;
	fscanf(file, "Textures: %d\n", &integer);
	map->p_Constants.Textures = integer;
	fscanf(file, "Sprites: %d\n", &integer);
	map->p_Constants.Sprites = integer;
	fscanf(file, "Animations: %d\n", &integer);
	map->p_Constants.Animations = integer;
	fscanf(file, "Skins: %d\n", &integer);
	map->p_Constants.Skins = integer;
	fscanf(file, "Widget_Constructors: %d\n", &integer);
	map->p_Constants.Widget_Constructors = integer;
	fscanf(file, "Widget_DrawFunctions: %d\n", &integer);
	map->p_Constants.Widget_DrawFunctions = integer;
	fscanf(file, "Widget_Destructors: %d\n", &integer);
	map->p_Constants.Widget_Destructors = integer;
	fscanf(file, "Widget_OnCommands: %d\n", &integer);
	map->p_Constants.Widget_OnCommands = integer;
    fscanf(file, "Widget_Mouses: %d\n", &integer);
    map->p_Constants.Widget_Mouses = integer;

	fclose(file);

	map->p_Constants.PointsPerTile = map->p_Constants.PointsPerPixel * map->p_Constants.PixelsPerTile;
	map->p_Constants.PointsPerSquare = map->p_Constants.PointsPerTile * map->p_Constants.TilesPerSquare;
	map->p_Constants.PixelsPerSquare = map->p_Constants.PixelsPerTile *  map->p_Constants.TilesPerSquare;

    map->misc.m_MapTime = 0;
	*self = map;

}
