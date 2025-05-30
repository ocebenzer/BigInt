#include "doctest/doctest.h"

#include "ocb/bigint.hpp"
#include "ocb/bigint/tests.hpp"

#include <random>

using ocb::BigInt;

TEST_CASE("Simple Subtraction") {
    BigInt i{36};
    i -= 6;

    CHECK_EQ(i.to_string(), "30");
    CHECK_EQ(i.get_value(), "30");
    CHECK_EQ(i.get_negative(), false);

    auto res{i - 20};

    CHECK_EQ(res.to_string(), "10");
    CHECK_EQ(res.get_value(), "10");
    CHECK_EQ(res.get_negative(), false);
}

TEST_CASE("Decrement") {
    BigInt i{100};

    auto pre_inc{i--};
    CHECK_EQ(pre_inc.get_value(), "100");
    CHECK_EQ(pre_inc.get_negative(), false);
    CHECK_EQ(i.get_value(), "99");
    CHECK_EQ(i.get_negative(), false);

    auto post_inc{--i};
    CHECK_EQ(post_inc.get_value(), "98");
    CHECK_EQ(post_inc.get_negative(), false);
    CHECK_EQ(i.get_value(), "98");
    CHECK_EQ(i.get_negative(), false);
}

TEST_CASE("Negative Subtraction") {
    BigInt i{-36};
    CHECK_EQ(i.to_string(), "-36");
    CHECK_EQ(i.get_value(), "36");
    CHECK_EQ(i.get_negative(), true);

    i -= -72;
    CHECK_EQ(i.to_string(), "36");
    CHECK_EQ(i.get_value(), "36");
    CHECK_EQ(i.get_negative(), false);

    auto res{i - -64};
    CHECK_EQ(res.to_string(), "100");
    CHECK_EQ(res.get_value(), "100");
    CHECK_EQ(res.get_negative(), false);

    res = res - -60;
    CHECK_EQ(res.to_string(), "160");
    CHECK_EQ(res.get_value(), "160");
    CHECK_EQ(res.get_negative(), false);

    res = -160 + res;
    CHECK_EQ(res.to_string(), "0");
    CHECK_EQ(res.get_value(), "0");
    CHECK_EQ(res.get_negative(), false);
}

TEST_CASE("Random Generation") {
    std::mt19937_64 rng;
    std::uniform_int_distribution<long long int> distribution;

    for (int i{0}; i < NUM_GENERATIONAL_TESTS; ++i) {
        const long long int n1{distribution(rng) / 2};
        const long long int n2{distribution(rng) / 2};
        const long long int sub{n1 - n2};

        BigInt big1{n1};
        BigInt big2{n2};
        BigInt big_sub{big1 - big2};
        CHECK_EQ(big_sub, sub);
        CHECK_EQ(big_sub.get_negative(), sub < 0);
        CHECK_EQ(big_sub.to_string(), std::to_string(sub));
    }
}
