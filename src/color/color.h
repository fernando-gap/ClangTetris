#ifndef SRC_COLORS_H
#define SRC_COLORS_H

typedef struct Color {
    int red;
    int green;
    int blue;
} Color;

extern Color BACKGROUND;
extern Color FOREGROUND;

void GAME_SetColor(Color color);

#endif