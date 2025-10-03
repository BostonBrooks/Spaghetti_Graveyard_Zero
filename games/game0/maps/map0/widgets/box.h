//box is a test bbWidget. eventually you will be able to click and draw the box.


#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"
#include "engine/widgets/bbWidgetFunctions.h"

//typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
//                                     bbWidgets* widgets, bbScreenPoints
//                                     screen_coords, bbWidget* parent);



bbFlag SPHERE_Mouse (bbWidget* widget, void* cl)
{


    mouseActionClosure* closure = cl;
    bbMouse* mouse = closure->mouse;


    bbScreenPoints point = mouse->position;

    bbScreenPointsRect rect = widget->rect;

    if (bbScreenPoints_inScreenPointsRect(point, rect)){

        bbDebug("Mouse interacts with Sphere\n");
        widget->rect.left = rand()%(720*8 - 52*8);
        widget->rect.top = rand()%(480*8 - 52*8);

    }



    return Continue;
}