#include "shape.h"
#include "../util/util.h"
#include "../board/board.h"
#include "SDL.h"

/* Detects if the current shape touches any other shape in the board */
int GAME_DetectSideShapeCollision(Shape *current, Shape *desired, RectangleSides where) {
    SDL_Rect *checkCurrent[] = {
        current->r1,
        current->r2,
        current->r3,
        current->r4
    };
    SDL_Rect *checkDesired[] = {
        desired->r1,
        desired->r2,
        desired->r3,
        desired->r4
    };


    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (checkDesired[j] != NULL) {
                if (GAME_DetectCollision(checkCurrent[i], checkDesired[j])) {
                    if (GAME_DetectSideCollision(checkCurrent[i], checkDesired[j]) == where)
                        return 1;
                }
            }
        }
    }
    return 0;
}

/* Detects if the current shape touches any other shape with the specified SIDE */
int GAME_DetectBoardShapeCollision(Shape *shape, RectangleSides where) {
    for (int i = 0; i < SHAPES_ARRAY_LENGTH; i++) {
        if (shapes[i] != NULL) {
            if (GAME_DetectSideShapeCollision(shape, shapes[i], where)) {
                return 1;
            }
        }
    }
    return 0;
}

/* TODO: try to reuse this function to other shapes as well*/
/* TODO: Move shape outside top */
void GAME_MoveShapeOutsideShape(Shape *shape) {
    BoardRow *boardRow = GAME_FindBoardRow(shape->r3->y);

    for (int i = 0; i < 10; i++) {
        if (boardRow->col[i].rect != NULL) {
            if ((*boardRow->col[i].rect)->x == shape->r1->x) {
                SDL_Rect boundBox = {
                    shape->r2->x+1, /* there is a bug with the pixel in the  board*/
                    shape->r2->y,
                    shape->r4->x+shape->r4->h-shape->r2->x,
                    shape->r2->y*2,
                };
                GAME_MoveShapeOutsideBorder(shape, RIGHT_EDGE, &boundBox);
            }
            if ((*boardRow->col[i].rect)->x == shape->r2->x) {
                SDL_Rect boundBox = {
                    shape->r2->x+1,
                    shape->r2->y,
                    shape->r4->x+shape->r4->h-shape->r2->x,
                    shape->r2->y*2,
                };
                GAME_MoveShapeOutsideBorder(shape, RIGHT_EDGE, &boundBox);
                GAME_MoveShapeOutsideBorder(shape, RIGHT_EDGE, &boundBox);
            }

            if ((*boardRow->col[i].rect)->x == shape->r3->x) {
                SDL_Rect boundBox = {
                    shape->r1->x,
                    shape->r1->y,
                    shape->r4->x-shape->r1->x,
                    shape->r1->y*2,
                };
                GAME_MoveShapeOutsideBorder(shape, LEFT_EDGE, &boundBox);
                GAME_MoveShapeOutsideBorder(shape, LEFT_EDGE, &boundBox);
            }

            if ((*boardRow->col[i].rect)->x == shape->r4->x) {
                SDL_Rect boundBox = {
                    shape->r1->x,
                    shape->r1->y,
                    shape->r4->x-shape->r1->x,
                    shape->r1->y*2,
                };
                GAME_MoveShapeOutsideBorder(shape, LEFT_EDGE, &boundBox);
                GAME_MoveShapeOutsideBorder(shape, LEFT_EDGE, &boundBox);
            }
        }
    }
}