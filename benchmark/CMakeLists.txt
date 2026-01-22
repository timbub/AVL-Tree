cmake_minimum_required(VERSION 3.20)

project(BENCH)

add_executable(avl)
target_sources(avl PRIVATE main_avl.cpp benchmark.hpp)

add_executable(set)
target_sources(set PRIVATE main_set.cpp benchmark.hpp)

