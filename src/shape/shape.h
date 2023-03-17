#ifndef SRC_SHAPES_H
#define SRC_SHAPES_H

#include "../macros.h"
#include "./I_shape/I_shape.h"
#include "./L_shape/L_shape.h"
#include "./S_shape/S_shape.h"
#include "./O_shape/O_shape.h"
#include "./K_shape/K_shape.h"
#include "enums.h"

typedef struct Shape {
    ShapeTypes type;
    ShapeRotation rotate;
    Color *color;
    SDL_Rect *r1;
    SDL_Rect *r2;
    SDL_Rect *r3;
    SDL_Rect *r4;
} Shape;

extern Shape **shapes;
extern Shape *currentSelect;
extern BoardRow *shapeRects;
extern int SHAPE_DELAY;

 /*
 * These functions call malloc()
 * be sure to free them with
 * GAME_FreeShape and GAME_FreeManyShapes
 */

SDL_Rect *GAME_CreateRect(int x, int y);
Shape *GAME_CreateShape_O();
Shape **GAME_AllocShapes();
void GAME_FreeShape(Shape *);
void GAME_FreeManyShapes();

/* Rotate Any Shape */
void GAME_RotateShape(Shape *shape);


/* Create Any Shape Randomly */
Shape *GAME_CreateRandomShape();


int GAME_GameOver(Shape *shape);
int GAME_DelayShapeVelocity(Uint64 frameStart);
int GAME_DetectBoardShapeCollision(Shape *shape, RectangleSides where);


/*
 * If there is space to rotate to left or right exclusive,
 * then make sure that the rotation is not overlapping with other's shape
 */
void GAME_MoveShapeOutsideBorder(Shape *shape, RectangleSides side, SDL_Rect *rect);
void GAME_MoveShapeOutsideShape(Shape *shape);


/*
 * The difference between the two closest squares gives the space that can fit the shape
 * If the difference is greater or equal to the shapes' width or height, then it cannot be rotate
 * in tha specific Y.
 */
int GAME_RotationSpaceX(Shape *shape, int shapeHeight);
int GAME_RotationSpaceY(Shape *shape, int shapeWidth);

/* Update X and Y coordinates of a shape in the specified direction */
void GAME_UpdateYPosition(Shape *shape, int top, int bottom);
void GAME_UpdateXPosition(Shape *shape, int left, int right);
void GAME_UpdateRect(SDL_Rect *rect, int x, int y);

/* Get X or Y min and max */
int GAME_GetMinShapeX(Shape *shape);
int GAME_GetMaxShapeX(Shape *shape);
int GAME_GetMinShapeY(Shape *shape);

/* this function is only used once to update */
void GAME_UpdateAfterTetris(int y, int times);
void GAME_UpdateManyYRect(int times, SDL_Rect *r);
int GAME_IsEmptyShape(Shape *shape);

/* Find the closest squares between x and y */
void GAME_RotationSpaceSideX(SDL_Rect **leftmost, SDL_Rect **rightmost, int y, int x);
void GAME_RotationSpaceSideY(SDL_Rect **topmost, SDL_Rect **bottommost, int y, int x);

#endif