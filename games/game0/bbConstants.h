/**
 * @file
 *
 * @ingroup
 * @brief this header file defines numerical constants used to compile a game
 * using the game engine.
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H



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


#endif //CONSTANTS_H