cmake_minimum_required(VERSION 3.10) #updated to a newer version
project(buffers)

add_library(buffers buffers.c)
target_include_directories(buffers PUBLIC . )
target_compile_options(buffers PUBLIC -g)
target_link_libraries(buffers PUBLIC logger verbose)

