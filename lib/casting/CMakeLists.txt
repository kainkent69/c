CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(casting)
ADD_LIBRARY(casting SHARED ./casting.c)
TARGET_INCLUDE_DIRECTORIES(./ PUBLIC)
TARGET_COMPILE_OPTIONS(casting PUBLIC -g )

