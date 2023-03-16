#include "window/window.h"
#include "window/event_loop/loop.h"
#include "util/util.h"

int main() {
    GAME_WindowInit();
    GAME_EventLoop();
    GAME_Quit();
    return 0;
}