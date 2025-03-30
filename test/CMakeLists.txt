cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME "test")
project(${PROJECT_NAME})

SET(LIBS_TO_LINK "logger arena buffers")
add_executable(test ./ctest/main.c ./main.c  )
add_executable(buffers_test ./ctest/main.c ./buffers_test.c)
add_executable(arena_test ./ctest/main.c ./arena_test.c)

# seting up tests
target_include_directories(logger PRIVATE ../lib/logger/includes/)
target_compile_options(test PRIVATE -Wno-format-truncation -g)
target_link_libraries(test logger arena buffers )

# setting up buffers

target_compile_options(buffers_test PRIVATE -Wno-format-truncation -g)
target_link_libraries(buffers_test logger arena buffers )

# setting up arena
target_compile_options(arena_test PRIVATE -Wno-format-truncation -g)
target_link_libraries(arena_test logger arena buffers )


