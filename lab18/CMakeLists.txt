cmake_minimum_required(VERSION 3.14)
project(ShellSortTesting C)

enable_testing()

find_package(cmocka REQUIRED)

add_executable(test3 test3.c shell_sort.c)
add_test(NAME Test_Grade3_Manual COMMAND test3)

add_executable(test4 test4.c shell_sort.c)
target_include_directories(test4 PRIVATE ${CMOCKA_INCLUDE_DIR})
target_link_libraries(test4 ${CMOCKA_LIBRARIES})
add_test(NAME Test_Grade4_Framework COMMAND test4)