#include "engine/graphics/bbColours.h"

sfColor bbRed;
sfColor bbRedOrange;
sfColor bbOrange;
sfColor bbYellowOrange;
sfColor bbYellow;
sfColor bbChartreuse;
sfColor bbGreen;
sfColor bbTeal;
sfColor bbBlue;
sfColor bbViolet;
sfColor bbPurple;
sfColor bbMagenta;



void bbColours_init(void){

    bbRed = sfColor_fromRGB(227, 35, 34);
    bbRedOrange = sfColor_fromRGB(233, 98, 32);
    bbOrange = sfColor_fromRGB(242, 142, 28);
    bbYellowOrange = sfColor_fromRGB(253, 198, 10);
    bbYellow = sfColor_fromRGB(243, 229, 0);
    bbChartreuse = sfColor_fromRGB(141, 187, 36);
    bbGreen = sfColor_fromRGB(0, 143, 90);
    bbTeal = sfColor_fromRGB(6, 150, 187);
    bbBlue = sfColor_fromRGB(42, 113, 175);
    bbViolet = sfColor_fromRGB(69,78, 153);
    bbPurple = sfColor_fromRGB(109,57, 139);
    bbMagenta = sfColor_fromRGB(197,3, 125);

}