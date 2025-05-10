#include "doctest/doctest.h"

#include "ocb/bigint.hpp"
#include "ocb/bigint/tests.hpp"

using ocb::BigInt;

TEST_CASE("Factorial") {
    CHECK_EQ(BigInt::factorial(0), 1);
    CHECK_EQ(BigInt::factorial(1), 1);
    CHECK_EQ(BigInt::factorial(2), 2);
    CHECK_EQ(BigInt::factorial(3), 6);
    CHECK_EQ(BigInt::factorial(4), 24);
    CHECK_EQ(BigInt::factorial(5), 120);

    CHECK_EQ(BigInt::factorial(10), 3628800);
}

TEST_CASE("Fibonacci") {
    CHECK_EQ(BigInt::fibonacci(1), 1);
    CHECK_EQ(BigInt::fibonacci(2), 1);
    CHECK_EQ(BigInt::fibonacci(3), 2);
    CHECK_EQ(BigInt::fibonacci(4), 3);
    CHECK_EQ(BigInt::fibonacci(5), 5);
    CHECK_EQ(BigInt::fibonacci(6), 8);

    CHECK_EQ(BigInt::fibonacci(10), 55);
    CHECK_EQ(BigInt::fibonacci(20), 6765);
}