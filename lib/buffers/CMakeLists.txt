cmake_minimum_required(VERSION 3.10) #updated to a newer version
project(buffers)

add_library(buffers buffers.c)
target_include_directories(buffers PUBLIC . )
target_compile_options(buffers PUBLIC -g)
target_link_libraries(buffers PUBLIC logger)

# for making test
add_executable(buffers_test ./test.c)
target_compile_options(buffers_test PRIVATE -Wno-format-truncation -g)
target_link_libraries(buffers_test buffers logger)
