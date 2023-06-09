cmake_minimum_required(VERSION 3.12)
project(BallsSample VERSION 1.0 LANGUAGES CXX)

find_package(physine 1.0 REQUIRED)
include_directories(${physine_INCLUDE_DIRS})

add_executable(FallingBalls FallingBalls.cpp)
target_link_libraries(FallingBalls PhysineCore)
