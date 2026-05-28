cmake_minimum_required(VERSION 3.10)

project(KeyboardTrainer C)

set(CMAKE_C_STANDARD 11)

add_executable(RGR
    RGR.c
    logger.c
    config.c
)

add_executable(tests
    tests.c
    RGR.c
    logger.c
    config.c
)

target_compile_definitions(tests PRIVATE TEST_BUILD)