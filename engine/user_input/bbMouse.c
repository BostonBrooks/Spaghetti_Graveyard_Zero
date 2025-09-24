
#include "engine/logic/bbFlag.h"
#include "engine/includes/CSFML.h"
#include "engine/user_input/bbInput.h"
#include "engine/user_input/bbMouse.h"
#include "engine/graphics/bbGraphics.h"
#include "engine/geometry/bbCoordinates.h"
#include "engine/widgets/bbWidget.h"

extern bbWidgets* testWidgets;
extern bbWidgetFunctions* testFunctions;


bbFlag bbMouse_new(bbMouse* mouse, sfRenderWindow* window,bbGraphics* graphics)
{
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    mouse->cursor = graphics->sprites->sprites[85];
}
bbFlag bbMouse_update(bbMouse* mouse, sfEvent* event){

    switch (event->type){
        case sfEvtMouseMoved:
            mouse->position = pixel_getScreenPoints(event->mouseMove.x,
                                                    event->mouseMove.y);

			bbMouseEvent mouseEvent;
			mouseEvent.ScreenCoords = mouse->position;
			mouseEvent.action = 0;

			mouseActionClosure cl;
			cl.event = &mouseEvent;
			cl.functions = testFunctions;

            //TODO call onMouse in main?
			//bbWidgets_onMouse(testWidgets, &cl);

            break;
        default:{
            bbDebug("input not recognised\n");
        }
    }
}


bbFlag bbMouse_draw(bbMouse* mouse, sfRenderWindow* window){
    sfVector2f pos = bbScreenPoints_getV2f(mouse->position);
    sfSprite_setPosition(mouse->cursor, pos);
    sfRenderWindow_drawSprite(window, mouse->cursor, NULL);
}