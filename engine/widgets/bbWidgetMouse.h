#ifndef BBWIDGETMOUSE_H
#define BBWIDGETMOUSE_H

#include "engine/widgets/bbWidget.h"

//TODO split into .h and .c files

//typedef bbFlag bbWidget_Mouse(void* void_mouseEvent, void* void_widget);

bbFlag bbWM_Viewport(void* void_mouseEvent, void* void_widget){

	bbMouseEvent* event = void_mouseEvent;
	bbWidget* widget = void_widget;

	bbScreenPointsRect rect =  widget->rect;
	bbScreenPoints point = event->ScreenCoords;

	if (bbScreenPoints_inScreenPointsRect(point, rect)){
		printf("mouse within viewport\n");
	} else {
		printf("mouse not within viewport\n");
	}

	return Break;
}

bbFlag bbWidgetMouse_new(bbWidgetFunctions* functions){

	functions->Mouse = calloc(1,sizeof (bbWidget_Mouse*));

	functions->Mouse[0] = bbWM_Viewport;

	return Success;
}


#endif // BBWIDGET_MOUSE_H