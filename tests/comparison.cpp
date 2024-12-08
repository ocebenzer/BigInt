#include "doctest/doctest.h"

#include "bigint/bigint.hpp"
#include "bigint/constants.hpp"

#include <cstdint>
#include <random>
#include <string>

using ocb::BigInt;

TEST_CASE("Less Than") {
    BigInt i;
    BigInt j;
    CHECK_FALSE(i < j);

    j += 1;
    CHECK(i < j);

    j = -2;
    CHECK_FALSE(i < j);
}

TEST_CASE("Greater Than") {
    BigInt i;
    BigInt j{0};
    CHECK_FALSE(i > j);

    i += 1;
    CHECK(i > j);

    j = 2;
    CHECK_FALSE(i > j);
}

TEST_CASE("Less Than Equal") {
    BigInt i{42};
    BigInt j{"43"};
    CHECK(i <= j);

    --j;
    CHECK(i <= j);

    ++i;
    CHECK_FALSE(i <= j);
}

TEST_CASE("Greater Than Equal") {
    BigInt i{"61"};
    BigInt j{62};
    CHECK(i <= j);

    --j;
    CHECK(i <= j);

    --j;
    CHECK_FALSE(i <= j);
}

TEST_CASE("Equal") {
    BigInt i{-100};
    BigInt j{-100};
    CHECK(i == j);

    i = 0;
    j = -0;
    CHECK(i == j);

    ++j;
    CHECK_FALSE(i == j);
}

TEST_CASE("Not Equal") {
    BigInt i{"36"};
    BigInt j{"-36"};
    CHECK(i != j);

    j = -j;
    CHECK_FALSE(i != j);

    i += 0;
    CHECK_FALSE(i != j);
}

TEST_CASE("Random Generation") {
    std::mt19937_64 rng;
    std::uniform_int_distribution<int64_t> distribution;

    for (int i{0}; i < NUM_GENERATIONAL_TESTS; ++i) {
        const int64_t n1{distribution(rng) / 2};
        const int64_t n2{distribution(rng) / 2};

        BigInt big1{n1};
        BigInt big2{n2};
        CHECK_EQ(big1 < big2, n1 < n2);
        CHECK_EQ(big1 > big2, n1 > n2);
        CHECK_EQ(big1 <= big2, n1 <= n2);
        CHECK_EQ(big1 >= big2, n1 >= n2);
        CHECK_EQ(big1 == big2, n1 == n2);
        CHECK_EQ(big1 != big2, n1 != n2);
    }
}
