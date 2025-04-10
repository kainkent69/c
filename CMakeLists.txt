CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(main)
ADD_EXECUTABLE(main main.c)
TARGET_INCLUDE_DIRECTORIES(main PUBLIC .)

#settting up the Global Options
SET(GLOBAL_TARGET_COMPILE_OPTIONS "-g" "Make it debuggable")
# Include subdirectories
ADD_SUBDIRECTORY(lib) #setting the  lib
ADD_SUBDIRECTORY(tests)
