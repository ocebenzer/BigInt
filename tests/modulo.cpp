#include "doctest/doctest.h"

#include "bigint.hpp"
#include "constants.hpp"

#include <cstdint>
#include <random>

using ocb::BigInt;

TEST_CASE("Simple Modulo") {
    BigInt i{15};
    i %= 4;

    CHECK_EQ(i.get(), "3");
    CHECK_EQ(i.get_value(), "3");
    CHECK_EQ(i.get_negative(), false);

    auto res{i % 1};

    CHECK_EQ(res.get(), "0");
    CHECK_EQ(res.get_value(), "0");
    CHECK_EQ(res.get_negative(), false);
}

TEST_CASE("Negative Modulo") {
    BigInt i{-61};
    CHECK_EQ(i.get(), "-61");
    CHECK_EQ(i.get_value(), "61");
    CHECK_EQ(i.get_negative(), true);

    i %= -13;
    CHECK_EQ(i.get(), "-9");
    CHECK_EQ(i.get_value(), "9");
    CHECK_EQ(i.get_negative(), true);

    auto res{i % 5};
    CHECK_EQ(res.get(), "-4");
    CHECK_EQ(res.get_value(), "4");
    CHECK_EQ(res.get_negative(), true);
}

TEST_CASE("Random Generation") {
    std::mt19937_64 rng;
    std::uniform_int_distribution<int64_t> distribution;

    for (int i{0}; i < NUM_GENERATIONAL_TESTS; ++i) {
        const int64_t n1{distribution(rng)};
        const int64_t n2{static_cast<int32_t>(distribution(rng))};
        if (n2 == 0) continue;
        const int64_t mod{n1 % n2};

        BigInt big1{n1};
        BigInt big2{n2};
        BigInt big_mod{big1 % big2};
        CHECK_EQ(big_mod, mod);
        CHECK_EQ(big_mod.get_negative(), mod < 0);
        CHECK_EQ(big_mod.get(), std::to_string(mod));
    }
}

TEST_CASE("Modulo of Zero") {
    BigInt i{5};
    CHECK_EQ(i.get(), "5");
    CHECK_EQ(i.get_value(), "5");
    CHECK_EQ(i.get_negative(), false);

    CHECK_THROWS(i %= 0);

    // auto res{0 % i};
    // CHECK_EQ(res.get(), "0");
    // CHECK_EQ(res.get_value(), "0");
    // CHECK_EQ(res.get_negative(), false);

    // res = -0 % i;
    // CHECK_EQ(res.get(), "0");
    // CHECK_EQ(res.get_value(), "0");
    // CHECK_EQ(res.get_negative(), false);
}
