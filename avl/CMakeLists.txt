cmake_minimum_required(VERSION 3.20)
project(HWT)
add_executable(avl)

target_sources(avl PRIVATE main.cpp tree.hpp)

set(SANITIZER_FLAGS "-fsanitize=address" "-g" "-fno-omit-frame-pointer")
target_compile_options(avl PRIVATE $<$<CONFIG:Debug>:${SANITIZER_FLAGS}>)
target_link_options(avl PRIVATE $<$<CONFIG:Debug>:${SANITIZER_FLAGS}>)


