/* Game widget doesn't draw anything to the screen, it just acts as a layer/container for
 * The viewport, dialog, prompt and command textboxes */

#include "engine/includes/CSFML.h"
#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"
#include "engine/logic/bbString.h"

bbFlag GAME_Constructor2 (bbWidget** self,
                            bbWidgets* widgets,
                            bbWidget* parent,
                            char* name,
                            bbScreenPoints screen_coords,
                            bbGraphicsApp* graphics
                            )
{
    bbWidget* widget;
    bbWidget_newEmpty2(&widget, widgets, parent, name);

    bbScreenPointsRect rect;


    rect.left = 0;
    rect.top = 0;
    rect.width = 720 * SCREEN_PPP;
    rect.height = 480 * SCREEN_PPP;
    widget->rect = rect;

    bbPool_Handle dimensions;
    bbFlag flag;
    bbWidget* textbox_widget;

    flag = bbWidget_constructor2(&textbox_widget,
                 widgets,
                 "TEXTBOX",
                 name,
                 "DIALOG",
                 497*SCREEN_PPP,
                 12*SCREEN_PPP);

    dimensions.i32x2.x = 200*SCREEN_PPP;
    dimensions.i32x2.y = 322*SCREEN_PPP;
    if (flag == Success) bbWidget_onCommand(textbox_widget, widgets, bbWC_setDimensions, dimensions);

    flag = bbWidget_constructor2(&textbox_widget,
                 widgets,
                 "TEXTBOX",
                 name,
                 "PROMPT",
                 497*SCREEN_PPP,
                 355*SCREEN_PPP);

    dimensions.i32x2.x = 200*SCREEN_PPP;
    dimensions.i32x2.y = 45*SCREEN_PPP;
    if (flag == Success) bbWidget_onCommand(textbox_widget, widgets, bbWC_setDimensions, dimensions);


    flag = bbWidget_constructor2(&textbox_widget,
                 widgets,
                 "TEXTBOX",
                 name,
                 "COMMAND",
                 497*SCREEN_PPP,
                 416*SCREEN_PPP);

    dimensions.i32x2.x = 200*SCREEN_PPP;
    dimensions.i32x2.y = 45*SCREEN_PPP;
    if (flag == Success) bbWidget_onCommand(textbox_widget, widgets, bbWC_setDimensions, dimensions);
    dimensions.i32x2.x = 64*SCREEN_PPP;
    dimensions.i32x2.y = 1*SCREEN_PPP;
    if (flag == Success) bbWidget_onCommand(textbox_widget, widgets, bbWC_setBounds, dimensions);



}