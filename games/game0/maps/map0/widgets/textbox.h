//textbox is a textbox

#include "engine/includes/CSFML.h"
#include "engine/logic/bbFlag.h"
#include "engine/userinterface/bbWidget.h"
#include "engine/userinterface/bbWidgetFunctions.h"
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
    rect.width = 50*POINTS_PER_PIXEL;
    rect.height = 11*POINTS_PER_PIXEL;

    widget->rect = rect;

    widget->ftable.OnCommand = bbWidgetFunctions_getInt(widgets->functions,WidgetOnCommand ,"TEXTBOX");

    int funcInt;
    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseIsOver,
                                  "HOVER");
    widget->mtable.isOver = funcInt;

    funcInt = bbMouseFunctions_getInt(&widgets->mouse->functions,MouseLeftDown,
                                  "TEXTBOX");
    widget->mtable.LeftDown = funcInt;

    widget->mtable.MouseIcon = 155;

    bbGraphicsApp* Graphics = graphics;
    bbPool_Handle drawfunctionHandle;
    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "TEXTBOX",
                        &drawfunctionHandle);
    widget->frames[0].drawfunction = drawfunctionHandle.u64;
    widget->frames[0].offset.x = 5;
    widget->frames[0].offset.y = 5;

    bbDictionary_lookup(Graphics->drawfunctions->dictionary, "TEXTBOXINDICATOR",
                        &drawfunctionHandle);
    widget->frames[1].drawfunction = drawfunctionHandle.u64;

    widget->type =  bbWidgetType_TextBox;

    char* string = calloc(1048, sizeof(char));

    widget->typeData.textBox.rows = 25;
    widget->typeData.textBox.columns = 25;

    bbStr_setStr(string , "", 1048);
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

//typedef bbFlag bbWidget_OnCommand (bbWidget* widget,bbWidgetCommandType type,  void* data);
bbFlag Textbox_OnCommand(bbWidget* widget, bbWidgetCommandType type, bbPool_Handle data){
    switch(type)
    {
         case bbWC_putChar:
             {
                 char ch = data.u64;
                 char* string = widget->typeData.textBox.string;
                 bbStr_putChar(string, ch, 1048);
                 bbStr_setBounds(string , widget->typeData.textBox.columns, widget->typeData.textBox.rows, 1048);

                 sfText_setString(widget->typeData.textBox.text, string);


                 break;
             }
    case bbWC_putStr:
             {
                 char* ch = data.ptr;
                 char* string = widget->typeData.textBox.string;
                 bbStr_putStr(string, ch, 1048);
                 bbStr_setBounds(string , widget->typeData.textBox.columns, widget->typeData.textBox.rows, 1048);

                 sfText_setString(widget->typeData.textBox.text, string);


                 break;
             }
        //TODO set textbox size in points. Bounds will be calculated based on font, font size and area
        case bbWC_setBounds:
             {
                 I32x2 bounds = data.i32x2;

                 widget->typeData.textBox.columns = bounds.x;
                 widget->typeData.textBox.rows = bounds.y;
                 bbStr_setBounds(widget->typeData.textBox.string,
                     widget->typeData.textBox.columns,
                     widget->typeData.textBox.rows,
                     1048);

                 sfText_setString(widget->typeData.textBox.text, widget->typeData.textBox.string);
                 break;
             }

    case bbWC_setDimensions:
             { //TODO get letter spacing and line spacing
                 I32x2 dimensions = data.i32x2;

                 widget->rect.width = dimensions.x;
                 widget->rect.height = dimensions.y;

                 sfText* text = widget->typeData.textBox.text;
                 float lineSpacing = 12;// != sfText_getLineSpacing(text);
                 float letterSpacing = 8;// != sfText_getLetterSpacing(text);
                 //int charsize = sfText_getCharacterSize(text);

                 //bbDebug("lineSpacing = %f, letterSpacing = %f, charsize = %d\n", lineSpacing, letterSpacing, charsize);


                 I32x2 bounds;
                 bounds.x = dimensions.x / (letterSpacing * SCREEN_PPP);
                 bounds.y = dimensions.y / (lineSpacing * SCREEN_PPP);

                 widget->typeData.textBox.columns = bounds.x;
                 widget->typeData.textBox.rows = bounds.y;
                 bbStr_setBounds(widget->typeData.textBox.string,
                     widget->typeData.textBox.columns,
                     widget->typeData.textBox.rows,
                     1048);

                 sfText_setString(widget->typeData.textBox.text, widget->typeData.textBox.string);
                 break;
             }
    case bbWC_setStr:
             {
                 char* ch = data.ptr;
                 char* string = widget->typeData.textBox.string;
                 bbStr_setStr(string, ch, 1048);
                 bbStr_setBounds(string , widget->typeData.textBox.columns, widget->typeData.textBox.rows, 1048);

                 sfText_setString(widget->typeData.textBox.text, string);


                 break;
             }
        case bbWC_clrStr:
        {
            char* ch = data.ptr;
            char* string = widget->typeData.textBox.string;
            bbStr_setStr(string, "", 1048);
            bbStr_setBounds(string , widget->typeData.textBox.columns, widget->typeData.textBox.rows, 1048);

            sfText_setString(widget->typeData.textBox.text, string);


            break;
        }

    }
    return Success;
}