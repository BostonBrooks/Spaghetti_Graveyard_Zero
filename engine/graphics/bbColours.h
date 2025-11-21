#ifndef BBCOLOURS_H
#define BBCOLOURS_H

#include "engine/includes/CSFML.h"
#include "engine/logic/bbTerminal.h"
#include "engine/data/bbHome.h"

///Clear the window to a given colour.
/// Used to see if the graphics library is functioning, because the graphics
/// library may crash long before the main thread realises



#define CLEARWINDOW(COLOUR) \
        bbHere();                    \
        sfRenderWindow_clear(home.private.window, COLOUR);\
        sfRenderWindow_display(home.private.window);


extern sfColor bbRed;
extern sfColor bbRedOrange;
extern sfColor bbOrange;
extern sfColor bbYellowOrange;
extern sfColor bbYellow;
extern sfColor bbChartreuse;
extern sfColor bbGreen;
extern sfColor bbTeal;
extern sfColor bbBlue;
extern sfColor bbViolet;
extern sfColor bbPurple;
extern sfColor bbMagenta;

extern sfColor bbWhite;
extern sfColor bbLight;
extern sfColor bbGrey;
extern sfColor bbDark;
extern sfColor bbBlack;

void bbColours_init(void);

#endif //BBCOLOURS_H