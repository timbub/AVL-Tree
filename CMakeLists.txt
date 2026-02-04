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

add_subdirectory(avl)
add_subdirectory(set)
add_subdirectory(benchmark)


