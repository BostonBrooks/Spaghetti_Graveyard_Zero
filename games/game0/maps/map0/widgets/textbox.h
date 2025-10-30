//textbox is a textbox

#include "engine/logic/bbFlag.h"
#include "engine/widgets/bbWidget.h"
#include "engine/widgets/bbWidgetFunctions.h"
#include "engine/logic/bbString.h"

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

    widget->ftable.OnCommand = bbWidgetFunctions_getInt(widgets->functions,WidgetOnCommand ,"TEXTBOX");

    bbGraphics* Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "TEXTBOX",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;
    widget->frames[0].offset.x = 5;
    widget->frames[0].offset.y = 5;

    widget->type =  bbWidgetType_TextBox;

    char* string = calloc(1048, sizeof(char));

    widget->typeData.textBox.rows = 25;
    widget->typeData.textBox.columns = 25;

    bbStr_setStr(string , "Sed ut perspiciatis, unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam eaque ipsa, quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt, explicabo. Nemo enim ipsam voluptatem, quia voluptas sit, aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos, qui ratione voluptatem sequi nesciunt, neque porro quisquam est, qui dolorem ipsum, quia dolor sit amet consectetur adipisci[ng] velit, sed quia non numquam [do] eius modi tempora inci[di]dunt, ut labore et dolore magnam aliquam quaerat voluptatem. Ut enim ad minima veniam, quis nostrum[d] exercitationem ullam corporis suscipit laboriosam, nisi ut aliquid ex ea commodi consequatur? [D]Quis autem vel eum i[r]ure reprehenderit, qui in ea voluptate velit esse, quam nihil molestiae consequatur, vel illum, qui dolorem eum fugiat, quo voluptas nulla pariatur?", 1048);
    bbStr_setBounds(string , widget->typeData.textBox.columns, widget->typeData.textBox.rows, 1048);
    widget->typeData.textBox.string = string;


    sfText* text = sfText_create();
    sfText_setString(text, widget->typeData.textBox.string);
    sfText_setFont(text, Graphics->fonts->fonts[0]);
    bbScreenPoints pts;
    pts.x = screen_coords.x + widget->frames[0].offset.x;
    pts.y = screen_coords.y + widget->frames[0].offset.y;
    sfVector2f pos;
    pos = bbScreenPoints_getV2f(pts);
    sfText_setPosition(text, pos);
    sfText_setCharacterSize(text, 15);
    sfText_setColor(text, sfBlack);

    widget->typeData.textBox.text = text;


    *self = widget;

    return Success;
}

//typedef bbFlag bbWidget_OnCommand (bbWidget* widget,WidgetCommandType type,  void* data);
bbFlag Textbox_OnCommand(bbWidget* widget,WidgetCommandType type,  void* data){
    switch(type)
    {
         case bbWC_putChar:
            char* ch = data;
            char* string = widget->typeData.textBox.string;
            bbStr_putChar(string, *ch, 1048);
            bbStr_setBounds(string , widget->typeData.textBox.columns, widget->typeData.textBox.rows, 1048);

            sfText_setString(widget->typeData.textBox.text, string);


        break;

        case bbWC_setBounds:
            I32x2* bounds = data;

            widget->typeData.textBox.columns = bounds->x;
            widget->typeData.textBox.rows = bounds->y;
            bbStr_setBounds(widget->typeData.textBox.string,
                widget->typeData.textBox.columns,
                widget->typeData.textBox.rows,
                1048);

        sfText_setString(widget->typeData.textBox.text, widget->typeData.textBox.string);
        break;
    }
    return Success;
}