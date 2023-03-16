#include "window.h"
#include "../shape/shape.h"
#include "../board/board.h"
#include "../util/util.h"
#include "SDL.h"

void GAME_Quit() {
    GAME_LogInfo("Quitting");
    GAME_FreeManyShapes();
    GAME_FreeBoard();
    SDL_DestroyWindow(GAME_Win.window);
    SDL_DestroyRenderer(GAME_Win.renderer);
    SDL_Quit();
}