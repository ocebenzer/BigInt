#include "doctest/doctest.h"

#include "bigint.hpp"

TEST_CASE("Simple Subtraction") {
    BigInt i{36};
    i -= 6;

    CHECK_EQ(i.get_value(), "30");
    CHECK_EQ(i.get_negative(), false);

    auto res{i - 20};

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
