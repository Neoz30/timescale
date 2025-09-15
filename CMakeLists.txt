cmake_minimum_required(VERSION 3.31)
set(CMAKE_CXX_STANDARD 23)

project(Timescale VERSION 1.0)

find_package(SDL3 REQUIRED)
include_directories(PRIVATE "include/")

add_executable(Timescale "source/main.cpp")

target_link_libraries(Timescale PRIVATE SDL3::SDL3)