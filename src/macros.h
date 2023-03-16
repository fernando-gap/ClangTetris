#ifndef SRC_MACROS_H
#define SRC_MACROS_H

#include <bits/stdint-uintn.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

/* Board */
#define BOARD_HEIGHT 400
#define BOARD_WIDTH 200
#define BOARD_OFFSET 60

/* Shape */
#define SHAPES_ARRAY_LENGTH 50
#define SHAPES_SIZE 20

/* Window */
#define WIDTH 640
#define HEIGHT 480
#define FPS 60
#define DELAY_TIME 1000.0f / FPS
#define TITLE "Tetris Game"

/* type fowarding */
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Window SDL_Window;
typedef union SDL_Event SDL_Event;
typedef struct SDL_Rect SDL_Rect;
typedef struct SDL_KeyboardEvent SDL_KeyboardEvent;
typedef struct Shape Shape;
typedef struct Color Color;
typedef struct BoardRow BoardRow;
typedef struct BoardCol BoardCol;
typedef uint64_t Uint64;

#endif