#include "board.h"
#include "SDL.h"

#include "../window/window.h"
#include "../window/event_loop/loop.h"
#include "../shape/enums.h"
#include "../shape/shape.h"
#include "../color/color.h"
#include "../util/util.h"

SDL_Rect borderRect = {BOARD_OFFSET+1, 0, BOARD_WIDTH, BOARD_HEIGHT+1};

void GAME_Board() {
    GAME_SetColor(BACKGROUND);
    GAME_Clear();
    GAME_SetColor(FOREGROUND);
    GAME_DrawLine(BOARD_OFFSET, 0, BOARD_OFFSET, BOARD_HEIGHT);
    GAME_DrawLine(BOARD_WIDTH+BOARD_OFFSET, 0, BOARD_WIDTH+BOARD_OFFSET, BOARD_HEIGHT);
    GAME_DrawLine(BOARD_OFFSET, BOARD_HEIGHT, BOARD_WIDTH+BOARD_OFFSET, BOARD_HEIGHT);
    GAME_DrawLine(BOARD_OFFSET, 0, BOARD_WIDTH+BOARD_OFFSET, 0);
}

RectangleSides GAME_CheckBorderCollision(SDL_Rect *a, SDL_Rect *b) {
    if (a != NULL && b != NULL) {
        if (a->y + a->h == b->y + b->h) {
            return BOTTOM_EDGE;
        }
        if (a->x == b->x) {
            return LEFT_EDGE;
        }
        if (a->x + a->w == b->x + b->w) {
            return RIGHT_EDGE;
        }
        return -1;
    }
    return -2;
}

int GAME_DetectBoardCollision(Shape *shape, RectangleSides side) {
    if (shape == NULL) {
        return 0;
    }
    if (GAME_CheckBorderCollision(shape->r1, &borderRect) == side) {
        return 1;
    }
    if (GAME_CheckBorderCollision(shape->r2, &borderRect) == side) {
        return 1;
    }
    if (GAME_CheckBorderCollision(shape->r3, &borderRect) == side) {
        return 1;
    }
    if (GAME_CheckBorderCollision(shape->r4, &borderRect) == side) {
        return 1;
    }
    return 0;
}

void GAME_AllocBoard() {
    shapeRects = calloc(1, sizeof(BoardRow));
    BoardRow *tmpShapeRects = shapeRects;

    for (int row = borderRect.y+1; row < borderRect.h; row+=SHAPES_SIZE) {
        tmpShapeRects->y = row;
        tmpShapeRects->col = calloc(10, sizeof(BoardCol));
        tmpShapeRects->nextRow = calloc(1, sizeof(BoardRow));

        if (tmpShapeRects->col == NULL || tmpShapeRects->nextRow == NULL) {
            GAME_LogError("Cannot Alloc Memory for Board");
            exit(-1);
            break;
        }

        for (int col = borderRect.x, i = 0; col < borderRect.w+borderRect.x; col+=SHAPES_SIZE, i++) {
            tmpShapeRects->col[i].x = col;
        }
        tmpShapeRects = tmpShapeRects->nextRow;
    }
    tmpShapeRects = NULL;
}

void GAME_FreeBoard() {
    BoardRow *tmpShapeRects = shapeRects;
    int j = 0;
    while (tmpShapeRects != NULL) {
        if (tmpShapeRects->col != NULL)
            free(tmpShapeRects->col);

        BoardRow *tmp = tmpShapeRects;
        tmpShapeRects = tmpShapeRects->nextRow;
        free(tmp);
    }
}

BoardCol *GAME_FindBoardCol(BoardRow *boardRow, int x) {
    for (int i = 0; i < 10; i++) {
        if (boardRow->col[i].x == x) {
            return &boardRow->col[i];
        }
    }
    return NULL;
}

BoardRow *GAME_FindBoardRow(int y) {
    BoardRow *tmpShapeRects = shapeRects;

    while (tmpShapeRects != NULL) {
        if (tmpShapeRects->y == y) {
            return tmpShapeRects;
        }
        tmpShapeRects = tmpShapeRects->nextRow;
    }
    return NULL;
}

void GAME_AddShapeRectsToBoard(Shape *shape) {
    SDL_Rect **rects[] = {
        &shape->r1,
        &shape->r2,
        &shape->r3,
        &shape->r4,
    };


    for (int i = 0; i < 4; i++) {
        if (*rects[i] != NULL) {
            BoardRow *row = GAME_FindBoardRow((*rects[i])->y);
            if (row != NULL) {
                BoardCol *col = GAME_FindBoardCol(row, (*rects[i])->x);
                if (col != NULL) {
                    col->rect = rects[i];
                }
            }
        }
    }
}

int GAME_CheckForTetris(BoardRow **tetrisFirst, BoardRow **tetrisLast) {
    int totalTetris = 0, isFirstTetris = 0;

    for (int row = borderRect.y+1; row < borderRect.h; row+=SHAPES_SIZE) {
        BoardRow *boardRow = GAME_FindBoardRow(row);
        if (boardRow != NULL) {
            int counter = 0;
            for (int col = borderRect.x; col < borderRect.w+borderRect.x; col+=SHAPES_SIZE) {
                if (boardRow != NULL) {
                    BoardCol *boardCol = GAME_FindBoardCol(boardRow, col);
                    if (boardCol != NULL) {
                        if (boardCol->rect != NULL && *boardCol->rect != NULL) {
                            ++counter;
                        }
                    };
                }
            }
            if (counter == 10) {
                ++totalTetris;

                if (!isFirstTetris) {
                    isFirstTetris = 1;
                    *tetrisFirst = boardRow; /* highest tetris in the stack */
                }

                *tetrisLast = boardRow; /* lowest tetris in the stack */

                for (int i = 0; i < 10; i++) {
                    if (boardRow->col[i].rect != NULL) {
                        if (*(boardRow->col[i].rect) != NULL) {
                            free(*(boardRow->col[i].rect));
                            *(boardRow->col[i].rect) = NULL;
                            boardRow->col[i].rect = NULL;
                        }
                    }
                }
            }
        }
    }
    return totalTetris;
}