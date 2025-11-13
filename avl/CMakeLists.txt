cmake_minimum_required(VERSION 3.20)
project(HWT)
add_executable(tree)

target_sources(tree PRIVATE main.cpp tree.hpp)

set(SANITIZER_FLAGS "-fsanitize=address")
target_compile_options(tree PRIVATE $<$<CONFIG:Debug>:${SANITIZER_FLAGS}>)
target_link_options(tree PRIVATE $<$<CONFIG:Debug>:${SANITIZER_FLAGS}>)

