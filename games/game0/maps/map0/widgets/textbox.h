//textbox is a textbox

#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"
#include "engine/widgets/bbWidgetFunctions.h"

//typedef bbFlag bbWidget_Constructor (bbWidget** reference, void* graphics,
//                                     bbWidgets* widgets, bbScreenPoints
//                                     screen_coords, bbWidget* parent);


bbFlag Textbox_Constructor (bbWidget** self, void* graphics,
                           bbWidgets* widgets, bbScreenPoints screen_coords, bbWidget* parent)
{
    bbWidget* widget;
    bbFlag flag =  bbWidget_newEmpty(&widget, widgets, parent);
    bbAssert(widget != NULL, "null address\n");


    bbScreenPointsRect rect;

    rect.left = screen_coords.x;
    rect.top = screen_coords.y;
    rect.width = 1;
    rect.height = 1;

    widget->rect = rect;

    bbGraphics* Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "TEXTBOX",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;
    widget->frames[0].offset.x = 0;
    widget->frames[0].offset.y = 0;

    widget->type =  bbWidgetType_TextBox;

    sfText* text = sfText_create();
    sfText_setString(text, "You look up to me for exaltation!");
    sfText_setFont(text, Graphics->fonts->fonts[0]);
    sfVector2f pos;
    pos.x = 50;
    pos.y = 50;
    sfText_setPosition(text, pos);
    sfText_setCharacterSize(text, 50);

    widget->typeData.textBox.text = text;


    *self = widget;


    return Success;
}

