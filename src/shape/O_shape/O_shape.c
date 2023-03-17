#include "../shape.h"
#include "../../color/color.h"
#include "SDL.h"

Shape *GAME_CreateShape_O() {
    // Shape O do not change coordinates
    Shape *shape = malloc(sizeof(Shape));
    shape->r1 = GAME_CreateRect(0, 0);
    shape->r2 = GAME_CreateRect(20, 0);
    shape->r3 = GAME_CreateRect(0, 20);
    shape->r4 = GAME_CreateRect(20, 20);
    shape->color = &FOREGROUND;
    return shape;
}