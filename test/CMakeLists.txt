cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME "test")
project(${PROJECT_NAME})

add_executable(test ./ctest/main.c ./main.c  )
target_include_directories(logger PRIVATE ../lib/logger/includes/)
target_compile_options(test PRIVATE -Wno-format-truncation -g)
target_link_libraries(test logger arena buffers  )

