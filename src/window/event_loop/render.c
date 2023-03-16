#include "../window.h"
#include "../../shape/shape.h"
#include "../../color/color.h"
#include "../../util/util.h"
#include "loop.h"
#include "SDL.h"

void GAME_Clear() {
    SDL_RenderClear(GAME_Win.renderer);
}

void GAME_DrawLine(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(GAME_Win.renderer, x1, y1, x2, y2);
}

void GAME_RenderRect(SDL_Rect *rect) {
    if (rect != NULL) {
        SDL_RenderDrawRect(GAME_Win.renderer, rect);
    }
}

void GAME_RenderShape(Shape *shape) {
    if (shape->color != NULL)
        GAME_SetColor(*(shape->color));

    GAME_RenderRect(shape->r1);
    GAME_RenderRect(shape->r2);
    GAME_RenderRect(shape->r3);
    GAME_RenderRect(shape->r4);
}

void GAME_RenderBoardShapes() {
    if (shapes == NULL) return;

    for (int i = 0; i < SHAPES_ARRAY_LENGTH; i++) {
        if (shapes[i] != NULL) {
            GAME_RenderShape(shapes[i]);
        }
        // TODO: free up and reuse space in shapes if type == 0
    }
}
