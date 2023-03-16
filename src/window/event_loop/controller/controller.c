#include "controller.h"
#include "../../../shape/shape.h"
#include "../../../board/board.h"
#include "../../../util/util.h"
#include "SDL.h"

void GAME_ControllerKey(SDL_KeyboardEvent *event) {
    switch (event->keysym.scancode) {
        case SDL_SCANCODE_LEFT:
            if (currentSelect != NULL) {
                if (GAME_DetectBoardCollision(currentSelect, LEFT_EDGE) == 0) {
                    if (GAME_DetectBoardCollision(currentSelect, BOTTOM_EDGE) == 0) {
                        if (GAME_DetectBoardShapeCollision(currentSelect, RIGHT_EDGE)) {
                            return;
                        }
                        GAME_UpdateXPosition(currentSelect, 1, 0);
                    }
                }
            }
            break;
        case SDL_SCANCODE_RIGHT:
            if (currentSelect != NULL) {
                if (GAME_DetectBoardCollision(currentSelect, RIGHT_EDGE) == 0) {
                    if (GAME_DetectBoardCollision(currentSelect, BOTTOM_EDGE) == 0) {
                        if (GAME_DetectBoardShapeCollision(currentSelect, LEFT_EDGE)) {
                            return;
                        }
                        GAME_UpdateXPosition(currentSelect, 0, 1);
                    }
                }
            }
            break;
        case SDL_SCANCODE_UP:
            /* Rotate Shape */
            if (currentSelect != NULL && event->repeat == 0) {
                GAME_RotateShape(currentSelect);
            }
            break;
        case SDL_SCANCODE_DOWN:
            SHAPE_DELAY = 10;
            break;
    }
}