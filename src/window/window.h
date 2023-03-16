#ifndef SRC_WINDOW_H
#define SRC_WINDOW_H

#include "../macros.h"

typedef struct GAME_WindowAndRenderer {
    SDL_Renderer *renderer;
    SDL_Window *window;
} GameWin;

extern GameWin GAME_Win;
extern int running;

int GAME_WindowInit();
void GAME_Quit();

#endif