cmake_minimum_required(VERSION 3.5.0)
project(bigint)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

find_package(doctest)
if (NOT doctest_FOUND)
    include_directories(${DOCTEST_PATH})
endif()

include_directories(include)

add_library(utils src/utils.cpp)

add_library(bigint
    src/bigint/addition.cpp
    src/bigint/subtraction.cpp
    src/bigint/multiplication.cpp
    src/bigint/division.cpp
    src/bigint/modulo.cpp
    src/bigint/logical.cpp
    src/bigint/stream.cpp
    src/bigint/misc.cpp
    src/bigint/bigint.cpp)

add_executable(bigint_tests
    tests/constructor.cpp
    tests/addition.cpp
    tests/subtraction.cpp
    tests/multiplication.cpp
    tests/division.cpp
    tests/modulo.cpp
    tests/logical.cpp
    tests/stream.cpp
    tests/main.cpp)

target_link_libraries(bigint_tests PRIVATE bigint utils)

add_compile_options(-Wall -Wextra -Wconversion -pedantic -Wfatal-errors)
