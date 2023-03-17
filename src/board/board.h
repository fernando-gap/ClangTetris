#ifndef SRC_BOARD_H
#define SRC_BOARD_H

#include "../macros.h"
#include "../shape/enums.h"

extern SDL_Rect borderRect;

typedef struct BoardCol {
    int x;
    SDL_Rect **rect;
} BoardCol;

typedef struct BoardRow {
    int y;
    BoardCol *col;
    BoardRow *nextRow;
} BoardRow;

void GAME_Board();
int GAME_DetectBoardCollision(Shape *, RectangleSides);
void GAME_AddShapeRectsToBoard(Shape *shape);
BoardRow *GAME_FindBoardRow(int y);
BoardCol *GAME_FindBoardCol(BoardRow *boardRow, int x);
RectangleSides GAME_CheckBorderCollision(SDL_Rect *a, SDL_Rect *b);
int GAME_CheckForTetris(BoardRow **firstTetris, BoardRow **lastTetris);

void GAME_FreeBoard();
void GAME_AllocBoard();
void GAME_ResetBoard();

#endif