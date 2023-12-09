#include "doctest/doctest.h"

#include "bigint.hpp"

using ocb::BigInt;

TEST_CASE("Default Constructor") {
    BigInt i;
    CHECK_EQ(i.get_value(), "0");
    CHECK_EQ(i.get_negative(), false);
}

TEST_CASE("Custom Constructors") {
{
    BigInt i{"42"};
    CHECK_EQ(i.get_value(), "42");
    CHECK_EQ(i.get_negative(), false);
    CHECK_EQ(i.get(), "42");
}

    BigInt i{"42"};
    CHECK_EQ(i.get_value(), "42");
    CHECK_EQ(i.get_negative(), false);
    CHECK_EQ(i.get(), "42");

    BigInt j{"-100"};
    CHECK_EQ(j.get_value(), "100");
    CHECK_EQ(j.get_negative(), true);
    CHECK_EQ(j.get(), "-100");

    BigInt k{"-0"};
    CHECK_EQ(k.get_value(), "0");
    CHECK_EQ(k.get_negative(), false);
    CHECK_EQ(k.get(), "0");
}
