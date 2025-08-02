#ifndef BBWODGETMOUSE_H
#define BBWODGETMOUSE_H

#include "engine/wodgets/bbWodget.h"

//TODO split into .h and .c files

//typedef bbFlag bbWodget_Mouse(void* void_mouseEvent, void* void_wodget);

bbFlag bbWM_Viewport(void* void_mouseEvent, void* void_wodget){

	bbMouseEvent* event = void_mouseEvent;
	bbWodget* wodget = void_wodget;

	bbScreenPointsRect rect =  wodget->rect;
	bbScreenPoints point = event->ScreenCoords;

	if (bbScreenPoints_inScreenPointsRect(point, rect)){
		printf("mouse within viewport\n");
	} else {
		printf("mouse not within viewport\n");
	}

	return Break;
}

bbFlag bbWodgetMouse_new(bbWodgetFunctions* functions){

	functions->Mouse = calloc(1,sizeof (bbWodget_Mouse*));

	functions->Mouse[0] = bbWM_Viewport;

	return Success;
}


#endif // BBWODGET_MOUSE_H