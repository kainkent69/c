CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(arena)
add_library(arena SHARED ./arena.c)
target_include_directories(arena PUBLIC ./)
target_compile_options(arena PUBLIC -g)

