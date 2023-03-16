cmake_minimum_required(VERSION 3.0.0)
project(tetris VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 99)
include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(tetris
    src/main.c
    src/shape/shape.c
    src/shape/shape.h
    src/shape/I_shape/I_shape.c
    src/shape/I_shape/I_rotate.c
    src/shape/alloc.c
    src/shape/collision.c
    src/shape/update.c
    src/shape/O_shape.c
    src/color/color.c
    src/board/board.c
    src/window/window.c
    src/window/window.h
    src/window/quit.c
    src/window/event_loop/loop.c
    src/window/event_loop/render.c
    src/window/event_loop/controller/controller.c
    src/util/util.c
)
target_include_directories(tetris PUBLIC src)
target_link_libraries(tetris ${SDL2_LIBRARIES})
target_compile_features(tetris PRIVATE c_std_99)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
