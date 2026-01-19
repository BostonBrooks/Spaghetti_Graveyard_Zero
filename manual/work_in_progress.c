
#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
bbFlag bbWidget_constructor2(bbWidget** self,
                             bbWidgets* widgets,
                             char* type,
                             char* parent,
                             char* name,
                             I32 position_x,
                             I32 position_y);


typedef bbFlag bbWidget_Constructor2 (bbWidget** self,
                                      bbWidgets* widgets,
                                      bbWidget* parent,
                                      char* name,
                                      bbScreenPoints screen_points,
                                      bbGraphicsApp* graphics
                                      );

