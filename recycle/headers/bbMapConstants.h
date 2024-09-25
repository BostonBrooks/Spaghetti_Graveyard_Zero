
/// contains data about the map

#ifndef BBMAPCONSTANTS_H
#define BBMAPCONSTANTS_H
#include "bbIntTypes.h"
#include "bbSystemIncludes.h"



typedef struct{
	float DrawableScale;
	float WidgetScale;
	I32 ElevationScale;
	I32 MaxPixelValue;
	I32 PointsPerPixel;
	I32 PixelsPerTile;
	I32 TilesPerSquare;
	I32 SquaresPerMapI;
	I32 SquaresPerMapJ;
	I32 ScreenPPP;
	I32 Textures;
	I32 Sprites;
	I32 Animations;
	I32 Skins;
	I32 Widget_Constructors;
	I32 Widget_DrawFunctions;
	I32 Widget_Updates;
	I32 Widget_Destructors;
	I32 Widget_OnCommands;
    I32 Widget_Mouses;
	I32 PointsPerTile;
	I32 PointsPerSquare;
	I32 PixelsPerSquare;

}bbMapConstants;

#endif // BBMAPCONSTANTS_H
