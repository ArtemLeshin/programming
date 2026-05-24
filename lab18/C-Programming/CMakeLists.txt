cmake_minimum_required(VERSION 3.10)
project(Paint++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем правильный путь к SFML из Homebrew на Mac M1/M2/M3
set(SFML_DIR "/opt/homebrew/opt/sfml@2/lib/cmake/SFML")

message(STATUS "Checking for SFML library...")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Добавляем все исходные файлы
add_executable(paint src/main.cpp src/paint_core.cpp)

# ИСПРАВЛЕНО: Правильные имена библиотек с префиксом sfml-
target_link_libraries(paint sfml-graphics sfml-window sfml-system)
