cmake_minimum_required(VERSION 3.12)

project(test_cases VERSION 1.0 LANGUAGES CXX)

add_library(doctest_h INTERFACE)
target_include_directories(doctest_h INTERFACE ${CMAKE_SOURCE_DIR}/extern)

include (CTest)

function(make_test name)
    if (${ARGC} EQUAL 1)
        add_executable(${name} ${name}.cpp)
    else()
        add_executable(${name} ${name}.cpp ${ARGN})
    endif()
    target_link_libraries(${name} doctest_h)
    target_compile_definitions(${name} PRIVATE DOCTEST_CONFIG_NO_POSIX_SIGNALS)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

make_test(doctest_test)
