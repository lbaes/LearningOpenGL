cmake_minimum_required(VERSION 3.1)
project (textures VERSION 1.0)

file(GLOB SOURCES "*.cpp")
add_library(textures STATIC ${SOURCES})
target_include_directories(textures PUBLIC "../glad/")