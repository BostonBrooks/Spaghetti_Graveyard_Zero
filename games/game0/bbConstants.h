/**
 * @file
 *
 * @ingroup
 * @brief this header file defines numerical constants used to compile a game
 * using the game engine.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define KEY_LENGTH            33

//TODO POINTS_PER_PIXEL needs to be separates from SCREEN_PPP
#define POINTS_PER_PIXEL      8
#define PIXELS_PER_TILE       16
#define POINTS_PER_TILE       (POINTS_PER_PIXEL*PIXELS_PER_TILE)
#define TILES_PER_SQUARE      32
#define PIXELS_PER_SQUARE     (PIXELS_PER_TILE * TILES_PER_SQUARE)
#define POINTS_PER_SQUARE     (POINTS_PER_PIXEL * PIXELS_PER_TILE * TILES_PER_SQUARE)
#define SQUARES_PER_MAP	      5
#define TILES_PER_MAP         (TILES_PER_SQUARE * SQUARES_PER_MAP)
#define PIXELS_PER_MAP        (PIXELS_PER_TILE * TILES_PER_MAP)
#define POINTS_PER_MAP        (POINTS_PER_PIXEL * PIXELS_PER_MAP)

#define MILLS_PER_POINT       1024
#define MILLS_PER_PIXEL       (MILLS_PER_POINT * POINTS_PER_PIXEL)
#define MILLS_PER_TILE        (MILLS_PER_POINT * POINTS_PER_TILE)
#define MILLS_PER_SQUARE      (MILLS_PER_POINT * POINTS_PER_SQUARE)

#define MAPICON_SCALE         8
#define SCREEN_PPP            8
#define SCREEN_PPPf           8.f

#endif //CONSTANTS_H