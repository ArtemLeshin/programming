cmake_minimum_required(VERSION 3.10)
project(ATM2077 VERSION 1.0.0 DESCRIPTION "NeuralBank ATM System")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")

add_executable(atm2077 ${SOURCES} ${HEADERS})

add_custom_target(prepare_dirs ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/data/cards
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/data/accounts
    COMMENT "Создаю киберпанк-хранилище..."
)

add_dependencies(atm2077 prepare_dirs)

set_target_properties(atm2077 PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/data"
)

# Обычный запуск
add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/bin/atm2077
    DEPENDS atm2077
    COMMENT "Запускаем ATM 2077..."
)

# Очистка данных
add_custom_target(clean_data
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/data
    COMMAND ${CMAKE_COMMAND} -E echo "Данные удалены."
)

add_custom_command(TARGET atm2077 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Сборка завершена! Запусти: make run"
)
