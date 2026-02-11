cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)

project(HWT)

add_compile_options(
    $<$<CONFIG:Debug>:-fsanitize=address>
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)

add_link_options(
    $<$<CONFIG:Debug>:-fsanitize=address>
    $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)

find_package(GTest REQUIRED)

add_library(avl_lib INTERFACE)
target_include_directories(avl_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/avl)

enable_testing()
add_subdirectory(avl)
add_subdirectory(set)
add_subdirectory(benchmark)
add_subdirectory(tests/unit)


