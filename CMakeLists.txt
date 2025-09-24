cmake_minimum_required(VERSION 3.31)
set(CMAKE_CXX_STANDARD 23)
add_compile_options(-g)

project(Timescale VERSION 1.0)

find_package(SDL3 REQUIRED)
include_directories(PUBLIC "include/")

add_library(Collider "source/collider.cpp")
add_library(Graphic "source/graphic.cpp")
add_library(Map "source/map.cpp")
add_library(Physic "source/physic.cpp")
add_executable(Timescale "source/main.cpp")

target_link_libraries(Timescale PUBLIC SDL3::SDL3)
target_link_libraries(Timescale PUBLIC Collider)
target_link_libraries(Timescale PUBLIC Graphic)
target_link_libraries(Timescale PUBLIC Map)
target_link_libraries(Timescale PUBLIC Physic)