cmake_minimum_required(VERSION 3.20)
project(HWT)
add_executable(bench)

target_sources(bench PRIVATE main.cpp benchmark.hpp)

set(SANITIZER_FLAGS "-fsanitize=address" "-g" "-fno-omit-frame-pointer")
target_compile_options(bench PRIVATE $<$<CONFIG:Debug>:${SANITIZER_FLAGS}>)
target_link_options(bench PRIVATE $<$<CONFIG:Debug>:${SANITIZER_FLAGS}>)
