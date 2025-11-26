cmake_minimum_required(VERSION 3.20)

project(BENCH)

add_executable(benchmark)
target_sources(benchmark PRIVATE main.cpp benchmark.hpp)

