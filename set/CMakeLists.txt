cmake_minimum_required(VERSION 3.20)
project(HWT)
add_executable(set)

target_sources(set PRIVATE main.cpp)

set(SANITIZER_FLAGS "-fsanitize=address")
target_compile_options(set PRIVATE $<$<CONFIG:Debug>:${SANITIZER_FLAGS}>)
target_link_options(set PRIVATE $<$<CONFIG:Debug>:${SANITIZER_FLAGS}>)

