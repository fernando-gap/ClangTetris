#include "window/window.h"
#include "window/event_loop/loop.h"
#include "util/util.h"
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    GAME_WindowInit();
    GAME_EventLoop();
    GAME_Quit();
    return 0;
}