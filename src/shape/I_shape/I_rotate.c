#include "../shape.h"
#include "../../board/board.h"
#include "../../util/util.h"
#include "SDL.h"

/* from top (|) to right (--) */
void GAME_Top_I(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x-40, shape->r1->y+40);
    GAME_UpdateRect(shape->r2, shape->r2->x-20, shape->r2->y+20);
    GAME_UpdateRect(shape->r4, shape->r4->x+20, shape->r4->y-20);
    shape->rotate = ROTATE_RIGHT;
}

/* from right (--) to bottom (|) */
void GAME_Right_I(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x+20, shape->r1->y-40);
    GAME_UpdateRect(shape->r2, shape->r2->x, shape->r2->y-20);
    GAME_UpdateRect(shape->r3, shape->r3->x-20, shape->r3->y);
    GAME_UpdateRect(shape->r4, shape->r4->x-40, shape->r4->y+20);
    shape->rotate = ROTATE_BOTTOM;
}

/* from bottom (|) to left (--) */
void GAME_Bottom_I(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x-20, shape->r1->y+40);
    GAME_UpdateRect(shape->r2, shape->r2->x, shape->r2->y+20);
    GAME_UpdateRect(shape->r3, shape->r3->x+20, shape->r3->y);
    GAME_UpdateRect(shape->r4, shape->r4->x+40, shape->r4->y-20);
    shape->rotate = ROTATE_LEFT;
}

/* from left (--) to top (|) */
void GAME_Left_I(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x+40, shape->r1->y-40);
    GAME_UpdateRect(shape->r2, shape->r2->x+20, shape->r2->y-20);
    GAME_UpdateRect(shape->r4, shape->r4->x-20, shape->r4->y+20);
    shape->rotate = ROTATE_TOP;
}

void GAME_RotateTop_I(Shape *shape) {
    if (shape == NULL) return;
    GAME_Top_I(shape);
    GAME_MoveShapeOut_I(shape);
}

void GAME_RotateRight_I(Shape *shape) {
    if (shape == NULL) return;
    GAME_Right_I(shape);
    GAME_MoveShapeOut_I(shape);
}

void GAME_RotateBottom_I(Shape *shape) {
    if (shape == NULL) return;
    GAME_Bottom_I(shape);
    GAME_MoveShapeOut_I(shape);
}

void GAME_RotateLeft_I(Shape *shape) {
    if (shape == NULL) return;
    GAME_Left_I(shape);
    GAME_MoveShapeOut_I(shape);
}

/* Rotate shape to the next direction */
void GAME_RotateShape_I(Shape *shape) {
    switch (shape->rotate) {
        case ROTATE_LEFT:
            if (GAME_RotationSpaceY(shape, 4)) {
                GAME_RotateLeft_I(shape);
            }
            break;
        case ROTATE_TOP:
            if (GAME_RotationSpaceX(shape, 4)) {
                GAME_RotateTop_I(shape);
            }
            break;
        case ROTATE_RIGHT:
            if (GAME_RotationSpaceY(shape, 4)) {
                GAME_RotateRight_I(shape);
            }
            break;
        case ROTATE_BOTTOM:
            if (GAME_RotationSpaceX(shape, 4)) {
                GAME_RotateBottom_I(shape);
            }
            break;
        default:
            return;
    }
}