#include "doctest/doctest.h"

#include "ocb/bigint.hpp"

using ocb::BigInt;

TEST_CASE("Factorial") {
    CHECK_EQ(ocb::factorial(0), 1);
    CHECK_EQ(ocb::factorial(1), 1);
    CHECK_EQ(ocb::factorial(2), 2);
    CHECK_EQ(ocb::factorial(3), 6);
    CHECK_EQ(ocb::factorial(4), 24);
    CHECK_EQ(ocb::factorial(5), 120);

    CHECK_EQ(ocb::factorial(10), 3628800);
}

TEST_CASE("Fibonacci") {
    CHECK_EQ(ocb::fibonacci(1), 1);
    CHECK_EQ(ocb::fibonacci(2), 1);
    CHECK_EQ(ocb::fibonacci(3), 2);
    CHECK_EQ(ocb::fibonacci(4), 3);
    CHECK_EQ(ocb::fibonacci(5), 5);
    CHECK_EQ(ocb::fibonacci(6), 8);

    CHECK_EQ(ocb::fibonacci(10), 55);
    CHECK_EQ(ocb::fibonacci(20), 6765);
}