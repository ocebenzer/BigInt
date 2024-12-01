cmake_minimum_required(VERSION 3.5.0)
project(bigint)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(bigint
    src/bigint/bigint.cpp
    src/bigint/unary.cpp
    src/bigint/arithmetic.cpp
    src/bigint/arithmetic-overrides.cpp
    src/bigint/bitwise-arithmetic-operators.cpp
    src/bigint/comparison.cpp
    src/bigint/stream.cpp
    src/bigint/misc.cpp
    src/utils.cpp
)

add_executable(bigint_tests
    tests/constructor.cpp
    tests/addition.cpp
    tests/subtraction.cpp
    tests/multiplication.cpp
    tests/division.cpp
    tests/modulo.cpp
    tests/comparison.cpp
    tests/stream.cpp
    tests/main.cpp
)

target_link_libraries(bigint_tests PRIVATE bigint)

add_compile_options(-Wall -Wextra -Wconversion -pedantic -Wfatal-errors)
