cmake_minimum_required(VERSION 3.10)
project(BackgroundSystem C)

add_subdirectory(background)
add_subdirectory(pipes)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/background
)

add_executable(background_system 
    src/main.c
)

target_link_libraries(background_system 
    background
)
