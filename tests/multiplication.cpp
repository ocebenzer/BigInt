#include "doctest/doctest.h"

#include "bigint.hpp"
#include "constants.hpp"

#include <cstdint>
#include <random>

using ocb::BigInt;

TEST_CASE("Simple Multiplication") {
    BigInt i{3};
    i *= 5;

    CHECK_EQ(i.get(), "15");
    CHECK_EQ(i.get_value(), "15");
    CHECK_EQ(i.get_negative(), false);

    auto res{i * 0};

    CHECK_EQ(res.get(), "0");
    CHECK_EQ(res.get_value(), "0");
    CHECK_EQ(res.get_negative(), false);
}

TEST_CASE("Negative Multiplication") {
    BigInt i{-6};
    CHECK_EQ(i.get(), "-6");
    CHECK_EQ(i.get_value(), "6");
    CHECK_EQ(i.get_negative(), true);

    i *= 9;
    CHECK_EQ(i.get(), "-54");
    CHECK_EQ(i.get_value(), "54");
    CHECK_EQ(i.get_negative(), true);

    auto res{i * -5};
    CHECK_EQ(res.get(), "270");
    CHECK_EQ(res.get_value(), "270");
    CHECK_EQ(res.get_negative(), false);

    res = -2 * res;
    CHECK_EQ(res.get(), "-540");
    CHECK_EQ(res.get_value(), "540");
    CHECK_EQ(res.get_negative(), true);

    res *= 0;
    CHECK_EQ(res.get(), "0");
    CHECK_EQ(res.get_value(), "0");
    CHECK_EQ(res.get_negative(), false);
}

TEST_CASE("Random Generation") {
    std::mt19937_64 rng;
    std::uniform_int_distribution<int32_t> distribution;

    for (int i{0}; i < NUM_GENERATIONAL_TESTS; ++i) {
        const int64_t n1{distribution(rng)};
        const int64_t n2{distribution(rng)};
        const int64_t mul{n1 * n2};

        BigInt big1{n1};
        BigInt big2{n2};
        BigInt big_mul{big1 * big2};
        CHECK_EQ(big_mul, mul);
        CHECK_EQ(big_mul.get_negative(), mul < 0);
        CHECK_EQ(big_mul.get(), std::to_string(mul));
    }
}
