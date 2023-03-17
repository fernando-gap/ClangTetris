#ifndef SRC_SHAPE_S_SHAPE_H
#define SRC_SHAPE_S_SHAPE_H

Shape *GAME_CreateShape_S();
Shape *GAME_CreateShape_RS(); /* RS: Reverse S */
void GAME_MoveShapeOut_S(Shape *shape);

void GAME_RotateTop_S(Shape *shape);
void GAME_RotateRight_S(Shape *shape);
void GAME_RotateBottom_S(Shape *shape);
void GAME_RotateRight_S(Shape *shape);
void GAME_RotateShape_S(Shape *shape);

void GAME_RotateTop_RS(Shape *shape);
void GAME_RotateRight_RS(Shape *shape);
void GAME_RotateBottom_RS(Shape *shape);
void GAME_RotateRight_RS(Shape *shape);
void GAME_RotateShape_RS(Shape *shape);

#endif