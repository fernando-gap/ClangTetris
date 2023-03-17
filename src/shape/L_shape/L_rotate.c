#include "../shape.h"
#include "../../board/board.h"
#include "../../util/util.h"
#include "SDL.h"

/* from top (Y) to right (S) */
void GAME_Top_L(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x-20, shape->r1->y+20);
    GAME_UpdateRect(shape->r2, shape->r2->x-20, shape->r2->y);
    GAME_UpdateRect(shape->r4, shape->r4->x, shape->r4->y-20);
    shape->rotate = ROTATE_RIGHT;
}

/* from right (|"") to bottom ("|) */
void GAME_Right_L(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x, shape->r1->y-20);
    GAME_UpdateRect(shape->r2, shape->r2->x+20, shape->r2->y);
    GAME_UpdateRect(shape->r4, shape->r4->x-20, shape->r4->y-20);
    shape->rotate = ROTATE_BOTTOM;
}

/* from bottom ("|) to left (__I) */
void GAME_Bottom_L(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x, shape->r1->y+20);
    GAME_UpdateRect(shape->r2, shape->r2->x+20, shape->r2->y-20);
    GAME_UpdateRect(shape->r4, shape->r4->x+20, shape->r4->y);
    shape->rotate = ROTATE_LEFT;
}

/* from left (__I) to top (|_) */
void GAME_Left_L(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x+20, shape->r1->y-20);
    GAME_UpdateRect(shape->r2, shape->r2->x-20, shape->r2->y+20);
    GAME_UpdateRect(shape->r4, shape->r4->x, shape->r4->y+40);
    shape->rotate = ROTATE_TOP;
}

void GAME_RotateTop_L(Shape *shape) {
    if (shape == NULL) return;
    GAME_Top_L(shape);
    GAME_MoveShapeOut_L(shape);
}

void GAME_RotateRight_L(Shape *shape) {
    if (shape == NULL) return;
    GAME_Right_L(shape);
    GAME_MoveShapeOut_L(shape);
}

void GAME_RotateBottom_L(Shape *shape) {
    if (shape == NULL) return;
    GAME_Bottom_L(shape);
    GAME_MoveShapeOut_L(shape);
}

void GAME_RotateLeft_L(Shape *shape) {
    if (shape == NULL) return;
    GAME_Left_L(shape);
    GAME_MoveShapeOut_L(shape);
}

/* Rotate shape to the next direction */
void GAME_RotateShape_L(Shape *shape) {
    switch (shape->rotate) {
        case ROTATE_LEFT:
            if (GAME_RotationSpaceY(shape, 4)) {
                GAME_RotateLeft_L(shape);
            }
            break;
        case ROTATE_TOP:
            if (GAME_RotationSpaceX(shape, 4)) {
                GAME_RotateTop_L(shape);
            }
            break;
        case ROTATE_RIGHT:
            if (GAME_RotationSpaceY(shape, 4)) {
                GAME_RotateRight_L(shape);
            }
            break;
        case ROTATE_BOTTOM:
            if (GAME_RotationSpaceX(shape, 4)) {
                GAME_RotateBottom_L(shape);
            }
            break;
        default:
            return;
    }
}




/**********************/
/* Reverse L Rotation */
/**********************/




/* from top (|") to right (""|) */
void GAME_Top_RL(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x, shape->r1->y+40);
    GAME_UpdateRect(shape->r2, shape->r2->x+20, shape->r2->y+20);
    GAME_UpdateRect(shape->r4, shape->r4->x-20, shape->r4->y-20);
    shape->rotate = ROTATE_RIGHT;
}

/* from right (""|) to bottom (_|) */
void GAME_Right_RL(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x-40, shape->r1->y);
    GAME_UpdateRect(shape->r2, shape->r2->x-20, shape->r2->y+20);
    GAME_UpdateRect(shape->r4, shape->r4->x+20, shape->r4->y-20);
    printf("hi");
    shape->rotate = ROTATE_BOTTOM;
}

/* from bottom (_|) to left (I__) */
void GAME_Bottom_RL(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x, shape->r1->y-40);
    GAME_UpdateRect(shape->r2, shape->r2->x-20, shape->r2->y-20);
    GAME_UpdateRect(shape->r4, shape->r4->x+20, shape->r4->y+20);
    shape->rotate = ROTATE_LEFT;
}

/* from left (I__) to top (|") */
void GAME_Left_RL(Shape *shape) {
    GAME_UpdateRect(shape->r1, shape->r1->x+40, shape->r1->y);
    GAME_UpdateRect(shape->r2, shape->r2->x+20, shape->r2->y-20);
    GAME_UpdateRect(shape->r4, shape->r4->x-20, shape->r4->y+20);
    shape->rotate = ROTATE_TOP;
}

void GAME_RotateTop_RL(Shape *shape) {
    if (shape == NULL) return;
    GAME_Top_RL(shape);
    GAME_MoveShapeOut_L(shape);
}

void GAME_RotateRight_RL(Shape *shape) {
    if (shape == NULL) return;
    GAME_Right_RL(shape);
    GAME_MoveShapeOut_L(shape);
}

void GAME_RotateBottom_RL(Shape *shape) {
    if (shape == NULL) return;
    GAME_Bottom_RL(shape);
    GAME_MoveShapeOut_L(shape);
}

void GAME_RotateLeft_RL(Shape *shape) {
    if (shape == NULL) return;
    GAME_Left_RL(shape);
    GAME_MoveShapeOut_L(shape);
}

/* Rotate shape to the next direction */
void GAME_RotateShape_RL(Shape *shape) {
    switch (shape->rotate) {
        case ROTATE_LEFT:
            if (GAME_RotationSpaceY(shape, 4)) {
                GAME_RotateLeft_RL(shape);
            }
            break;
        case ROTATE_TOP:
            if (GAME_RotationSpaceX(shape, 4)) {
                GAME_RotateTop_RL(shape);
            }
            break;
        case ROTATE_RIGHT:
            if (GAME_RotationSpaceY(shape, 4)) {
                GAME_RotateRight_RL(shape);
            }
            break;
        case ROTATE_BOTTOM:
            if (GAME_RotationSpaceX(shape, 4)) {
                GAME_RotateBottom_RL(shape);
            }
            break;
        default:
            return;
    }
}