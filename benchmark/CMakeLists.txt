cmake_minimum_required(VERSION 3.20)

project(BENCH)

add_executable(b_avl)
target_sources(b_avl PRIVATE main_avl.cpp benchmark.hpp)

add_executable(b_set)
target_sources(b_set PRIVATE main_set.cpp benchmark.hpp)

