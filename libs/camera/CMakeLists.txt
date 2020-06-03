cmake_minimum_required(VERSION 3.1)
project (camera VERSION 1.0)

file(GLOB SOURCES "*.cpp")
add_library(camera STATIC ${SOURCES})
target_include_directories(camera PUBLIC "../glm/" "../glad/")