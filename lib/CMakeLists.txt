cmake_minimum_required(VERSION 3.10)
project(lib)
add_library(logger  ./loggers/src/log.c )
target_include_directories(logger PUBLIC ./loggers/src/ )
target_compile_options(logger PRIVATE -g)
add_subdirectory(./verbose)
add_subdirectory(./buffers)

