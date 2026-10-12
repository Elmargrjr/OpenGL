cmake_minimum_required(VERSION 3.20)

project(opengl-curso LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(opengl-curso src/main.cpp)

target_link_libraries(opengl-curso PRIVATE glfw glad::glad glm::glm)