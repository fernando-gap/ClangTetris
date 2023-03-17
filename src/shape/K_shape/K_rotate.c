#include "../shape.h"
#include "../../board/board.h"
#include "../../util/util.h"
#include "SDL.h"

/* from top (|-) to right ("|") */
void GAME_Top_K(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x-20, shape->r1->y-20);
    GAME_UpdateRect(shape->r2, shape->r2->x, shape->r2->y+40);
    shape->rotate = ROTATE_RIGHT;
}

/* from right ("|") to bottom (-|) */
void GAME_Right_K(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x+20, shape->r1->y-20);
    GAME_UpdateRect(shape->r4, shape->r4->x-40, shape->r4->y);
    shape->rotate = ROTATE_BOTTOM;
}

/* from bottom (-|) to left (_I_) */
void GAME_Bottom_K(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x-20, shape->r1->y+20);
    GAME_UpdateRect(shape->r2, shape->r2->x, shape->r2->y-40);
    GAME_UpdateRect(shape->r4, shape->r4->x+40, shape->r4->y);
    shape->rotate = ROTATE_LEFT;
}

/* from left (_I_) to top (|-) */
void GAME_Left_K(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x+20, shape->r1->y+20);
    shape->rotate = ROTATE_TOP;
}

void GAME_RotateTop_K(Shape *shape) {
    if (shape == NULL) return;
    GAME_Top_K(shape);
    GAME_MoveShapeOut_K(shape);
}

void GAME_RotateRight_K(Shape *shape) {
    if (shape == NULL) return;
    GAME_Right_K(shape);
    GAME_MoveShapeOut_K(shape);
}

void GAME_RotateBottom_K(Shape *shape) {
    if (shape == NULL) return;
    GAME_Bottom_K(shape);
    GAME_MoveShapeOut_K(shape);
}

void GAME_RotateLeft_K(Shape *shape) {
    if (shape == NULL) return;
    GAME_Left_K(shape);
    GAME_MoveShapeOut_K(shape);
}

/* Rotate shape to the next direction */
void GAME_RotateShape_K(Shape *shape) {
    switch (shape->rotate) {
        case ROTATE_LEFT:
            if (GAME_RotationSpaceY(shape, 4)) {
                GAME_RotateLeft_K(shape);
            }
            break;
        case ROTATE_TOP:
            if (GAME_RotationSpaceX(shape, 4)) {
                GAME_RotateTop_K(shape);
            }
            break;
        case ROTATE_RIGHT:
            if (GAME_RotationSpaceY(shape, 4)) {
                GAME_RotateRight_K(shape);
            }
            break;
        case ROTATE_BOTTOM:
            if (GAME_RotationSpaceX(shape, 4)) {
                GAME_RotateBottom_K(shape);
            }
            break;
        default:
            return;
    }
}