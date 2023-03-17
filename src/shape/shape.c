#include "shape.h"
#include "../window/event_loop/loop.h"
#include "../color/color.h"
#include "../board/board.h"
#include "../util/util.h"
#include "SDL.h"

/* All Shapes are stored here */
Shape **shapes;

/* Current Shape Created. */
Shape *currentSelect = NULL;

/*
When a shape touches the board it is not a shape anymore, instead is a collection of rects.
This variable will be used for two purposes
    (1) check if the current selected can be rotated
    (2) check if a tetris occurs, then remove the rects from the board
*/
BoardRow *shapeRects;

/* Last frame for delay */
Uint64 lastFrame = 0;

int SHAPE_DELAY = 500;


void GAME_RotateShape(Shape *shape) {
    switch (shape->type) {
        case SHAPE_I:
            GAME_RotateShape_I(shape);
            break;
        case SHAPE_S:
            GAME_RotateShape_S(shape);
            break;
        case SHAPE_REVERSE_S:
            GAME_RotateShape_RS(shape);
            break;
        case SHAPE_L:
            GAME_RotateShape_L(shape);
            break;
        case SHAPE_REVERSE_L:
            GAME_RotateShape_RL(shape);
            break;
        case SHAPE_K:
            GAME_RotateShape_K(shape);
            break;
    }
}

int GAME_DelayShapeVelocity(Uint64 frameStart) {
    if (lastFrame == 0) {
        lastFrame = frameStart + SHAPE_DELAY;
    } else {
        if (frameStart >= lastFrame) {
            lastFrame = 0;
            return 1;
        }
    }
    return 0;
}

void GAME_MoveShapeOutsideBorder(Shape *shape, RectangleSides side, SDL_Rect *rect) {
    if (side == RIGHT_EDGE) {
        if (shape->r1->x < rect->x ||
            shape->r2->x < rect->x ||
            shape->r3->x < rect->x ||
            shape->r4->x < rect->x) {
                GAME_UpdateXPosition(shape, 0, 1);
        }
    } else if (side == LEFT_EDGE) {
        if (shape->r1->x+shape->r1->w > rect->w+rect->x ||
            shape->r2->x+shape->r2->w > rect->w+rect->x ||
            shape->r3->x+shape->r3->w > rect->w+rect->x ||
            shape->r4->x+shape->r4->w > rect->w+rect->x) {
                GAME_UpdateXPosition(shape, 1, 0);
        }
    } else if (side == BOTTOM_EDGE) {
        if (shape->r1->y+shape->r1->w > rect->h+rect->y ||
            shape->r2->y+shape->r2->w > rect->h+rect->y ||
            shape->r3->y+shape->r3->w > rect->h+rect->y ||
            shape->r4->y+shape->r4->w > rect->h+rect->y) {
                GAME_UpdateYPosition(shape, 1, 0);
        }
    }
}

int GAME_GameOver(Shape *shape) {
    if (shape == NULL) return 0;
    /* TODO: better check when the game is over*/
    if (shape->r1->y <= 1 &&
        shape->r2->y <= 1 &&
        shape->r3->y <= 1 &&
        shape->r4->y <= 1) {

        if (shapes != NULL) {
            for (int i = 0; i < SHAPES_ARRAY_LENGTH; i++) {
                if (shapes[i] != NULL) {
                    GAME_FreeShape(shapes[i]);
                    shapes[i] = NULL;
                }
            }
        }
        GAME_FreeShape(shape);
        GAME_ResetBoard();
        return 1;
    }
    return 0;
}

int GAME_ValidateRotationX(SDL_Rect *leftmost, SDL_Rect *rightmost, int shapeHeight) {
    if (leftmost != NULL && rightmost != NULL) {
        int diffShapes = (rightmost->x - (leftmost->x + SHAPES_SIZE)) / SHAPES_SIZE;
        if (diffShapes < shapeHeight) {
            return 1;
        }
    }
    return 0;
}

int GAME_ValidateRotationY(SDL_Rect *topMost, SDL_Rect *bottomMost, int shapeWidth) {
    if (topMost != NULL && bottomMost != NULL) {
        int diffShapes = (bottomMost->y - (topMost->y + SHAPES_SIZE)) / SHAPES_SIZE;
        if (diffShapes < shapeWidth) {
            return 1;
        }
    }
    return 0;
}


