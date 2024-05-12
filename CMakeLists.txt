cmake_minimum_required(VERSION 3.28)
project(csnake C)

set(CMAKE_C_STANDARD 11)

add_executable(csnake
        src/memory_allocator/memory_allocator.c
        src/memory_allocator/memory_allocator.h
        src/snake.c
        src/snake.h
        src/board.c
        src/board.h
        src/main.c
        src/errors.h
        src/pixel.h
        src/game_state.h
)
