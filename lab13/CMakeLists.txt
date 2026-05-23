cmake_minimum_required(VERSION 3.10)

project(smarthome)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(LIB_SOURCE ${SOURCE_DIR}/smarthome.c)

include_directories(${INCLUDE_DIR})

option(BUILD_SHARED_LIBS OFF)

add_library(smarthome ${LIB_SOURCE})

add_executable(program ${SOURCE_DIR}/main.c)

target_link_libraries(program smarthome)



