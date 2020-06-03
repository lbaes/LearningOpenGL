cmake_minimum_required(VERSION 3.1)
project(shader VERSION 1.0)

file(GLOB SOURCES "*.cpp")
add_library(shader STATIC ${SOURCES})
target_include_directories(shader PUBLIC "../glm/" "../glad/")
