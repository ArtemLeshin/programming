# Задание: Создать библиотеку из background.c и слинковать ее с библиотекой pipes
add_library(background STATIC 
    background.c 
) 
target_link_libraries(background 
    pipes 
)