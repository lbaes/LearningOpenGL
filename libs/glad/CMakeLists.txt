cmake_minimum_required(VERSION 3.1)
project (glad VERSION 1.0)

file(GLOB SOURCES "*.c")
add_library(glad STATIC ${SOURCES})
target_include_directories(glad PUBLIC ".")