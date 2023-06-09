cmake_minimum_required(VERSION 3.12)
project (Physine VERSION 1.0 LANGUAGES CXX)

set(version 1.0)

add_library(PhysineCore STATIC collider.cpp world.cpp circle_shape.cpp image_drawable.cpp
    rectangle_shape.cpp graphics.cpp collision_solver.cpp debug.cpp color.cpp event_manager.cpp
    ph_math.cpp)

target_compile_options(PhysineCore PRIVATE -Wall -Wextra -Wpedantic -Wno-c99-extensions)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(PhysineCore sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
endif()

target_include_directories(PhysineCore PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

install(FILES collider.h color.h event.h keyboard.h rect.h callback_list.h collision.h common.h world.h
        circle.h collision_points.h constants.h event_manager.h object.h timer.h object_builder.h
        transform.h clock.h collision_solver.h debug.h graphics.h utils.h drawable.h ph_math.h vector.h
        DESTINATION include/physine-${version}/Physine)
install(TARGETS PhysineCore
    DESTINATION lib/physine-${version}
    EXPORT physine-targets)
install(EXPORT physine-targets
    DESTINATION lib/physine-${version})

configure_file(
    ${Physine_SOURCE_DIR}/pkg/physine-config.cmake.in
    ${Physine_BINARY_DIR}/pkg/physine-config.cmake @ONLY
    )

configure_file(
    ${Physine_SOURCE_DIR}/physine-config-version.cmake.in
    ${Physine_BINARY_DIR}/physine-config-version.cmake @ONLY
    )

install(FILES ${Physine_BINARY_DIR}/pkg/physine-config.cmake
    ${Physine_BINARY_DIR}/physine-config-version.cmake
    DESTINATION lib/physine-${version})
