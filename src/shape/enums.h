#ifndef SRC_SHAPE_ENUMS_H
#define  SRC_SHAPE_ENUMS_H

typedef enum RectangleSides {
    RIGHT_EDGE = 1,
    LEFT_EDGE,
    TOP_EDGE,
    BOTTOM_EDGE
} RectangleSides;

typedef enum ShapeRotation {
    ROTATE_TOP,    // from left to top
    ROTATE_RIGHT,  // from top to right
    ROTATE_BOTTOM, // from right to bottom
    ROTATE_LEFT,   // from bottom to left
} ShapeRotation;

typedef enum ShapeTypes {
    SHAPE_I = 1,
    SHAPE_S = 2,
    SHAPE_L = 3,
    SHAPE_O = 4,
    SHAPE_REVERSE_S = 5,
    SHAPE_REVERSE_L = 6,
    SHAPE_K = 7
} ShapeTypes;

#endif