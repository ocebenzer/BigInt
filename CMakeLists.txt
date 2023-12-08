cmake_minimum_required(VERSION 3.0.0)
project(bigint)

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

find_package(doctest REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

include_directories(include)

add_library(bigint src/bigint.cpp)

add_executable(bigint_tests tests/constructor.cpp tests/addition.cpp tests/main.cpp)
target_link_libraries(bigint_tests PRIVATE bigint)

add_compile_options(-Wall -Wextra -Wconversion -pedantic -Wfatal-errors)
