#ifndef SRC_WINDOW_EVENTLOOP_H
#define SRC_WINDOW_EVENTLOOP_H

#include "../../macros.h"

extern SDL_Event event;

void GAME_Clear();
void GAME_DrawLine(int x1, int y1, int x2, int y2);
void GAME_EventLoop();
void GAME_RenderBoardShapes();
void GAME_RenderRect(SDL_Rect *);
void GAME_RenderShape(Shape *);
int GAME_UpdateCurrentShape(Shape *shape, Uint64 frameStart);
void GAME_UpdateTetrisRender(Uint64 frameStart);
void GAME_AddShapeBorder(Shape *);
void GAME_AddShapeToRect();

#endif