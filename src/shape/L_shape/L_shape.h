#ifndef SRC_SHAPE_L_SHAPE_H
#define SRC_SHAPE_L_SHAPE_H

Shape *GAME_CreateShape_L();
Shape *GAME_CreateShape_RL(); /* RL: Reverse L */
void GAME_MoveShapeOut_L(Shape *shape);

void GAME_RotateTop_L(Shape *shape);
void GAME_RotateRight_L(Shape *shape);
void GAME_RotateBottom_L(Shape *shape);
void GAME_RotateRight_L(Shape *shape);
void GAME_RotateShape_L(Shape *shape);

void GAME_RotateTop_RL(Shape *shape);
void GAME_RotateRight_RL(Shape *shape);
void GAME_RotateBottom_RL(Shape *shape);
void GAME_RotateRight_RL(Shape *shape);
void GAME_RotateShape_RL(Shape *shape);

#endif