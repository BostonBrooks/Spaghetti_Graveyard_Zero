
#ifndef BBFONTS_H
#define BBFONTS_H


#include "engine/includes/CSFML.h"
#include "engine/logic/bbDictionary.h"
#include "engine/logic/bbIntTypes.h"
#include "engine/logic/bbTerminal.h"

typedef struct {

    I32 numFonts;
    bbDictionary* dictionary;
    sfFont* fonts[];

} bbFonts;

bbFlag bbFonts_new(bbFonts** self, char* filepath);


#endif //BBFONTS_H
