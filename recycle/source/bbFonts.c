/// stuff for fonts and drawing sfText here

#include <inttypes.h>
#include "headers/bbSystemIncludes.h"
#include "headers/bbDictionary.h"
#include "headers/bbFonts.h"
#include "headers/bbIntTypes.h"


I32 bbFonts_new(bbFonts** self, char* folderPath, I32 numTextures){

    if (folderPath == NULL) {
        bbFonts *fonts = calloc(1, sizeof(bbFonts));
        fonts->m_Fonts = calloc(1, sizeof(sfFont *));
        fonts->m_Fonts[0] = sfFont_createFromFile("../games/game/graphics/Bowman.ttf");
        bbAssert(fonts->m_Fonts[0] != NULL, "Bowman font failed to load");
        *self = fonts;
    }
    return f_Success;
}


