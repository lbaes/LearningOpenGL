cmake_minimum_required(VERSION 3.1)
project(LearningOpenGL VERSION 1.0)

add_subdirectory("${CMAKE_SOURCE_DIR}/libs/")

add_executable(LearningOpenGL
               game.cpp)

target_include_directories(LearningOpenGL PUBLIC
                            "${PROJECT_SOURCE_DIR}/includes/"
                            "${PROJECT_SOURCE_DIR}/libs/shader"
                            "${PROJECT_SOURCE_DIR}/libs/texture"
                            "${PROJECT_SOURCE_DIR}/libs/glfw/include"
                            "${PROJECT_SOURCE_DIR}/libs/geometry"
                            "${PROJECT_SOURCE_DIR}/libs/glm"
                            "${PROJECT_SOURCE_DIR}/libs/glad"
                            "${PROJECT_SOURCE_DIR}/libs/camera")

target_link_libraries(LearningOpenGL PUBLIC glfw shader geometry textures glad glm camera assimp)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})