#include "../shape.h"
#include "../../color/color.h"
#include "../../util/util.h"
#include "../../board/board.h"
#include "SDL.h"

/* TODO: parameters that choose constraints such as type, position and color */
Shape *GAME_CreateShape_S() {
    Shape *shape = malloc(sizeof(Shape));
    if (shape == NULL) {
        GAME_LogError("Cannot Create Shape S");
        exit(-1);
    }

    shape->type = SHAPE_S;
    shape->rotate = ROTATE_LEFT;
    shape->r1 = GAME_CreateRect(0, 20);
    shape->r2 = GAME_CreateRect(20, 20);
    shape->r3 = GAME_CreateRect(20, 0); /* r3 always the middle */
    shape->r4 = GAME_CreateRect(40, 0);
    shape->color = &FOREGROUND;
    return shape;
}

Shape *GAME_CreateShape_RS() {
    Shape *shape = malloc(sizeof(Shape));
    if (shape == NULL) {
        GAME_LogError("Cannot Create Shape S");
        exit(-1);
    }

    shape->type = SHAPE_REVERSE_S;
    shape->rotate = ROTATE_LEFT;
    shape->r1 = GAME_CreateRect(0, 0);
    shape->r3 = GAME_CreateRect(20, 0); /* r3 always the middle */
    shape->r2 = GAME_CreateRect(20, 20);
    shape->r4 = GAME_CreateRect(40, 20);
    shape->color = &FOREGROUND;
    return shape;
}

void GAME_MoveShapeOut_S(Shape *shape) {
    GAME_MoveShapeOutsideBorder(shape, RIGHT_EDGE, &borderRect);
    GAME_MoveShapeOutsideBorder(shape, RIGHT_EDGE, &borderRect);
    GAME_MoveShapeOutsideBorder(shape, LEFT_EDGE, &borderRect);
    GAME_MoveShapeOutsideBorder(shape, LEFT_EDGE, &borderRect);
    GAME_MoveShapeOutsideBorder(shape, BOTTOM_EDGE, &borderRect);
    GAME_MoveShapeOutsideBorder(shape, BOTTOM_EDGE, &borderRect);
    GAME_MoveShapeOutsideShape(shape);
}