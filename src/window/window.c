#include "SDL.h"
#include "window.h"
#include "../util/util.h"

GameWin GAME_Win;

int GAME_WindowInit() {
    int init = SDL_Init(SDL_INIT_VIDEO);

    if (init < 0) {
        GAME_LogError("SDL_Init");
        return -1;
    }

    GAME_Win.window = SDL_CreateWindow(TITLE,
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            WIDTH, HEIGHT,
                            SDL_WINDOW_RESIZABLE);

    GAME_Win.renderer = SDL_CreateRenderer(GAME_Win.window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(GAME_Win.renderer, WIDTH, HEIGHT);

    if (GAME_Win.window == NULL) {
        GAME_LogError("SDL_CreateWindow");
        exit(-1);
    }

    if (GAME_Win.renderer == NULL) {
        GAME_LogError("SDL_CreateWindow");
        exit(-1);
    }
    GAME_LogInfo("SDL_Init Success");
    return 0;
}
