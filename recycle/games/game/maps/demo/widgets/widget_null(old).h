/**
 * @file
 * @brief The functions in this folder define the behavior of an object with class bbWidget and type NULL
 */
#include "recycle/headers/bbGeometry.h"
#include "recycle/headers/bbWidget.h"

///	Spawn a null widget on selected map at coordinates mc
I32 bbWidget_NULL_new(bbWidget** reference, bbWidgets* widgets, bbScreenCoordsI screen_coords, I32 parent){}

/// Update widget
I32 bbWidget_NULL_update(bbWidget* widget){}

/// Send a command to the widget / update widget, etc
I32 bbWidget_NULL_onCommand(bbWidget* widget, I32 command, void* data){}

/// Delete widget
I32 bbWidget_NULL_delete(bbWidget* widget){}

/// Draw widget to screen
I32 bbWidget_NULL_draw(bbWidget* widget){}