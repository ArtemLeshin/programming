cmake_minimum_required(VERSION 3.10)
project(VibeBank2077 VERSION 1.0)

# Устанавливаем стандарт C++17 для поддержки современных фич
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Собираем все .cpp файлы в текущей директории
file(GLOB SOURCES "*.cpp")

# Создаем исполняемый файл
add_executable(VibeBank_2077 ${SOURCES})

# Добавляем опции для красоты и безопасности
if(MSVC)
    target_compile_options(VibeBank_2077 PRIVATE /W4)
else()
    target_compile_options(VibeBank_2077 PRIVATE -Wall -Wextra -Wpedantic)
endif()