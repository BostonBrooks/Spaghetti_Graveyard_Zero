
#include "engine/logic/bbFlag.h"
#include "engine/includes/csfml.h"
#include "engine/user_input/bbInput.h"
#include "engine/user_input/bbMouse.h"
#include "engine/graphics/bbGraphics.h"
#include "engine/geometry/bbCoordinates.h"


bbFlag bbMouse_new(bbMouse* mouse, sfRenderWindow* window,bbGraphics* graphics)
{
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    mouse->cursor = graphics->sprites->sprites[4];
}
bbFlag bbMouse_update(bbMouse* mouse, sfEvent* event){
    switch (event->type){
        case sfEvtMouseMoved:
            mouse->position = pixel_getScreenPoints(event->mouseMove.x,
                                                    event->mouseMove.y);
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