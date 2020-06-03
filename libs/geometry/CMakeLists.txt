cmake_minimum_required(VERSION 3.1)
project (geometry VERSION 1.0)

file(GLOB SOURCES "*.cpp")
add_library(geometry STATIC ${SOURCES})
target_include_directories(geometry PUBLIC "../glad")