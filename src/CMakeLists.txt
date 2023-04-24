cmake_minimum_required(VERSION 3.12)
project (Physine VERSION 1.0 LANGUAGES CXX)

add_library(PhysineCore collider.cpp world.cpp circle_shape.cpp text_drawable.cpp image_drawable.cpp
    rectangle_shape.cpp graphics.cpp collision_solver.cpp debug.cpp color.cpp event_manager.cpp
    ph_math.cpp)

target_compile_options(PhysineCore PRIVATE -Wall -Wextra -Wpedantic -Wno-c99-extensions)

add_executable(${PROJECT_NAME} main.cpp)
add_executable(Test test.cpp)
add_executable(AirResistance air_resistance_sample.cpp)
add_executable(Rotation rotation_test.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(PhysineCore sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC PhysineCore)
target_link_libraries(Test PUBLIC PhysineCore)
target_link_libraries(AirResistance PUBLIC PhysineCore)
target_link_libraries(Rotation PUBLIC PhysineCore)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../extern>
)
