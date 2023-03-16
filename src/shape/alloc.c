#include "shape.h"
#include "../util/util.h"
#include "SDL.h"

/* Alloc shapes on the board */
Shape **GAME_AllocShapes() {
    Shape **s = calloc(SHAPES_ARRAY_LENGTH, sizeof(Shape *));
    if (s == NULL) {
        GAME_LogError("Cannot Alloc Shapes");
        exit(-1);
    }
    return s;
}

/* Free shape rects and shape */
void GAME_FreeShape(Shape *shape) {
    if (shape != NULL) {
        if (shape->r1 != NULL)
            free(shape->r1);
        if (shape->r2 != NULL)
            free(shape->r2);
        if (shape->r3 != NULL)
            free(shape->r3);
        if (shape->r4 != NULL)
            free(shape->r4);
        free(shape);
    }
}

/* Create from width x height and x, y rect */
SDL_Rect *GAME_CreateRect(int x, int y) {
    SDL_Rect *r = malloc(sizeof(SDL_Rect));
    r->x = x+BOARD_OFFSET+1; /* do not overlap pixel board */
    r->y = y+1; /* do not overlap pixel border */
    r->w = 20;
    r->h = 20;
    return r;
}

/* free all the shapes on the board */
void GAME_FreeManyShapes() {
    if (shapes != NULL) {
        for (int i = 0; i < SHAPES_ARRAY_LENGTH; i++) {
            if (shapes[i] != NULL) {
                if (shapes[i]->type != 0)
                    GAME_FreeShape(shapes[i]);
            }
        }
        free(shapes);
    }
}