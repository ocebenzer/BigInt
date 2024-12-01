#include "doctest/doctest.h"

#include "bigint.hpp"
#include "constants.hpp"

#include <cstdint>
#include <random>

using ocb::BigInt;

TEST_CASE("Simple Divison") {
    BigInt i{15};
    i /= 3;

    CHECK_EQ(i.to_string(), "5");
    CHECK_EQ(i.get_value(), "5");
    CHECK_EQ(i.get_negative(), false);

    auto res{i / 5};

    CHECK_EQ(res.to_string(), "1");
    CHECK_EQ(res.get_value(), "1");
    CHECK_EQ(res.get_negative(), false);
}

TEST_CASE("Negative Divison") {
    BigInt i{-60};
    CHECK_EQ(i.to_string(), "-60");
    CHECK_EQ(i.get_value(), "60");
    CHECK_EQ(i.get_negative(), true);

    i /= -3;
    CHECK_EQ(i.to_string(), "20");
    CHECK_EQ(i.get_value(), "20");
    CHECK_EQ(i.get_negative(), false);

    auto res{i / -5};
    CHECK_EQ(res.to_string(), "-4");
    CHECK_EQ(res.get_value(), "4");
    CHECK_EQ(res.get_negative(), true);

    res = res / -2;
    CHECK_EQ(res.to_string(), "2");
    CHECK_EQ(res.get_value(), "2");
    CHECK_EQ(res.get_negative(), false);

    res /= -2;
    CHECK_EQ(res.to_string(), "-1");
    CHECK_EQ(res.get_value(), "1");
    CHECK_EQ(res.get_negative(), true);
}

TEST_CASE("Divison with Remainder") {
    BigInt i{51};
    CHECK_EQ(i.to_string(), "51");
    CHECK_EQ(i.get_value(), "51");
    CHECK_EQ(i.get_negative(), false);

    i /= 10;
    CHECK_EQ(i.to_string(), "5");
    CHECK_EQ(i.get_value(), "5");
    CHECK_EQ(i.get_negative(), false);

    auto res{i / 3};
    CHECK_EQ(res.to_string(), "1");
    CHECK_EQ(res.get_value(), "1");
    CHECK_EQ(res.get_negative(), false);
}

TEST_CASE("Negative Divison with Remainder") {
    BigInt i{-51};
    CHECK_EQ(i.to_string(), "-51");
    CHECK_EQ(i.get_value(), "51");
    CHECK_EQ(i.get_negative(), true);

    i /= -10;
    CHECK_EQ(i.to_string(), "5");
    CHECK_EQ(i.get_value(), "5");
    CHECK_EQ(i.get_negative(), false);

    auto res{i / 3};
    CHECK_EQ(res.to_string(), "1");
    CHECK_EQ(res.get_value(), "1");
    CHECK_EQ(res.get_negative(), false);
}

TEST_CASE("Random Generation") {
    std::mt19937_64 rng;
    std::uniform_int_distribution<int64_t> distribution;

    for (int i{0}; i < NUM_GENERATIONAL_TESTS; ++i) {
        const int64_t n1{distribution(rng)};
        const int64_t n2{static_cast<int32_t>(distribution(rng))};
        if (n2 == 0) continue;
        const int64_t div{n1 / n2};

        BigInt big1{n1};
        BigInt big2{n2};
        BigInt big_div{big1 / big2};
        CHECK_EQ(big_div, div);
        CHECK_EQ(big_div.get_negative(), div < 0);
        CHECK_EQ(big_div.to_string(), std::to_string(div));
    }
}

TEST_CASE("Divide by Zero") {
    BigInt i{5};
    CHECK_EQ(i.to_string(), "5");
    CHECK_EQ(i.get_value(), "5");
    CHECK_EQ(i.get_negative(), false);

    CHECK_THROWS(i /= 0);

    auto res{0 / i};
    CHECK_EQ(res.to_string(), "0");
    CHECK_EQ(res.get_value(), "0");
    CHECK_EQ(res.get_negative(), false);

    res = -0 / i;
    CHECK_EQ(res.to_string(), "0");
    CHECK_EQ(res.get_value(), "0");
    CHECK_EQ(res.get_negative(), false);
}
