
cmake_minimum_required(VERSION 3.10)
project(logger)

add_library(logger ./logger/src/log.c)
target_include_directories(logger PUBLIC ./logger/src/)
target_compile_options(logger PUBLIC -g)

