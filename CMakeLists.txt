cmake_minimum_required (VERSION 3.0)
set(project maze)
project(${project})

find_package(glbinding REQUIRED)

set(use_utilgpu_compilation_options ON)
find_package(utilgpu REQUIRED)

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

find_package(Qt5Core REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(source)
add_subdirectory(test)
