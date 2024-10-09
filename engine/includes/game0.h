/**
 * @file
 *
 * @ingroup
 * @brief this header includes all the files in games/game0 used to compile
 * the engine for that specific game. all references to "game0" are found in
 * this file, modify this file only to compile for a different game
 */

#ifndef GAME_H
#define GAME_H

#define GAME_NAME "game0"

#define STR_IMPL(A) #A
#define STR(A) STR_IMPL(A)

#define RESOURCE_FILE bbConstants.h
#define PROJECT_DIRECTORY games/game0
#define RESOURCE_PATH STR(PROJECT_DIRECTORY/RESOURCE_FILE)

#include RESOURCE_PATH

#undef STR_IMPL()
#undef STR()
#undef RESOURCE_FILE

#endif //GAME_H