/* This function is executed before shapes' rotation. From least width to the most width */
int GAME_RotationSpaceX(Shape *shape, int shapeHeight) {
    /*
     * TODO: there is a bug with shape->r3->y, it only check on the r3 and not other r's
     * That causes the shape to rotate in the situation where it has only one space to rotate,
     * it is needed to check the rotation to the right and/or left of the higher/lower rects.
     */

    int minX = GAME_GetMinShapeX(shape);
    SDL_Rect *leftmost = NULL, *rightmost = NULL;

    GAME_RotationSpaceSideX(&leftmost, &rightmost, shape->r3->y, minX);

    if (leftmost == NULL && rightmost == NULL) return 1;

    /* borderRect only contains the leftmost coordinates */
    SDL_Rect border = {borderRect.w+borderRect.x, 0, 0, 0};

    if (GAME_ValidateRotationX(leftmost, &border, shapeHeight)) return 0;
    if (GAME_ValidateRotationX(&borderRect, rightmost, shapeHeight)) return 0;
    if (GAME_ValidateRotationX(leftmost, rightmost, shapeHeight)) return 0;

    return 1;
}


void GAME_RotationSpaceSideX(SDL_Rect **leftmost, SDL_Rect **rightmost, int y, int x) {
    BoardRow *boardRow = GAME_FindBoardRow(y);

    for (int i = x-20; i >= borderRect.x; i-=20) {
        BoardCol *boardCol = GAME_FindBoardCol(boardRow, i);
        if (boardCol->rect != NULL) {
            *leftmost = *boardCol->rect;
            break;
        }
    }

    for (int i = x+20; i < borderRect.x+borderRect.w; i+=20) {
        BoardCol *boardCol = GAME_FindBoardCol(boardRow, i);
        if (boardCol->rect != NULL) {
            *rightmost = *boardCol->rect;
            break;
        }
    }
}

void GAME_RotationSpaceSideY(SDL_Rect **topmost, SDL_Rect **bottommost, int y, int x) {

    for (int i = y-20; i >= borderRect.y; i-=20) {
        BoardRow *boardRow = GAME_FindBoardRow(i);
        BoardCol *boardCol = GAME_FindBoardCol(boardRow, x);

        if (boardCol->rect != NULL) {
            *topmost = *boardCol->rect;
            break;
        }
    }

    for (int i = y+20; i < borderRect.h; i+=20) {
        BoardRow *boardRow = GAME_FindBoardRow(i);
        BoardCol *boardCol = GAME_FindBoardCol(boardRow, x);

        if (boardCol->rect != NULL) {
            *bottommost = *boardCol->rect;
            break;
        }
    }
}

/* This function is executed before shapes' rotation. From least height to the most height */
int GAME_RotationSpaceY(Shape *shape, int shapeWidth) {
    /*
     * TODO: there is a bug with shape->r3->y, it only check on the r3 and not other r's
     * That causes the shape to rotate in the situation where it has only one space to rotate,
     * it is needed to check the rotation to the right and/or left of the higher/lower rects.
     */

    int minX = GAME_GetMinShapeX(shape);
    int maxX = GAME_GetMaxShapeX(shape);
    int minY = GAME_GetMinShapeY(shape);

    SDL_Rect *topMostMin = NULL, *bottomMostMin = NULL;
    SDL_Rect *topMostMax = NULL, *bottomMostMax = NULL;

    GAME_RotationSpaceSideY(&topMostMin, &bottomMostMin, minY, minX);
    GAME_RotationSpaceSideY(&topMostMax, &bottomMostMax, minY, maxX);

    if (GAME_ValidateRotationY(topMostMin, bottomMostMin, shapeWidth)) return 0;
    if (GAME_ValidateRotationY(topMostMax, bottomMostMax, shapeWidth)) return 0;

    return 1;
}


Shape *GAME_CreateRandomShape() {
    Shape *(*shapeFunctions[])() = {
        GAME_CreateShape_I,
        GAME_CreateShape_K,
        GAME_CreateShape_L,
        GAME_CreateShape_RL,
        GAME_CreateShape_S,
        GAME_CreateShape_RS,
        GAME_CreateShape_O
    };
    int randomNum = rand() % 7;
    return (*shapeFunctions[randomNum])();
}

int GAME_IsEmptyShape(Shape *shape) {
    return shape->r1 == NULL && shape->r2 == NULL && shape->r3 == NULL && shape->r4 == NULL;
}

int GAME_GetMinShapeX(Shape *shape) {
    int minX = min(shape->r1->x, shape->r2->x);
    minX = min(minX, shape->r3->x);
    minX = min(minX, shape->r4->x);
    return minX;
}

int GAME_GetMaxShapeX(Shape *shape) {
    int maxX = max(shape->r1->x, shape->r2->x);
    maxX = max(maxX, shape->r3->x);
    maxX = max(maxX, shape->r4->x);
    return maxX;
}

int GAME_GetMinShapeY(Shape *shape) {
    int minY = min(shape->r1->y, shape->r2->y);
    minY = min(minY, shape->r3->y);
    minY = min(minY, shape->r4->y);
    return minY;
}