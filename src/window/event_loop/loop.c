#include "loop.h"
#include "../window.h"
#include "../../board/board.h"
#include "../../shape/shape.h"
#include "../../util/util.h"
#include "controller/controller.h"
#include "SDL.h"

SDL_Event event;
int running = 1;

void GAME_EventLoop() {
    shapes = GAME_AllocShapes();
    GAME_AllocBoard();
    while (running) {
        Uint64 frameStart = SDL_GetTicks64();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    GAME_ControllerKey(&event.key);
                    break;
                case SDL_KEYUP:
                    SHAPE_DELAY = 500;
                    break;
            }
        }

        if (currentSelect == NULL) {
            currentSelect = GAME_CreateRandomShape();
        }

        GAME_UpdateTetrisRender(frameStart);
        Uint64 frameDuration = SDL_GetTicks64() - frameStart;

        if (frameDuration < DELAY_TIME) {
            SDL_Delay(DELAY_TIME - frameDuration);
        }
    }
}


void GAME_UpdateTetrisRender(Uint64 frameStart) {
    GAME_Board();
    GAME_RenderBoardShapes();

    if (GAME_UpdateCurrentShape(currentSelect, frameStart)) {
        if (GAME_GameOver(currentSelect)) {
            currentSelect = NULL;
            return;
        }

        GAME_AddShapeBorder(currentSelect);
        currentSelect = NULL;

        BoardRow *tetrisFirst;
        BoardRow *tetrisLast;
        int tetrisTotal = GAME_CheckForTetris(&tetrisFirst, &tetrisLast);

        if (tetrisTotal > 0) {
            printf("Tetris: %d\n", tetrisTotal);
            GAME_UpdateAfterTetris(tetrisFirst->y, tetrisTotal);
            GAME_AddShapeToRect();
        }
    }

    SDL_RenderPresent(GAME_Win.renderer);
}


int GAME_UpdateCurrentShape(Shape *shape, Uint64 frameStart) {
    /* Checks if the current shape touches the ground*/
    if (shape != NULL)
        GAME_RenderShape(shape);
        if (GAME_DelayShapeVelocity(frameStart)) {
            if (GAME_DetectBoardCollision(shape, BOTTOM_EDGE)) {
                return 1;
            }
            if (GAME_DetectBoardShapeCollision(shape, BOTTOM_EDGE)) {
                return 1;
            }

            /* move shape */
            GAME_UpdateYPosition(shape, 0, 1);
        }
    return 0;
}


void GAME_AddShapeBorder(Shape *shape) {
    if (shape != NULL) {
        for (int i = 0; i < SHAPES_ARRAY_LENGTH; i++) {
            if (shapes[i] != NULL && GAME_IsEmptyShape(shapes[i])) {
                GAME_FreeShape(shapes[i]);
                shapes[i] = NULL;
                continue;
            }

            if (shapes[i] == NULL) {
                shapes[i] = malloc(sizeof(Shape));
                memcpy(shapes[i], shape, sizeof(*shape));
                GAME_AddShapeRectsToBoard(shapes[i]);
                return;
            }
        }
    }
}

void GAME_AddShapeToRect() {
    BoardRow *boardRow = shapeRects;
    /* erase shapeRects data structure */
    while (boardRow != NULL) {
        if (boardRow->col != NULL) {
            for (int i = 0; i < 10; i++) {
                boardRow->col[i].rect = NULL;
            }
        }
        boardRow = boardRow->nextRow;
    }

    /* populate again with the new shapes[i] rects positions caused by tetris */
    for (int i = 0; i < SHAPES_ARRAY_LENGTH; i++) {
        if (shapes[i] != NULL && !GAME_IsEmptyShape(shapes[i])) {
            GAME_AddShapeRectsToBoard(shapes[i]);
        }
    }
}