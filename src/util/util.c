#include "../shape/shape.h"
#include "../util/util.h"
#include "SDL.h"

void GAME_LogError(char *func) {
    printf("ERROR: %s -- %s\n", func, SDL_GetError());
}

void GAME_LogInfo(char *func) {
    printf("INFO: %s\n", func);
}

void GAME_DebugShape(Shape *shape, char *name) {
    printf("-------- SHAPE: %s --------\n", name);
    printf("R%d -- x, y = (%d, %d)\n", 1, shape->r1->x, shape->r1->y);
    printf("R%d -- x, y = (%d, %d)\n", 2, shape->r2->x, shape->r2->y);
    printf("R%d -- x, y = (%d, %d)\n", 3, shape->r3->x, shape->r3->y);
    printf("R%d -- x, y = (%d, %d)\n", 4, shape->r4->x, shape->r4->y);
    printf("\n");
}

void GAME_DebugRect(SDL_Rect *rect, char *name) {
    printf("-------- SDL_RECT: %s --------\n", name);
    printf("(x, y) = (%d, %d)\n", rect->x, rect->y);
    printf("(w, h) = (%d, %d)\n", rect->w, rect->h);
    printf("\n");
}

void GAME_DebugArray(int *array, int size, char *name) {
    printf("--------- ARRAY: %s ---------\n", name);
    for (int i = 0; i < size; i++) {
        printf("Element[%d]: %d\n", i, array[i]);
    }
    printf("\n");
}

int GAME_DetectCollision(SDL_Rect *a, SDL_Rect *b) {
    if (a != NULL && b != NULL) {
        if (a->x + a->w >= b->x &&    // right edge of A is to the right of left edge of B
            a->x <= b->x + b->w &&    // left edge of A is to the left of right edge of B
            a->y + a->h >= b->y &&    // bottom edge of A is below top edge of B
            a->y <= b->y + b->h) {    // top edge of A is above bottom edge of B
            return 1;
        }
    }
    return 0;
}

RectangleSides GAME_DetectSideCollision(SDL_Rect *a, SDL_Rect *b) {
    if (a != NULL && b != NULL) {
        if (a->y + a->h == b->y && a->x == b->x) {
            return BOTTOM_EDGE;
        } else if (a->x + a->w == b->x && a->y == b->y) {
            return LEFT_EDGE;
        } else if (a->x == b->x + b->w && a->y == b->y) {
            return RIGHT_EDGE;
        }
        return -1;
    }
    return -2;
}