#ifndef SRC_UTIL
#define SRC_UTIL

#include "../macros.h"
#include "../shape/enums.h"

void GAME_LogError(char *);
void GAME_LogInfo(char *);
void GAME_DebugShape(Shape *, char*);
void GAME_DebugArray(int *array, int size, char *name);
void GAME_DebugRect(SDL_Rect *rect, char *name);
int GAME_DetectCollision(SDL_Rect *a, SDL_Rect *b);
RectangleSides GAME_DetectSideCollision(SDL_Rect *a, SDL_Rect *b);

#endif