# Задание: Создать библиотеку pipes из read_pipe.c write_pipe.c
add_library(pipes STATIC 
    read_pipe.c 
    write_pipe.c 
) 
 
target_include_directories(pipes PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
)
