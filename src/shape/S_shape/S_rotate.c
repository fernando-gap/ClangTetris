#include "../shape.h"
#include "../../board/board.h"
#include "../../util/util.h"
#include "SDL.h"

/* from top (Y) to right (S) */
void GAME_Top_S(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x-40, shape->r1->y);
    GAME_UpdateRect(shape->r2, shape->r2->x, shape->r2->y+40);
    shape->rotate = ROTATE_RIGHT;
}

/* from right (S) to bottom (Y) */
void GAME_Right_S(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x, shape->r1->y-40);
    GAME_UpdateRect(shape->r2, shape->r2->x-20, shape->r2->y-20);
    GAME_UpdateRect(shape->r4, shape->r4->x-20, shape->r4->y+20);
    shape->rotate = ROTATE_BOTTOM;
}

/* from bottom (Y) to left (S) */
void GAME_Bottom_S(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x, shape->r1->y+40);
    GAME_UpdateRect(shape->r2, shape->r2->x+20, shape->r2->y+20);
    GAME_UpdateRect(shape->r4, shape->r4->x+20, shape->r4->y-20);
    shape->rotate = ROTATE_LEFT;
}

/* from left (S) to top (Y) */
void GAME_Left_S(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x+40, shape->r1->y);
    GAME_UpdateRect(shape->r2, shape->r2->x, shape->r2->y-40);
    shape->rotate = ROTATE_TOP;
}

void GAME_RotateTop_S(Shape *shape) {
    if (shape == NULL) return;
    GAME_Top_S(shape);
    GAME_MoveShapeOut_S(shape);
}

void GAME_RotateRight_S(Shape *shape) {
    if (shape == NULL) return;
    GAME_Right_S(shape);
    GAME_MoveShapeOut_S(shape);
}

void GAME_RotateBottom_S(Shape *shape) {
    if (shape == NULL) return;
    GAME_Bottom_S(shape);
    GAME_MoveShapeOut_S(shape);
}

void GAME_RotateLeft_S(Shape *shape) {
    if (shape == NULL) return;
    GAME_Left_S(shape);
    GAME_MoveShapeOut_S(shape);
}

/* Rotate shape to the next direction */
void GAME_RotateShape_S(Shape *shape) {
    switch (shape->rotate) {
        case ROTATE_LEFT:
            if (GAME_RotationSpaceY(shape, 4)) {
                GAME_RotateLeft_S(shape);
            }
            break;
        case ROTATE_TOP:
            if (GAME_RotationSpaceX(shape, 4)) {
                GAME_RotateTop_S(shape);
            }
            break;
        case ROTATE_RIGHT:
            if (GAME_RotationSpaceY(shape, 4)) {
                GAME_RotateRight_S(shape);
            }
            break;
        case ROTATE_BOTTOM:
            if (GAME_RotationSpaceX(shape, 4)) {
                GAME_RotateBottom_S(shape);
            }
            break;
        default:
            return;
    }
}



/**********************/
/* Reverse S Rotation */
/**********************/




/* from top (Y) to right (S) */
void GAME_Top_RS(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x-40, shape->r1->y+20);
    GAME_UpdateRect(shape->r4, shape->r4->x, shape->r4->y+20);
    shape->rotate = ROTATE_RIGHT;
}

/* from right (S) to bottom (Y) */
void GAME_Right_RS(Shape *shape) {
    GAME_UpdateRect(shape->r2, shape->r2->x, shape->r2->y-40);
    GAME_UpdateRect(shape->r4, shape->r4->x-40, shape->r4->y);
    shape->rotate = ROTATE_BOTTOM;
}

/* from bottom (S) to left (Y) */
void GAME_Bottom_RS(Shape *shape) {
    GAME_UpdateRect(shape->r2, shape->r2->x, shape->r2->y+40);
    GAME_UpdateRect(shape->r4, shape->r4->x+40, shape->r4->y);
    shape->rotate = ROTATE_LEFT;
}

/* from left (S) to top (Y) */
void GAME_Left_RS(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x+40, shape->r1->y-20);
    GAME_UpdateRect(shape->r4, shape->r4->x, shape->r4->y-20);
    shape->rotate = ROTATE_TOP;
}

void GAME_RotateTop_RS(Shape *shape) {
    if (shape == NULL) return;
    GAME_Top_RS(shape);
    GAME_MoveShapeOut_S(shape);
}

void GAME_RotateRight_RS(Shape *shape) {
    if (shape == NULL) return;
    GAME_Right_RS(shape);
    GAME_MoveShapeOut_S(shape);
}

void GAME_RotateBottom_RS(Shape *shape) {
    if (shape == NULL) return;
    GAME_Bottom_RS(shape);
    GAME_MoveShapeOut_S(shape);
}

void GAME_RotateLeft_RS(Shape *shape) {
    if (shape == NULL) return;
    GAME_Left_RS(shape);
    GAME_MoveShapeOut_S(shape);
}

/* Rotate shape to the next direction */
void GAME_RotateShape_RS(Shape *shape) {
    switch (shape->rotate) {
        case ROTATE_LEFT:
            if (GAME_RotationSpaceY(shape, 4)) {
                GAME_RotateLeft_RS(shape);
            }
            break;
        case ROTATE_TOP:
            if (GAME_RotationSpaceX(shape, 4)) {
                GAME_RotateTop_RS(shape);
            }
            break;
        case ROTATE_RIGHT:
            if (GAME_RotationSpaceY(shape, 4)) {
                GAME_RotateRight_RS(shape);
            }
            break;
        case ROTATE_BOTTOM:
            if (GAME_RotationSpaceX(shape, 4)) {
                GAME_RotateBottom_RS(shape);
            }
            break;
        default:
            return;
    }
}
