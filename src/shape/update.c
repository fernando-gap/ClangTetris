#include "shape.h"
#include "SDL.h"

void GAME_UpdateRect(SDL_Rect *rect, int x, int y) {
    rect->x = x;
    rect->y = y;
}

void GAME_UpdateXPosition(Shape *shape, int left, int right) {
    if (shape != NULL) {
        if (left) {
            shape->r1->x -= 20;
            shape->r2->x -= 20;
            shape->r3->x -= 20;
            shape->r4->x -= 20;
        }

        if (right) {
            shape->r1->x += 20;
            shape->r2->x += 20;
            shape->r3->x += 20;
            shape->r4->x += 20;
        }
    }
}

void GAME_UpdateYPosition(Shape *shape, int top, int bottom) {
    if (shape != NULL) {
        if (top) {
            if(shape->r1 != NULL) shape->r1->y -= 20;
            if(shape->r2 != NULL) shape->r2->y -= 20;
            if(shape->r3 != NULL) shape->r3->y -= 20;
            if(shape->r4 != NULL) shape->r4->y -= 20;
        }

        if (bottom) {
            if(shape->r1 != NULL) shape->r1->y += 20;
            if(shape->r2 != NULL) shape->r2->y += 20;
            if(shape->r3 != NULL) shape->r3->y += 20;
            if(shape->r4 != NULL) shape->r4->y += 20;
        }
    }
}

void GAME_UpdateManyYRect(int times, SDL_Rect *r) {
    for (int i = 0; i < times; i++) {
        r->y += SHAPES_SIZE;
    }
}

/* When tetris occur it is needed to update all shapes' rect positions Y*/
void GAME_UpdateAfterTetris(int y, int times) {
    for (int i = 0; i < SHAPES_ARRAY_LENGTH; i++) {
        if (shapes[i] != NULL) {
            if (shapes[i]->r1 != NULL && shapes[i]->r1->y < y) {
                GAME_UpdateManyYRect(times, shapes[i]->r1);
            }
            if (shapes[i]->r2 != NULL && shapes[i]->r2->y < y) {
                GAME_UpdateManyYRect(times, shapes[i]->r2);
            }
            if (shapes[i]->r3 != NULL && shapes[i]->r3->y < y) {
                GAME_UpdateManyYRect(times, shapes[i]->r3);
            }
            if (shapes[i]->r4 != NULL && shapes[i]->r4->y < y) {
                GAME_UpdateManyYRect(times, shapes[i]->r4);
            }
        }
    }
}