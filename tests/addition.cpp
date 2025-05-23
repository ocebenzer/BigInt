#include "doctest/doctest.h"

#include "ocb/bigint.hpp"
#include "ocb/bigint/tests.hpp"

#include <cstdint>
#include <random>
#include <string>

using ocb::BigInt;

TEST_CASE("Simple Addition") {
    BigInt i{36};

    i += 14;
    CHECK_EQ(i.get_value(), "50");
    CHECK_EQ(i.get_negative(), false);

    auto res{i + 1000};
    CHECK_EQ(res.get_value(), "1050");
    CHECK_EQ(res.get_negative(), false);
}

TEST_CASE("Increment") {
    BigInt i{100};

    auto pre_inc{i++};
    CHECK_EQ(pre_inc.get_value(), "100");
    CHECK_EQ(pre_inc.get_negative(), false);
    CHECK_EQ(i.get_value(), "101");
    CHECK_EQ(i.get_negative(), false);

    auto post_inc{++i};
    CHECK_EQ(post_inc.get_value(), "102");
    CHECK_EQ(post_inc.get_negative(), false);
    CHECK_EQ(i.get_value(), "102");
    CHECK_EQ(i.get_negative(), false);
}

TEST_CASE("Negative Addition") {
    BigInt i{36};

    i += -16;
    CHECK_EQ(i.to_string(), "20");
    CHECK_EQ(i.get_value(), "20");
    CHECK_EQ(i.get_negative(), false);

    auto res{i + -100};
    CHECK_EQ(res.to_string(), "-80");
    CHECK_EQ(res.get_value(), "80");
    CHECK_EQ(res.get_negative(), true);

    res = -1000 + res;
    CHECK_EQ(res.to_string(), "-1080");
    CHECK_EQ(res.get_value(), "1080");
    CHECK_EQ(res.get_negative(), true);
}

TEST_CASE("Random Generation") {
    std::mt19937_64 rng;
    std::uniform_int_distribution<long long int> distribution;

    for (int i{0}; i < NUM_GENERATIONAL_TESTS; ++i) {
        const long long int n1{distribution(rng) / 2};
        const long long int n2{distribution(rng) / 2};
        const long long int sum{n1 + n2};

        BigInt big1{n1};
        BigInt big2{n2};
        BigInt big_sum{big1 + big2};
        CHECK_EQ(big_sum, sum);
        CHECK_EQ(big_sum.get_negative(), sum < 0);
        CHECK_EQ(big_sum.to_string(), std::to_string(sum));
    }
}