#include "color.h"
#include "../window/window.h"
#include "SDL.h"

Color BACKGROUND = {0, 0, 0};
Color FOREGROUND = {255, 255, 255};

void GAME_SetColor(Color color) {
    SDL_SetRenderDrawColor(
        GAME_Win.renderer,
        color.red,
        color.green,
        color.blue,
        0
    );
}