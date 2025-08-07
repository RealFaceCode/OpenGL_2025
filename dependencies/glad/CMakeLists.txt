project(glad)
cmake_minimum_required(VERSION 3.20)

set(SOURCE_FILES src/gl.c)

add_library(glad STATIC ${SOURCE_FILES})
target_include_directories(glad PUBLIC include)